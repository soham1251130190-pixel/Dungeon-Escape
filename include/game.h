#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "weapons.h"
#include "inventory.h"
#include "stack.h"
#include "binary_tree.h"
#include "graph.h"
#include "queue.h"
#include "circular_queue.h"
#include "heap.h"
#include "hashing.h"
#include "searching.h"
#include "sorting.h"
#include "leaderboard.h"

// Central Game Controller function prototypes
void startGame(void);
void showMainMenu(void);
void showInstructions(void);
void runGameLoop(Player *player, Leaderboard *leaderboard, HashTable *itemDb, TreeNode *dungeonTree);

#endif // GAME_H
