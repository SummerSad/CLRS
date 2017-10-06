#include "share.h"
#include <stdlib.h>

#define MYSIZE 10

// Heap sort here I implement is max heap
// max heap is arr[parent(i)] >= arr[i]
void maxHeapify(int *arr, int size, int i);
void buildMaxHeap(int *arr, int size);
void maxHeapSort(int *arr, int size);

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

// check if arr[i] is violation heap or not
// if yes, we need to make arr[i] right order in heap
void maxHeapify(int *arr, int size, int i)
{
    int left = i * 2 + 1;
    if (left >= size) // overflow
        return;
    int right = i * 2 + 2;
    int max_child;
    if (left == size - 1) // only left child
        max_child = left;
    else
        max_child = arr[left] < arr[right] ? right : left;
    if (arr[i] < arr[max_child]) // arr[i] violation heap
    {
        myswap(&arr[i], &arr[max_child]);
        maxHeapify(arr, size, max_child); // recursive here
    }
}

// build heap array
void buildMaxHeap(int *arr, int size)
{
    // run from n/2 to 0 because arr[n/2+1..n] are leaves
    // leaves are good in heap
    for (int i = (size - 1) / 2; i >= 0; --i)
    {
        maxHeapify(arr, size, i);
    }
}

// combine evrything to make heap sort
void maxHeapSort(int *arr, int size)
{
    int i = size; // i: size->1
    do
    {
        buildMaxHeap(arr, i);
        myswap(&arr[0], &arr[--i]); // make max move to the end
        // and decrease heap size
    } while (i > 0);
}
