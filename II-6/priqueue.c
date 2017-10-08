#include "priqueue.h"
#include "heapsort.h"
#include "share.h"
#include <stdio.h>
#include <stdlib.h>

#define NEINF -1000000

int heapMax(Heap A) { return A.arr[0]; }

int heapExtractMax(Heap *A)
{
    if (A->size < 1)
        printf("Heap underflow\n");
    int max = A->arr[0];
    myswap(&A->arr[0], &A->arr[A->size - 1]);
    --A->size; // decrease heap size
    A->arr = (int *)realloc(A->arr, sizeof(int) * A->size);
    maxHeapifyIterate(A->arr, A->size, 0);
    return max;
}

void heapIncreaseKey(Heap A, int i, int key)
{
    if (key < A.arr[i])
    {
        printf("New key is smaller than current key\n");
        return;
    }
    A.arr[i] = key; // this may violate heap
    int child = i;
    int parent = (child - 1) / 2;
    while (parent >= 0)
    {
        if (A.arr[parent] >= A.arr[child]) // all good man
            break;
        myswap(&A.arr[parent], &A.arr[child]);
        child = parent;
        parent = (child - 1) / 2;
    }
}

void maxHeapInsert(Heap *A, int key)
{
    ++A->size;
    A->arr = (int *)realloc(A->arr, sizeof(int) * A->size);
    A->arr[A->size - 1] = NEINF;
    heapIncreaseKey(*A, A->size - 1, key);
}

Heap *initHeap()
{
    Heap *A = (Heap *)malloc(sizeof(Heap));
    A->arr = NULL;
    A->size = 0;
    return A;
}

void delHeap(Heap *A)
{
    free(A->arr);
    free(A);
    A->size = 0;
}
