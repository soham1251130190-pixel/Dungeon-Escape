#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

// Initialize an empty stack
void initializeStack(Stack *stack) {
    if (stack == NULL) return;
    stack->top = NULL;
    stack->count = 0;
}

// Check if the stack is empty
int isStackEmpty(const Stack *stack) {
    if (stack == NULL) return 1;
    return (stack->top == NULL);
}

// Push a room onto the top of the stack (LIFO)
void push(Stack *stack, int roomId, const char *roomName) {
    if (stack == NULL) return;

    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed during stack push.\n");
        return;
    }

    newNode->roomId = roomId;
    if (roomName != NULL) {
        strncpy(newNode->roomName, roomName, MAX_ROOM_NAME_LEN - 1);
        newNode->roomName[MAX_ROOM_NAME_LEN - 1] = '\0';
    } else {
        strcpy(newNode->roomName, "Unknown Room");
    }

    // New node points to current top, then becomes the new top
    newNode->next = stack->top;
    stack->top = newNode;
    stack->count++;
}

// Pop the top room from the stack (LIFO)
int pop(Stack *stack, int *outRoomId, char *outRoomName) {
    if (stack == NULL || isStackEmpty(stack)) {
        return 0; // Stack underflow
    }

    StackNode *temp = stack->top;
    if (outRoomId != NULL) {
        *outRoomId = temp->roomId;
    }
    if (outRoomName != NULL) {
        strncpy(outRoomName, temp->roomName, MAX_ROOM_NAME_LEN - 1);
        outRoomName[MAX_ROOM_NAME_LEN - 1] = '\0';
    }

    stack->top = stack->top->next;
    free(temp);
    stack->count--;
    return 1;
}

// Peek at the top room without removing it
int peek(const Stack *stack, int *outRoomId, char *outRoomName) {
    if (stack == NULL || isStackEmpty(stack)) {
        return 0;
    }

    if (outRoomId != NULL) {
        *outRoomId = stack->top->roomId;
    }
    if (outRoomName != NULL) {
        strncpy(outRoomName, stack->top->roomName, MAX_ROOM_NAME_LEN - 1);
        outRoomName[MAX_ROOM_NAME_LEN - 1] = '\0';
    }
    return 1;
}

// Display the stack visually from TOP to BOTTOM for viva demonstration
void displayStack(const Stack *stack) {
    printf("\n========================================\n");
    printf("         MOVEMENT STACK (LIFO)\n");
    printf("========================================\n");

    if (stack == NULL || isStackEmpty(stack)) {
        printf("  Stack is empty. No previous moves recorded.\n");
        printf("  TOP -> [EMPTY]\n");
        printf("========================================\n\n");
        return;
    }

    printf("  TOP\n   |\n   v\n");
    StackNode *current = stack->top;
    int step = stack->count;
    while (current != NULL) {
        printf("  [%2d] %s (Room ID: %d)\n", step--, current->roomName, current->roomId);
        current = current->next;
    }
    printf("   |\n  BOTTOM\n");
    printf("  Total recorded moves: %d\n", stack->count);
    printf("========================================\n\n");
}

// Free all nodes in the stack
void freeStack(Stack *stack) {
    if (stack == NULL) return;

    StackNode *current = stack->top;
    while (current != NULL) {
        StackNode *temp = current;
        current = current->next;
        free(temp);
    }
    stack->top = NULL;
    stack->count = 0;
}
