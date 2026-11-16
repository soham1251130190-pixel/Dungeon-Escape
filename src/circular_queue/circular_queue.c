#include <stdio.h>
#include <string.h>
#include "circular_queue.h"

// Initialize array-based circular queue
void initializeCircularQueue(CircularQueue *cq) {
    if (cq == NULL) return;
    cq->front = -1;
    cq->rear = -1;
    cq->count = 0;
}

// Check if circular queue is empty
int isCircularQueueEmpty(const CircularQueue *cq) {
    if (cq == NULL) return 1;
    return (cq->count == 0);
}

// Check if circular queue is full
int isCircularQueueFull(const CircularQueue *cq) {
    if (cq == NULL) return 0;
    return (cq->count == MAX_TURNS);
}

// Enqueue turn into circular queue using modulo arithmetic
int enqueueTurn(CircularQueue *cq, TurnEntity entity) {
    if (cq == NULL || isCircularQueueFull(cq)) {
        return 0; // Queue is full
    }

    if (cq->front == -1) {
        cq->front = 0;
    }

    cq->rear = (cq->rear + 1) % MAX_TURNS;
    cq->items[cq->rear] = entity;
    cq->count++;
    return 1;
}

// Dequeue turn from circular queue using modulo arithmetic
int dequeueTurn(CircularQueue *cq, TurnEntity *outEntity) {
    if (cq == NULL || isCircularQueueEmpty(cq)) {
        return 0; // Queue is empty
    }

    if (outEntity != NULL) {
        *outEntity = cq->items[cq->front];
    }

    if (cq->front == cq->rear) {
        // Only 1 item was present
        cq->front = -1;
        cq->rear = -1;
    } else {
        cq->front = (cq->front + 1) % MAX_TURNS;
    }

    cq->count--;
    return 1;
}

// Display circular queue turn ring
void displayTurns(const CircularQueue *cq) {
    printf("\n========================================\n");
    printf("       BATTLE TURNS (CIRCULAR QUEUE)\n");
    printf("========================================\n");

    if (cq == NULL || isCircularQueueEmpty(cq)) {
        printf("  No turns active.\n");
        printf("========================================\n\n");
        return;
    }

    printf("Turn Order (Wrap-Around Cycle):\n  ");
    int idx = cq->front;
    for (int i = 0; i < cq->count; i++) {
        printf("[%s]", cq->items[idx].name);
        if (i < cq->count - 1) printf(" -> ");
        idx = (idx + 1) % MAX_TURNS;
    }
    printf(" -> (wraps to start)\n");
    printf("========================================\n\n");
}
