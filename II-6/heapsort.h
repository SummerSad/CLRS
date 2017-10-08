#ifndef HEAPSORT_H
#define HEAPSORT_H

// Heap sort here I implement is max heap
// max heap is arr[parent(i)] >= arr[i]
void maxHeapify(int *arr, int size, int i);
void buildMaxHeap(int *arr, int size);
void maxHeapSort(int *arr, int size);

// no recursive
void maxHeapifyIterate(int *arr, int size, int i);

#endif
