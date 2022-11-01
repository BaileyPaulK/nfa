#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
//#include "path.h"
#include "usefull.h"
    using namespace std;
    class node
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
        struct path getPath(string arg);
    };
    
    struct path
    {
        char state;
        node* to;
    };
#endif