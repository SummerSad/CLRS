#include "quicksort.h"
#include "share.h"

int parition(int *arr, int low, int high)
{
    int pivot = low;
    int i = low;
    for (int j = low + 1; j <= high; ++j)
    {
        if (arr[j] < arr[pivot])
        {
            // move value < arr[pivot] to the left
            // arr[i] now point to < arr[pivot]
            // but arr[i+1] is > arr[pivot]
            myswap(&arr[j], &arr[++i]);
        }
    }
    myswap(&arr[pivot], &arr[i]); // move pivot to the mid
    pivot = i;
    return pivot;
}

void quickSort(int *arr, int low, int high)
{
    if (low < high)
    {
        int pivot = parition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}
