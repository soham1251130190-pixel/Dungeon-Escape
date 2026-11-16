#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

// Initialize an empty FIFO queue
void initializeQueue(Queue *q) {
    if (q == NULL) return;
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
}

// Check if queue is empty
int isQueueEmpty(const Queue *q) {
    if (q == NULL) return 1;
    return (q->front == NULL);
}

// Insert an enemy at the rear of the queue (FIFO)
void enqueue(Queue *q, Enemy enemy) {
    if (q == NULL) return;

    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        printf("Memory allocation failed for queue node.\n");
        return;
    }

    newNode->enemy = enemy;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->count++;
}

// Remove and retrieve the enemy from the front of the queue (FIFO)
int dequeue(Queue *q, Enemy *outEnemy) {
    if (q == NULL || isQueueEmpty(q)) {
        return 0; // Queue underflow
    }

    QueueNode *temp = q->front;
    if (outEnemy != NULL) {
        *outEnemy = temp->enemy;
    }

    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    q->count--;
    return 1;
}

// Peek at the enemy at the front of the queue without removing it
int peekQueue(const Queue *q, Enemy *outEnemy) {
    if (q == NULL || isQueueEmpty(q)) {
        return 0;
    }
    if (outEnemy != NULL) {
        *outEnemy = q->front->enemy;
    }
    return 1;
}

// Display visual queue representation for academic viva demonstration
void displayQueue(const Queue *q) {
    printf("\n========================================\n");
    printf("        ENEMY WAITING QUEUE (FIFO)\n");
    printf("========================================\n");

    if (q == NULL || isQueueEmpty(q)) {
        printf("  Queue is empty. No enemies waiting.\n");
        printf("  FRONT -> [EMPTY] <- REAR\n");
        printf("========================================\n\n");
        return;
    }

    printf("  FRONT -> ");
    QueueNode *curr = q->front;
    while (curr != NULL) {
        printf("[%s (HP:%d, ATK:%d)]", curr->enemy.name, curr->enemy.health, curr->enemy.attack);
        if (curr->next != NULL) printf(" -> ");
        curr = curr->next;
    }
    printf(" -> REAR\n");
    printf("  Total enemies in waiting queue: %d\n", q->count);
    printf("========================================\n\n");
}

// Free all allocated nodes in the queue
void freeQueue(Queue *q) {
    if (q == NULL) return;

    QueueNode *curr = q->front;
    while (curr != NULL) {
        QueueNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
}
