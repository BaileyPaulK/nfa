#include "nodes.h"
using namespace std;

void nodes::addPath(int index, string path)
{
    this->nodeList[index]->addPath(getPath(path));
}

int nodes::addNode(node* newNode)
{
    int index = findSpot(newNode->N);
    this->nodeList.insert(this->nodeList.begin() + index, newNode);
    newNode->index = index;
    //correct index's of nodes after
    int correct = index;
    while (correct + 1 < this->nodeList.size())
    {
        correct ++;
        this->nodeList[correct]->index ++;
    }
    return index;
}

node* nodes::addNode(string arg, int index)
{
    node* newNode   = new node(arg, index);
    node* check     = this->findNode(newNode->N);
    if (check == NULL) //Node doesn't exist yet
    {
        addNode(newNode);
        return newNode;
    }
    cout << "node :" << newNode->N << ": already existed in list" << endl;
    newNode->~node();
    return check;
}

node* nodes::addNode(int n)
{
    node* newNode = new node(n);
    addNode(newNode);
    return newNode;
}

node* nodes::findNode(int n) //binary search for gross but need to get working first
{
    int index = findSpot(n);
    if (index < this->nodeList.size() && this->nodeList[index]->N == n)
    {
        cout << n << " == " << this->nodeList[index]->N << endl;
        return nodeList[index];
    } 
    /*else if (index + 1 < this->nodeList.size() && this->nodeList[index + 1]->N == n)
    {
        return nodeList[index + 1];
    }*/
    if (index < this->nodeList.size())
    {
        cout << n << " != " << this->nodeList[index]->N << endl;
    } else
    {
        cout << n << " is larger than all current nodes" << endl;
    }
    
    
    return NULL;
}

node nodes::copyFoundNode(int n) //binary search for gross but need to get working first
{
    int index = findSpot(n);
    if (index < this->nodeList.size() && this->nodeList[index]->N == n)
    {
        cout << n << " == " << this->nodeList[index]->N << endl;
        return *nodeList[index];
    } 
    /*else if (index + 1 < this->nodeList.size() && this->nodeList[index + 1]->N == n)
    {
        return nodeList[index + 1];
    }*/
    if (index < this->nodeList.size())
    {
        cout << n << " != " << this->nodeList[index]->N << endl;
    } else
    {
        cout << n << " is larger than all current nodes" << endl;
    }
    
    return NULL;
}

nodes::nodes(/* args */)
{
}

nodes::~nodes()
{
}

int   nodes::findSpot(int n) //not efficent, want to eventually make a binary search
{
    int index = 0;
    while (index < this->nodeList.size() && n > this->nodeList[index]->N)
    {
        index ++;
    }
    //if (n > this->nodeList[index]->N){index ++;}
    return index;
}

int nodes::getNode(string arg, int point)
{
    int node = 0;
    while (point < arg.size() && isdigit(arg[point]))
    {
        node = node * 10 + ((arg[point]) - '0');
        point ++;
    }
    return node;
}

path nodes::getPath(string arg)
{
    int open    = -1; //where in string { is
    int comma   = -1; //where in string , is
    int close   = -1; //where in string } is
    for (int scan = 0; scan < arg.size(); scan++)
    {
        switch (arg[scan])
        {
        case '{':
            if (open < 0) //make sure only first instance of bracket is used
            {
                open = scan;
            }
            break;
        case ',':
            comma = scan; //always last instance
            break;
        case '}':
            close = scan; //always last instance
        default:
            break;
        }
    }

    char state;
    int to      = -1;
    int index   = 0;
    if (comma > 0) //there is a non empty state 
    {
        //make sure state is properly formated
        if (open >= 0 && open != comma - 2) // if isn't { ,
        {
            ERROR("non empty state of more than char:" + arg.substr(open, open - comma + 1) + ":");
        } else if (open < 0 && comma != 1)
        {
            ERROR("non empty state of more than char:" + arg.substr(0, comma + 1) + ":");
        } else
        {
            state = arg[comma -1]; //set state
        }
        //set to node
        index = comma + 1;
    }else //empty state
    {
        index = 0;
    }
    while (index < arg.size() && arg[index] != 'n')
    {
        //cout << arg[index] << " !n: ";
        index++;
    }
    //cout << "!" << arg[index] << endl;
    if (index == arg.size() || arg[index] != 'n') //make sure start of node was found
    {
        ERROR("no node found in:" + arg.substr(comma + 1, arg.size() - comma) + ": point:" + arg[index] + ": index :" + to_string(index) + ":");
    }
    index ++; //move past n marker
    to = getNode(arg, index);
    //index + floor(log10(to) + 1);
    path addpath;
    addpath.state = state;
    node* node = this->findNode(to);
    if (node == NULL)       //if to node doesn't exist yet, make it
    {
        //cout << "creating node :" << to << endl; 
        node = this->addNode(to);
    }
    addpath.to = node;
    //cout << ":path: " << addpath.state << " -> " << addpath.to->N << endl;
    return addpath;
}