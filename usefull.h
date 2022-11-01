#ifndef USEFULL_H
#define USEFULL_H
#include <string>
#include <iostream>
using namespace std;
void ERROR(string err = "undefined error")
{
    cout << endl << "**********************************" << endl << "ERROR:" << err << endl << "**********************************" << endl;
    throw(err);
}
#endif