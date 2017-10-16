#ifndef QUICKSORT_H
#define QUICKSORT_H

int parition(int *arr, int low, int high);
// Randomized version of quicksort
int randParition(int *arr, int low, int high);
// Original quicksort by A. R. Hoare
int HoareParition(int *arr, int low, int high);

void quickSort(int *arr, int low, int high, int (*howParition)(int *, int, int));

#endif
