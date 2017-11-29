#include "heapsort.h"
#include "priqueue.h"
#include "share.h"
#include <stdlib.h>

#define MYSIZE 10

int main()
{
    // rand a arr
    int size = MYSIZE;
    int *arr = (int *)malloc(sizeof(int) * size);
    randArr(arr, size);

    // test heap sort
    maxHeapSort(arr, size);
    printArr(arr, size);
    free(arr);
    return 0;
}
