#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#define MAX_TURNS 10
#define MAX_TURN_NAME_LEN 30

// Structure representing a participant in a combat turn
typedef struct {
    char name[MAX_TURN_NAME_LEN];
    int isPlayer;     // 1 if player, 0 if enemy
    int enemyIndex;   // index if enemy
} TurnEntity;

// Array-based Circular Queue structure
// Circular queue reuses array positions using modulo arithmetic for continuous turn cycles.
typedef struct {
    TurnEntity items[MAX_TURNS];
    int front;
    int rear;
    int count;
} CircularQueue;

// Function prototypes
void initializeCircularQueue(CircularQueue *cq);
int isCircularQueueEmpty(const CircularQueue *cq);
int isCircularQueueFull(const CircularQueue *cq);
int enqueueTurn(CircularQueue *cq, TurnEntity entity);
int dequeueTurn(CircularQueue *cq, TurnEntity *outEntity);
void displayTurns(const CircularQueue *cq);

#endif // CIRCULAR_QUEUE_H
