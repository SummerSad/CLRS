#include "strmatch.h"
#include <string.h>

int naiveMatch(const char *T, const char *P)
{
    int n = strlen(T);
    int m = strlen(P);
    for (int i = 0; i <= n - m; ++i)
    {
        bool match = true; // reset for each match
        for (int j = 0; j < m; ++j)
        {
            if (P[j] != T[j + i]) // 1 error is enough
            {
                match = false;
                break;
            }
        }
        if (match == true)
            return i;
    }
    return -1;
}
