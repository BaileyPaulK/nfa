#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <string>
#include <math.h>
#include <limits>

//#include "path.h"
#include "node.h"
#include "nodes.h"
//#include "usefull.h"
//#include "node.cpp"
using namespace std;

/* NFA file to data struct
structure for input
N(NodeNumber) {(Char),n(NodeNumber)} {(Char),n(NodeNumber)} {n(NodeNumber)} //for null paths
example: N0 {a,n1} N1 {n2} N2 {n3} {n13} N3 {n8} {n4} N4 {c,n5}
N5 {o, n6} N6 {w, n7} N7 {n12} N8 {c, n9} N9 {a, n10} N10 {t,n11} N11 {n12} N12 {n13} N13 {n2}
NOTE: N's do not need to be in order, and white space is ignored unless between { , as a char for a path

future me look at 
-passing of strings through functions (optimization)
*/




void DEBUG(nodes& NODES)
{
    cout << endl << "debug nodes" << endl;
    for (node* node : NODES.nodeList)
    {
        cout << "Node :N" << node->N << ": ";
        for (struct path path : node->paths)
        {
            cout << "{" << path.state << ", n" << path.to->N << "} ";
        }
        cout << endl << endl;
    }
}

void buildNFA(nodes& NODES)
{
    ifstream inputfile ("input.txt");
    int currentNode = -1; //using nodes list because context is needed for adding paths
    string line;
    string path;
    while (getline(inputfile, line))
    {
        cout << "New line:" << line << ":" << endl;
        int point = 0;
        while (point >= 0 && point < line.size())
        {
            cout << "line left :" << line.substr(point, line.length() - point) << endl;
            point = min(line.find('N', point), line.find('{', point)); //set point to nearest N or { ::find(line, point, 'N'), find(line, point, '{')
            //DEBUG(NODES);
            switch (line[point])
            {
            case 'N':
                point ++;
                currentNode = NODES.addNode(line, point)->index;
                cout << "New node :" << NODES.nodeList[currentNode]->N << ":" << endl;
                break;
            case '{':
                path = line.substr(point, line.find('}', point + 2) - point + 1); //gross ik, but yeah
                NODES.addPath(currentNode, path);
                cout << "New path :" << NODES.nodeList[currentNode]->paths.back().state << "-> n" << NODES.nodeList[currentNode]->paths.back().to->N <<":" << endl;
                point += path.size() - 1;
                break;
            default:        //should mean end of args for line, so index should be set to -1
                //index ++;
                break;
            }
        }
    }
    
    inputfile.close();
}

class DFA: public nodes
{
private:
public:
    DFA();
    ~DFA();
    node* buildEFrom(int N, nodes);
};

node* DFA::buildEFrom(int N, nodes Nodes)
{
    node* E = this->findNode(N);
    if (E != NULL)  //check to make sure eclosure doesn't exist already
    {
        cout << "eclosure already found for that node" << endl;
        return E;
    }
    E = Nodes.findNode(N);
    deque<node*> toAdd;
    node* startNode;
    if (E != NULL)
    {
    toAdd.push_back(E);
    startNode = this->addNode(N);
    }
    else
    {
        return NULL;
    }
    
    while (toAdd.size() != 0)
    {
        E = toAdd.front();
        //cout << ":" << E->N << ":";
        toAdd.pop_front();
        startNode->eclosure.push_back(E);
        for (path path: E->paths) //checks for paths that have empty transitions
        {                           //this part is a lil ugly ik, but isn't the worst looking and should be decently optimized (based on current search alg)
            if (path.state == '\0')
            {
                int index = 0;
                while (index < startNode->eclosure.size() - 1 && startNode->eclosure[index]->N != path.to->N)
                {
                    index ++;
                }
                if (startNode->eclosure[index]->N != path.to->N)
                {
                    index = 0;
                    if (!toAdd.empty())
                    {
                        while (index < toAdd.size()  - 1 && toAdd[index]->N != path.to->N)
                        {
                            index ++;
                        }
                        if (toAdd[index]->N != path.to->N)
                        {
                            toAdd.push_back(path.to);
                            //cout << "adding " << path.to->N << ", ";
                        }
                    }
                    else
                    {
                        toAdd.push_back(path.to);
                        //cout << "adding " << path.to->N << ", ";
                    }
                    
                }
                
            }
            
        }
        
    }
    return startNode;
}

DFA::DFA(/* args */)
{
}

DFA::~DFA()
{
}


int main() 
{
    nodes NFA;
    buildNFA(NFA);
    DEBUG(NFA);

    DFA dfa;
    node* ecloser;
    int input;
    while (input >= 0)
    {
        cout << endl << "input node to make eclosure from (or < 0 to stop): ";
        cin >> input;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        ecloser = dfa.buildEFrom(input, NFA);
        if (ecloser != NULL)
        {
            cout << "ECLOSER" << endl;
            for (node* node : ecloser->eclosure)
            {
                cout << "N" << node->N << ", ";
            }
            cout << endl;
        }
        else
        {
            cout << "That node... doesn't exist.... you good???" << endl;
        }
        
    }
    

    return 0;
}



