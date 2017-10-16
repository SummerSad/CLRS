#include "quicksort.h"
#include "share.h"
#include <stdlib.h>

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
            return j;
        }
    }
}

void HoareQuickSort(int *arr, int low, int high)
{
    if (low < high)
    {
        int pivot = HoareParition(arr, low, high);
        HoareQuickSort(arr, low, pivot);
        HoareQuickSort(arr, pivot + 1, high);
    }
}
