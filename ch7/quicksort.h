#ifndef QUICKSORT_H
#define QUICKSORT_H

int parition(int *arr, int low, int high);

// Randomized version of quicksort
int randParition(int *arr, int low, int high);

// Original quicksort by A. R. Hoare
int HoareParition(int *arr, int low, int high);
void HoareQuickSort(int *arr, int low, int high);

// My mod of Hoare version to use like other parition
int HoareParitionMod(int *arr, int low, int high);

// Use with other parition
void quickSort(int *arr, int low, int high,
               int (*howParition)(int *, int, int));

#endif
