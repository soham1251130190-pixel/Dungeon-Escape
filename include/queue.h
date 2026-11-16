#ifndef QUEUE_H
#define QUEUE_H

#define MAX_ENEMY_NAME_LEN 30

// Structure representing an enemy monster
typedef struct {
    char name[MAX_ENEMY_NAME_LEN];
    int health;
    int maxHealth;
    int attack;
    int priority;
    int scoreReward;
} Enemy;

// Node for singly linked list Queue implementation
// Queue follows FIFO (First-In, First-Out) for enemy waiting line.
typedef struct QueueNode {
    Enemy enemy;
    struct QueueNode *next;
} QueueNode;

// Queue wrapper structure
typedef struct {
    QueueNode *front;
    QueueNode *rear;
    int count;
} Queue;

// Function prototypes
void initializeQueue(Queue *q);
int isQueueEmpty(const Queue *q);
void enqueue(Queue *q, Enemy enemy);
int dequeue(Queue *q, Enemy *outEnemy);
int peekQueue(const Queue *q, Enemy *outEnemy);
void displayQueue(const Queue *q);
void freeQueue(Queue *q);

#endif // QUEUE_H
