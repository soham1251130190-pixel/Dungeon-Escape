#ifndef HEAP_H
#define HEAP_H

#include "queue.h"

#define MAX_HEAP_SIZE 20

// Max Heap structure for enemy attack priority
// Max heap gives highest attack enemy top priority at the root.
typedef struct {
    Enemy elements[MAX_HEAP_SIZE];
    int size;
} MaxHeap;

// Function prototypes
void initializeHeap(MaxHeap *heap);
int isHeapEmpty(const MaxHeap *heap);
int isHeapFull(const MaxHeap *heap);
void insertHeap(MaxHeap *heap, Enemy enemy);
int removeMax(MaxHeap *heap, Enemy *outEnemy);
int peekMax(const MaxHeap *heap, Enemy *outEnemy);
void heapify(MaxHeap *heap, int index);
void displayHeap(const MaxHeap *heap);
void freeHeap(MaxHeap *heap);

#endif // HEAP_H
