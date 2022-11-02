#ifndef NODES_H
#define NODES_H
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "node.h"
//#include "usefull.cpp"
    using namespace std;
    
    class nodes
    {
    private:
        int   findSpot(node*);
    public:
        vector<node*> nodeList;
        nodes();
        ~nodes();
        int addNode(node*);
        node* addNode(int n);
        node* addNode(string, int index);
        node* findNode(int n);
        node copyFoundNode(int n);
        void addPath(int index, string path);
        int findSpot(int n);
        int getNode(string arg, int point);
        path getPath(string arg);
    };
#endif