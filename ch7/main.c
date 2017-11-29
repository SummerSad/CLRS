#include "quicksort.h"
#include "share.h"
#include <stdio.h>
#include <stdlib.h>

#define MYSIZE 5

int main()
{
    int size = MYSIZE;
    int *arr = (int *)malloc(sizeof(int) * size);
    randArr(arr, size);
    // printArr(arr, size);
    // quickSort(arr, 0, size - 1, HoareParitionMod);
    HoareQuickSort(arr, 0, size - 1);
    // int d = HoareParition(arr, 0, size - 1);
    // printf("%d\n", d);
    // printArr(arr, size);
    printf("%d\n", isSorted(arr, size));
    free(arr);
    return 0;
}
