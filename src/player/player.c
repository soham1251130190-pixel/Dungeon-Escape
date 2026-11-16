#include <stdio.h>
#include <string.h>
#include "player.h"
#include "inventory.h"

// Initialize player with starting values: Health=100, Attack=20, Score=0, Room=0 (Entrance)
void initializePlayer(Player *player, const char *name) {
    if (player == NULL) return;
    
    // Strings handle character data for player name
    if (name != NULL && strlen(name) > 0) {
        strncpy(player->name, name, MAX_NAME_LEN - 1);
        player->name[MAX_NAME_LEN - 1] = '\0';
    } else {
        strncpy(player->name, "Hero", MAX_NAME_LEN - 1);
        player->name[MAX_NAME_LEN - 1] = '\0';
    }

    player->health = 100;
    player->maxHealth = 100;
    player->attack = 20;
    player->score = 0;
    player->currentRoom = 0;
    player->hasKey = 0;
    player->alive = 1;

    // Initialize Linked List Inventory
    initializeInventory(&player->inventory);
}

// Display player statistics in a clean terminal card
void displayPlayer(const Player *player) {
    if (player == NULL) return;

    printf("\n========================================\n");
    printf("             PLAYER STATS\n");
    printf("========================================\n");
    printf("  Name           : %s\n", player->name);
    printf("  Health         : %d / %d\n", player->health, player->maxHealth);
    printf("  Attack         : %d\n", player->attack);
    printf("  Score          : %d\n", player->score);
    printf("  Dungeon Key    : %s\n", player->hasKey ? "FOUND [YES]" : "NOT FOUND [NO]");
    printf("  Inventory Items: %d\n", player->inventory.count);
    printf("  Status         : %s\n", player->alive ? "Alive" : "Defeated");
    printf("========================================\n\n");
}

// Deal damage to player and check if player is defeated
void takeDamage(Player *player, int damage) {
    if (player == NULL || !player->alive) return;

    player->health -= damage;
    printf("[!] %s took %d damage! Remaining HP: %d\n", player->name, damage, player->health > 0 ? player->health : 0);

    if (player->health <= 0) {
        player->health = 0;
        player->alive = 0;
        printf("[X] %s has fallen in battle!\n", player->name);
    }
}

// Heal player without exceeding maximum health cap
void healPlayer(Player *player, int amount) {
    if (player == NULL || !player->alive) return;

    player->health += amount;
    if (player->health > player->maxHealth) {
        player->health = player->maxHealth;
    }
    printf("[+] %s recovered %d HP! Current HP: %d/%d\n", player->name, amount, player->health, player->maxHealth);
}

// Increment player score
void addScore(Player *player, int points) {
    if (player == NULL) return;

    player->score += points;
    printf("[*] +%d points! Total Score: %d\n", points, player->score);
}

// Check if player is alive
int isPlayerAlive(const Player *player) {
    if (player == NULL) return 0;
    return (player->alive && player->health > 0);
}

// Free player resources including dynamically allocated inventory
void freePlayer(Player *player) {
    if (player == NULL) return;
    freeInventory(&player->inventory);
}
