#ifndef STACK_H
#define STACK_H

#define MAX_ROOM_NAME_LEN 50

// Node representing a room entry in the movement stack
// Stack follows LIFO (Last-In, First-Out) principle for undoing moves.
typedef struct StackNode {
    int roomId;
    char roomName[MAX_ROOM_NAME_LEN];
    struct StackNode *next;
} StackNode;

// Stack wrapper structure
typedef struct {
    StackNode *top;
    int count;
} Stack;

// Function prototypes
void initializeStack(Stack *stack);
int isStackEmpty(const Stack *stack);
void push(Stack *stack, int roomId, const char *roomName);
int pop(Stack *stack, int *outRoomId, char *outRoomName);
int peek(const Stack *stack, int *outRoomId, char *outRoomName);
void displayStack(const Stack *stack);
void freeStack(Stack *stack);

#endif // STACK_H
