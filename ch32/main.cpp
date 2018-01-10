#include "strmatch.h"
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	char T[] = "xxxababxxaca";
	char P[] = "??a";
	cout << naiveMatchGap(T, P) << endl;
	cout << hpMatchGap(T, P) << endl;

	return 0;
}
