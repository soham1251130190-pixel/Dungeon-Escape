#ifndef PLAYER_H
#define PLAYER_H

#include "inventory.h"

#define MAX_NAME_LEN 50

// Player structure to maintain player attributes throughout the dungeon
typedef struct {
    char name[MAX_NAME_LEN];
    int health;
    int maxHealth;
    int attack;
    int score;
    int currentRoom;
    int hasKey;
    int alive;
    Inventory inventory; // Linked List for dynamic item storage
} Player;

// Function prototypes
void initializePlayer(Player *player, const char *name);
void displayPlayer(const Player *player);
void takeDamage(Player *player, int damage);
void healPlayer(Player *player, int amount);
void addScore(Player *player, int points);
int isPlayerAlive(const Player *player);
void freePlayer(Player *player);

#endif // PLAYER_H
