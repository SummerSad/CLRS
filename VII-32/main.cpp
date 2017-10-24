#include "strmatch.h"
#include <iostream>
using namespace std;

int main()
{
    char T[] = "abdcdababcd";
    char P[] = "bcd";
    cout << naiveMatch(T, P) << endl;
    cout << dfaMatch(T, P) << endl;
    return 0;
}
