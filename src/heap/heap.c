#include <stdio.h>
#include "heap.h"

// Swap two enemy elements
static void swapEnemy(Enemy *a, Enemy *b) {
    Enemy temp = *a;
    *a = *b;
    *b = temp;
}

// Initialize empty Max Heap
void initializeHeap(MaxHeap *heap) {
    if (heap == NULL) return;
    heap->size = 0;
}

// Check if heap is empty
int isHeapEmpty(const MaxHeap *heap) {
    if (heap == NULL) return 1;
    return (heap->size == 0);
}

// Check if heap is full
int isHeapFull(const MaxHeap *heap) {
    if (heap == NULL) return 0;
    return (heap->size >= MAX_HEAP_SIZE);
}

// Insert an enemy into the max heap (sift-up by attack power)
void insertHeap(MaxHeap *heap, Enemy enemy) {
    if (heap == NULL || isHeapFull(heap)) {
        printf("Max Heap is full. Cannot insert enemy.\n");
        return;
    }

    int current = heap->size;
    heap->elements[current] = enemy;
    heap->size++;

    // Sift up: child compares with parent (parent = (current - 1) / 2)
    while (current > 0) {
        int parent = (current - 1) / 2;
        if (heap->elements[current].attack > heap->elements[parent].attack) {
            swapEnemy(&heap->elements[current], &heap->elements[parent]);
            current = parent;
        } else {
            break;
        }
    }
}

// Down-heapify to maintain max heap property after root removal
void heapify(MaxHeap *heap, int index) {
    if (heap == NULL) return;

    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->elements[left].attack > heap->elements[largest].attack) {
        largest = left;
    }

    if (right < heap->size && heap->elements[right].attack > heap->elements[largest].attack) {
        largest = right;
    }

    if (largest != index) {
        swapEnemy(&heap->elements[index], &heap->elements[largest]);
        heapify(heap, largest);
    }
}

// Remove the root (strongest enemy with maximum attack)
int removeMax(MaxHeap *heap, Enemy *outEnemy) {
    if (heap == NULL || isHeapEmpty(heap)) {
        return 0; // Heap underflow
    }

    if (outEnemy != NULL) {
        *outEnemy = heap->elements[0];
    }

    heap->elements[0] = heap->elements[heap->size - 1];
    heap->size--;

    if (heap->size > 0) {
        heapify(heap, 0);
    }

    return 1;
}

// Peek at the highest priority enemy at root without removing
int peekMax(const MaxHeap *heap, Enemy *outEnemy) {
    if (heap == NULL || isHeapEmpty(heap)) {
        return 0;
    }
    if (outEnemy != NULL) {
        *outEnemy = heap->elements[0];
    }
    return 1;
}

// Display max heap elements and structure for academic demonstration
void displayHeap(const MaxHeap *heap) {
    printf("\n========================================\n");
    printf("        ENEMY MAX HEAP (PRIORITY)\n");
    printf("========================================\n");

    if (heap == NULL || isHeapEmpty(heap)) {
        printf("  Heap is empty.\n");
        printf("========================================\n\n");
        return;
    }

    printf("Array Representation:\n");
    for (int i = 0; i < heap->size; i++) {
        printf("  [%d] %-14s (ATK: %d, HP: %d)\n", i, heap->elements[i].name, heap->elements[i].attack, heap->elements[i].health);
    }

    printf("\nHeap Priority Order (Root = Top Threat):\n");
    for (int i = 0; i < heap->size; i++) {
        int parent = (i - 1) / 2;
        if (i == 0) {
            printf("  Root -> %s (%d ATK)\n", heap->elements[i].name, heap->elements[i].attack);
        } else {
            printf("  Child of [%s] -> %s (%d ATK)\n", heap->elements[parent].name, heap->elements[i].name, heap->elements[i].attack);
        }
    }
    printf("========================================\n\n");
}

// Clean up heap
void freeHeap(MaxHeap *heap) {
    if (heap == NULL) return;
    heap->size = 0;
}
