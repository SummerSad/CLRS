#include "heapsort.h"
#include "share.h"
#include <stdlib.h>

// check if arr[i] is violation heap or not
// if yes, we need to make arr[i] right order in heap
// *we have an assumption that arr[i+1..size-1] is already heap
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

// build heap array with above assumption
void buildMaxHeap(int *arr, int size)
{
    // run from n/2 to 0 because arr[n/2+1..n] are leaves
    // leaves are good in heap
    for (int i = (size - 1) / 2; i >= 0; --i)
    {
        // maxHeapify(arr, size, i);
        maxHeapifyIterate(arr, size, i);
    }
}

void maxHeapSort(int *arr, int size)
{
    buildMaxHeap(arr, size);
    int i = size;
    while (i > 0)
    {
        myswap(&arr[0], &arr[--i]); // make max move to the end
        // maxHeapify(arr, i, 0);      // make arr[0] is max
        maxHeapifyIterate(arr, i, 0);
    }
}

// no recursive
void maxHeapifyIterate(int *arr, int size, int i)
{
    int parent = i;
    int child = parent * 2 + 1;
    while (child < size)
    {
        if (child != size - 1) // have child and child+1
            child = arr[child] > arr[child + 1] ? child : child + 1;
        if (arr[parent] >= arr[child]) // already heap
            break;
        myswap(&arr[parent], &arr[child]);
        parent = child;
        child = parent * 2 + 1;
    }
}
