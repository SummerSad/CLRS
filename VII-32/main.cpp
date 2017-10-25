#include "strmatch.h"
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    char T[] = "ababaca";
    char P[] = "ca";
    cout << naiveMatch(T, P) << endl;
    cout << dfaMatch(T, P) << endl;
    cout << kmpMatch(T, P) << endl;

    return 0;
}
