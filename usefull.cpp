#include "usefull.h"
using namespace std;
void ERROR(string err)
{
    cout << endl << "**********************************" << endl << "ERROR:" << err << endl << "**********************************" << endl;
    throw(err);
}