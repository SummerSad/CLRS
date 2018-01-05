#include "strmatch.h"
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	char T[] = "ababaca";
	char P[] = "???";
	cout << naiveMatchGap(T, P) << endl;
	cout << dfaMatch(T, P) << endl;
	cout << kmpMatch(T, P) << endl;
	cout << hpMatch(T, P) << endl;

	return 0;
}
