#include "node.h"
using namespace std;


/*class node
{
private:
public:
    vector<struct path> paths;
    int N;
    int index;
    node(int N);
    node(string arg, int argIndex);
    ~node();
    void setIndex(int index);
    void addPath(struct path);
    void addPath(string);
    int getNode(string, int argIndex);
    path getPath(string arg);
};*/

/*
struct path
{
    char state;
    node* to;
};*/

int node::getNode(string arg, int index)
{
    int node = 0;
    while (index < arg.size() && isdigit(arg[index]))
    {
        node = node * 10 + ((arg[index]) - '0');
        index ++;
    }
    return node;
}

void node::addPath(path newpath)
{
    this->paths.push_back(newpath);
}
void node::setIndex(int index)
{
    this->index = index;
}

node::node(string arg, int index)
{
    this->N = getNode(arg, index);
}

node::node(int N)
{
    this->N = N;
}

node::~node()
{
}

/* code moved to nodes imp
void node::addPath(string arg)
{
    this->paths.push_back(getPath(arg));
}
path node::getPath(string arg)
{
    //cout << "making path from :" << arg << ":" << endl;
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
    node* node = NODES.findNode(to);
    if (node == NULL)       //if to node doesn't exist yet, make it
    {
        //cout << "creating node :" << to << endl; 
        node = NODES.addNode(to);
    }
    addpath.to = node;
    //cout << ":path: " << addpath.state << " -> " << addpath.to->N << endl;
    return addpath;
    
}*/

