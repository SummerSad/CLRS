#include "share.h"

//  My implement of max priority queue
//  It's based on heap data structures
//  It's used for share work, after done we extractMax
//  and go to work with their relatives
typedef struct Heap
{
    int *arr;
    int size;
} Heap;

int heapMax(Heap A);
int heapExtractMax(Heap *A);
void heapIncreaseKey(Heap A, int i, int key); // change A[i] to key
void maxHeapInsert(Heap *A, int key);
Heap *initHeap();
void delHeap(Heap *A);
