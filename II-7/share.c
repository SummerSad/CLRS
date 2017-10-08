#include "share.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANDMAX 1000

void myswap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArr(int *arr, int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void randArr(int *arr, int size)
{
    srand(time(NULL));
    for (int i = 0; i < size; ++i)
    {
        arr[i] = rand() % RANDMAX;
    }
}

int isSorted(int *arr, int size)
{
    if (size == 1)
        return 1;
    if (arr[size - 2] > arr[size - 1])
        return 0;
    return isSorted(arr, size - 1);
}
