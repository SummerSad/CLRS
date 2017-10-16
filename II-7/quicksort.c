#include "quicksort.h"
#include "share.h"
#include <stdlib.h>

// Make pivot in right location
// low..pivot-1 < pivot < pivot+1..high
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

void quickSort(int *arr, int low, int high, int (*howParition)(int *, int, int))
{
    if (low < high)
    {
        int pivot = howParition(arr, low, high);
        // Because pivot is right place, we ignore it
        quickSort(arr, low, pivot - 1, howParition);
        quickSort(arr, pivot + 1, high, howParition);
    }
}

int randParition(int *arr, int low, int high)
{
    int randPivot = low + rand() % (high - low + 1);
    myswap(&arr[low], &arr[randPivot]);
    return parition(arr, low, high);
}

int HoareParitionMod(int *arr, int low, int high)
{
    int x = arr[low];
    int i = low;
    int j = high + 1;
    while (1)
    {
        do
        {
            --j;
        } while (arr[j] > x); // stop when arr[j]<=x
        do
        {
            ++i;
        } while (arr[i] < x); // stop when arr[i]>=x
        if (i < j)
        {
            myswap(&arr[i], &arr[j]);
        }
        else
        {
            // low..j..i..high
            myswap(&arr[low], &arr[j]);
            return j;
        }
    }
}

// Hoare original idea is not divide arr surround pivot,
// He divie 2 subarr, the left is < the right
// But our idea is more: we have a pivot.
// The left < pivot < the right
int HoareParition(int *arr, int low, int high)
{
    int x = arr[low];
    int i = low - 1;
    int j = high + 1;
    while (1)
    {
        do
        {
            --j;
        } while (arr[j] > x); // Stop when arr[j]<=x
        do
        {
            ++i;
        } while (arr[i] < x); // Stop when arr[i]>=x
        if (i < j)
        {
            myswap(&arr[i], &arr[j]);
        }
        else
        {
            return j;
        }
    }
}

void HoareQuickSort(int *arr, int low, int high)
{
    if (low < high)
    {
        int pivot = HoareParition(arr, low, high);
        // Because we have 2 subarr, the left < the right
        // We continue to recursive to 2 subarr
        HoareQuickSort(arr, low, pivot);
        HoareQuickSort(arr, pivot + 1, high);
    }
}
