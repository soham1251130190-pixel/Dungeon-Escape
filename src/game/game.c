#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

// Helper function to safely read an integer from standard input
static int getIntInput(void) {
    int choice = -1;
    char buffer[64];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (sscanf(buffer, "%d", &choice) != 1) {
            return -1;
        }
        return choice;
    }
    // Return sentinel on EOF
    return -999;
}

// Helper function to safely read a string from standard input
static void getStringInput(char *dest, int maxLen) {
    if (dest == NULL || maxLen <= 0) return;
    if (fgets(dest, maxLen, stdin) != NULL) {
        size_t len = strlen(dest);
        if (len > 0 && dest[len - 1] == '\n') {
            dest[len - 1] = '\0';
        }
    } else {
        dest[0] = '\0';
    }
}

// Display game instructions and data structure overview
void showInstructions(void) {
    printf("\n========================================================\n");
    printf("              DUNGEON ESCAPE - INSTRUCTIONS\n");
    printf("========================================================\n");
    printf(" Objective:\n");
    printf("   1. Explore the connected dungeon rooms using the Graph.\n");
    printf("   2. Find items & weapons stored in your Linked List inventory.\n");
    printf("   3. Defeat dangerous enemies in turn-based combat using\n");
    printf("      Queue (waiting line), Max Heap (priority), & Circular Queue (turns).\n");
    printf("   4. Locate the Dungeon Key in the Treasure Room.\n");
    printf("   5. Navigate through the Boss Room to reach the Exit.\n");
    printf("   6. Escape with the highest score and save to the Leaderboard!\n\n");
    printf(" Data Structures Implemented in this Project:\n");
    printf("   - Array          : Weapon Arsenal Database & Leaderboard records\n");
    printf("   - Strings        : Player, item, room, and enemy names\n");
    printf("   - Linked List    : Dynamic Player Inventory\n");
    printf("   - Stack          : Undo Movement History (LIFO)\n");
    printf("   - Queue          : Enemy Battle Waiting Line (FIFO)\n");
    printf("   - Circular Queue : Turn-Based Combat Rotation Ring\n");
    printf("   - Max Heap       : Enemy Threat & Attack Priority\n");
    printf("   - Binary Tree    : Hierarchical Dungeon Layout\n");
    printf("   - Graph          : Room Connectivity Network (Adjacency List)\n");
    printf("   - Hashing        : Fast Item Encyclopedia Lookup (Chaining)\n");
    printf("   - Linear Search  : Inventory and list item search\n");
    printf("   - Binary Search  : O(log n) Weapon search on sorted array\n");
    printf("   - Sorting        : Manual Bubble / Selection / Insertion Sort\n");
    printf("   - Recursion      : Tree Traversals & Depth-First Search (DFS)\n");
    printf("========================================================\n\n");
}

// Display main menu
void showMainMenu(void) {
    printf("\n========================================\n");
    printf("           DUNGEON ESCAPE\n");
    printf("========================================\n");
    printf("1. Start Game\n");
    printf("2. Instructions\n");
    printf("3. Leaderboard\n");
    printf("4. Exit\n");
    printf("----------------------------------------\n");
    printf("Enter choice: ");
}

// Display Game HUD Header
static void displayGameMenuHeader(const Player *player, const Graph *g) {
    printf("\n========================================\n");
    printf("              GAME MENU\n");
    printf("========================================\n");
    printf("Player: %-14s  Health : %d / %d\n", player->name, player->health, player->maxHealth);
    printf("Attack: %-14d  Score  : %d\n", player->attack, player->score);
    printf("Room  : [%d] %-10s Key    : %s\n", player->currentRoom,
           getRoomNameById(g, player->currentRoom),
           player->hasKey ? "FOUND [YES]" : "NOT FOUND [NO]");
    printf("----------------------------------------\n");
    printf("1. Move\n");
    printf("2. Explore Dungeon\n");
    printf("3. Show Inventory\n");
    printf("4. Pick / Use Item\n");
    printf("5. Search Item\n");
    printf("6. Search Weapon\n");
    printf("7. Fight Enemy\n");
    printf("8. Undo Last Move\n");
    printf("9. Find Shortest Path\n");
    printf("10. Show Dungeon Graph\n");
    printf("11. Show Dungeon Tree\n");
    printf("12. Show Leaderboard\n");
    printf("13. Player Stats\n");
    printf("0. Quit Game\n");
    printf("----------------------------------------\n");
    printf("Enter choice: ");
}

// Handle Room Exploration & Recursive Traversals
static void handleExploreDungeon(const TreeNode *dungeonTree, const Graph *graph, int currentRoom) {
    printf("\n========================================\n");
    printf("      DUNGEON EXPLORATION (RECURSION)\n");
    printf("========================================\n");
    printf("1. Preorder Traversal  (Root -> Left -> Right)\n");
    printf("2. Inorder Traversal   (Left -> Root -> Right)\n");
    printf("3. Postorder Traversal (Left -> Right -> Root)\n");
    printf("4. Recursive DFS Search (Reachable Graph Rooms)\n");
    printf("0. Back to Game Menu\n");
    printf("----------------------------------------\n");
    printf("Enter choice: ");

    int choice = getIntInput();
    switch (choice) {
        case 1:
            printf("\n[Recursion] Binary Tree Preorder Traversal:\n");
            preorderTraversal(dungeonTree);
            printf("\n\n");
            break;
        case 2:
            printf("\n[Recursion] Binary Tree Inorder Traversal:\n");
            inorderTraversal(dungeonTree);
            printf("\n\n");
            break;
        case 3:
            printf("\n[Recursion] Binary Tree Postorder Traversal:\n");
            postorderTraversal(dungeonTree);
            printf("\n\n");
            break;
        case 4:
            // Recursive Depth-First Search on Graph
            DFS(graph, currentRoom);
            break;
        case 0:
            break;
        default:
            printf("[!] Invalid traversal choice.\n");
            break;
    }
}

// Handle Combat Demonstration using Queue, Max Heap, and Circular Queue
static void handleCombat(Player *player) {
    printf("\n================================================\n");
    printf("            ENTERING DUNGEON COMBAT\n");
    printf("================================================\n");

    // 1. Initialize FIFO Queue for waiting enemies
    Queue enemyQueue;
    initializeQueue(&enemyQueue);

    Enemy goblin = {"Goblin", 30, 30, 20, 1, 50};
    Enemy orc = {"Orc Warrior", 60, 60, 50, 2, 100};
    Enemy dragon = {"Dungeon Dragon", 120, 120, 80, 3, 200};

    enqueue(&enemyQueue, goblin);
    enqueue(&enemyQueue, orc);
    enqueue(&enemyQueue, dragon);

    printf("[1/3] Enemies Enqueued into Waiting Line (Queue - FIFO):\n");
    displayQueue(&enemyQueue);

    // 2. Initialize Max Heap to determine enemy threat / attack priority
    MaxHeap priorityHeap;
    initializeHeap(&priorityHeap);

    insertHeap(&priorityHeap, goblin);
    insertHeap(&priorityHeap, orc);
    insertHeap(&priorityHeap, dragon);

    printf("[2/3] Enemies Inserted into Max Heap (Priority based on Attack):\n");
    displayHeap(&priorityHeap);

    // 3. Initialize Circular Queue for Turn Rotation
    CircularQueue turnQueue;
    initializeCircularQueue(&turnQueue);

    TurnEntity pTurn;
    strncpy(pTurn.name, player->name, MAX_TURN_NAME_LEN - 1);
    pTurn.name[MAX_TURN_NAME_LEN - 1] = '\0';
    pTurn.isPlayer = 1;
    pTurn.enemyIndex = 0;

    TurnEntity eTurn1;
    strncpy(eTurn1.name, dragon.name, MAX_TURN_NAME_LEN - 1);
    eTurn1.name[MAX_TURN_NAME_LEN - 1] = '\0';
    eTurn1.isPlayer = 0;
    eTurn1.enemyIndex = 1;

    TurnEntity eTurn2;
    strncpy(eTurn2.name, orc.name, MAX_TURN_NAME_LEN - 1);
    eTurn2.name[MAX_TURN_NAME_LEN - 1] = '\0';
    eTurn2.isPlayer = 0;
    eTurn2.enemyIndex = 2;

    TurnEntity eTurn3;
    strncpy(eTurn3.name, goblin.name, MAX_TURN_NAME_LEN - 1);
    eTurn3.name[MAX_TURN_NAME_LEN - 1] = '\0';
    eTurn3.isPlayer = 0;
    eTurn3.enemyIndex = 3;

    enqueueTurn(&turnQueue, pTurn);
    enqueueTurn(&turnQueue, eTurn1);
    enqueueTurn(&turnQueue, eTurn2);
    enqueueTurn(&turnQueue, eTurn3);

    printf("[3/3] Combat Turn Rotation Initialized (Circular Queue):\n");
    displayTurns(&turnQueue);

    // Active Combat Loop against top threat from Max Heap
    Enemy activeEnemy;
    removeMax(&priorityHeap, &activeEnemy);

    printf("\n>>> Top Priority Threat Selected: %s (HP: %d, ATK: %d) <<<\n",
           activeEnemy.name, activeEnemy.health, activeEnemy.attack);

    int inBattle = 1;
    while (inBattle && isPlayerAlive(player) && activeEnemy.health > 0) {
        printf("\n----------------------------------------\n");
        printf(" BATTLE: %s (HP: %d) vs %s (HP: %d)\n",
               player->name, player->health, activeEnemy.name, activeEnemy.health);
        printf("----------------------------------------\n");
        printf("1. Attack\n");
        printf("2. Use Health Potion\n");
        printf("3. View Inventory\n");
        printf("4. Show Battle Data Structures\n");
        printf("5. Flee Combat\n");
        printf("Enter choice: ");

        int bChoice = getIntInput();
        switch (bChoice) {
            case 1: {
                // Player attacks active enemy
                int damageDealt = player->attack;
                activeEnemy.health -= damageDealt;
                printf("\n[*] You struck %s for %d damage!\n", activeEnemy.name, damageDealt);

                if (activeEnemy.health <= 0) {
                    activeEnemy.health = 0;
                    printf("\n[+] Victory! %s was defeated!\n", activeEnemy.name);
                    addScore(player, activeEnemy.scoreReward);

                    // Check if another enemy is in the priority heap
                    if (!isHeapEmpty(&priorityHeap)) {
                        removeMax(&priorityHeap, &activeEnemy);
                        printf("\n>>> Next Highest Threat Steps Up: %s (HP: %d, ATK: %d) <<<\n",
                               activeEnemy.name, activeEnemy.health, activeEnemy.attack);
                    } else {
                        printf("\n[***] All dungeon monsters in this encounter defeated! [***]\n");
                        inBattle = 0;
                        break;
                    }
                }

                // Enemy counter-attacks if still alive
                if (activeEnemy.health > 0) {
                    takeDamage(player, activeEnemy.attack);
                    if (!isPlayerAlive(player)) {
                        inBattle = 0;
                    }
                }
                break;
            }
            case 2: {
                ItemNode *potion = searchItem(&player->inventory, "Health Potion");
                if (potion != NULL) {
                    healPlayer(player, potion->value);
                    removeItem(&player->inventory, "Health Potion");
                } else {
                    printf("[!] No Health Potion in inventory!\n");
                }
                break;
            }
            case 3:
                displayInventory(&player->inventory);
                break;
            case 4:
                displayQueue(&enemyQueue);
                displayHeap(&priorityHeap);
                displayTurns(&turnQueue);
                break;
            case 5:
                printf("\n[*] You tactically retreated from combat!\n");
                inBattle = 0;
                break;
            default:
                printf("[!] Invalid battle action.\n");
                break;
        }
    }

    freeQueue(&enemyQueue);
    freeHeap(&priorityHeap);
}

// Handle Movement across dungeon rooms using Graph and Stack
static void handleMove(Player *player, Graph *graph, Stack *movementStack) {
    if (graph == NULL || player == NULL) return;

    printf("\nAvailable paths from [%d] %s:\n", player->currentRoom, graph->rooms[player->currentRoom].name);
    AdjListNode *curr = graph->rooms[player->currentRoom].head;
    int options[MAX_ROOMS];
    int count = 0;

    while (curr != NULL) {
        options[count] = curr->dest;
        printf("  %d. Move to %s (Room ID: %d)\n", count + 1, graph->rooms[curr->dest].name, curr->dest);
        count++;
        curr = curr->next;
    }
    printf("  0. Stay in current room\n");
    printf("Enter choice (1-%d, or Room ID): ", count);
    int choice = getIntInput();

    if (choice == 0) {
        printf("[*] You remain in %s.\n", getRoomNameById(graph, player->currentRoom));
        return;
    }

    int targetRoom = -1;
    if (choice >= 1 && choice <= count) {
        targetRoom = options[choice - 1];
    } else if (isValidMove(graph, player->currentRoom, choice)) {
        targetRoom = choice;
    } else {
        printf("[!] Invalid choice. Move cancelled.\n");
        return;
    }

    // Push previous room to Stack (LIFO)
    push(movementStack, player->currentRoom, getRoomNameById(graph, player->currentRoom));

    // Update room
    player->currentRoom = targetRoom;
    printf("\n[Move] You walked into: [%d] %s\n", player->currentRoom, getRoomNameById(graph, player->currentRoom));
    printf("       \"%s\"\n", graph->rooms[player->currentRoom].description);

    // Trigger room specific events
    switch (player->currentRoom) {
        case 1: // Armory
            if (graph->rooms[1].hasItem) {
                printf("\n[Event] You found a tempered Knightly Sword in the armory!\n");
                addItem(&player->inventory, "Sword", ITEM_WEAPON, 50);
                graph->rooms[1].hasItem = 0;
            }
            break;
        case 2: // Library
            printf("\n[Event] Ancient inscriptions reveal: \"The Key is sealed in the Treasure Room; the Exit lies past the Dragon's lair!\"\n");
            break;
        case 4: // Potion Room
            if (graph->rooms[4].hasItem) {
                printf("\n[Event] You found a restorative Health Potion on the alchemy desk!\n");
                addItem(&player->inventory, "Health Potion", ITEM_POTION, 50);
                graph->rooms[4].hasItem = 0;
            }
            break;
        case 5: // Monster Room
            if (graph->rooms[5].hasEnemy) {
                printf("\n[Event] Dangerous monsters ambush you in the Monster Room!\n");
                handleCombat(player);
                graph->rooms[5].hasEnemy = 0;
            }
            break;
        case 6: // Treasure Room
            if (graph->rooms[6].hasItem) {
                printf("\n[Event] You unlocked the ornate golden chest!\n");
                addItem(&player->inventory, "Dungeon Key", ITEM_KEY, 0);
                addItem(&player->inventory, "Gold Treasure", ITEM_TREASURE, 100);
                player->hasKey = 1;
                addScore(player, 250);
                printf("[*] Acquired the Dungeon Key (+150 pts) and Gold Treasure (+100 pts)!\n");
                graph->rooms[6].hasItem = 0;
            }
            break;
        case 7: // Boss Room
            if (graph->rooms[7].hasEnemy) {
                printf("\n[Event] The mighty Dungeon Dragon descends from the cavern ceiling!\n");
                handleCombat(player);
                graph->rooms[7].hasEnemy = 0;
            }
            break;
        case 8: // Exit Room
            if (player->hasKey) {
                printf("\n========================================\n");
                printf("             YOU ESCAPED!\n");
                printf("========================================\n");
                printf("Player: %s\n", player->name);
                addScore(player, 500);
                printf("Escaped the Dungeon successfully! Final Score: %d\n", player->score);
                printf("========================================\n\n");
            } else {
                printf("\n[!] The Exit is locked! You need the Dungeon Key to escape.\n");
                printf("    (Hint: Search the Treasure Room [ID: 6] to find the Key)\n");
            }
            break;
        default:
            break;
    }
}

// Handle Undo Last Move via Stack (LIFO)
static void handleUndo(Player *player, Stack *movementStack, const Graph *graph) {
    if (isStackEmpty(movementStack)) {
        printf("\n========================================\n");
        printf("         UNDO MOVE (STACK)\n");
        printf("========================================\n");
        printf("  Stack Underflow: No previous moves to undo!\n");
        printf("========================================\n\n");
        return;
    }

    int prevRoomId;
    char prevRoomName[MAX_ROOM_NAME_LEN];
    if (pop(movementStack, &prevRoomId, prevRoomName)) {
        printf("\n========================================\n");
        printf("         UNDO MOVE (STACK - LIFO)\n");
        printf("========================================\n");
        printf("  Popped Previous Room: [%d] %s\n", prevRoomId, prevRoomName);
        player->currentRoom = prevRoomId;
        printf("  Player successfully returned to %s (Room ID: %d)\n",
               getRoomNameById(graph, player->currentRoom), player->currentRoom);
        printf("========================================\n\n");
    }
}

// Handle Item Lookup via Hash Table with Separate Chaining
static void handleItemSearch(const HashTable *itemDb) {
    printf("\n========================================\n");
    printf("      SEARCH ITEM (HASH TABLE)\n");
    printf("========================================\n");
    printf("1. Search Item by Name\n");
    printf("2. Display Entire Hash Table Structure\n");
    printf("0. Back to Game Menu\n");
    printf("----------------------------------------\n");
    printf("Enter choice: ");

    int choice = getIntInput();
    switch (choice) {
        case 1: {
            char searchName[MAX_HASH_STR_LEN];
            printf("Enter item name to search (e.g. Sword, Potion, Key, Bow): ");
            getStringInput(searchName, sizeof(searchName));

            HashNode *found = searchHash(itemDb, searchName);
            if (found != NULL) {
                printf("\n========================================\n");
                printf("           ITEM DETAILS\n");
                printf("========================================\n");
                printf("  Name       : %s\n", found->name);
                printf("  Type       : %s\n", found->type);
                printf("  Value      : +%d\n", found->value);
                printf("  Description: %s\n", found->description);
                printf("========================================\n\n");
            }
            break;
        }
        case 2:
            displayHashTable(itemDb);
            break;
        case 0:
            break;
        default:
            printf("[!] Invalid choice.\n");
            break;
    }
}

// Handle Weapon Search via Binary Search on Sorted Array
static void handleWeaponSearch(void) {
    printf("\n========================================\n");
    printf("      SEARCH WEAPON (BINARY SEARCH)\n");
    printf("========================================\n");
    printf("1. Search Weapon by Attack Power (Binary Search)\n");
    printf("2. View All Weapons in Arsenal (Array)\n");
    printf("0. Back to Game Menu\n");
    printf("----------------------------------------\n");
    printf("Enter choice: ");

    int choice = getIntInput();
    switch (choice) {
        case 1: {
            int targetAttack;
            printf("Enter weapon attack value to search (e.g. 15, 25, 40, 50, 70, 100): ");
            targetAttack = getIntInput();

            Weapon weaponsArray[MAX_WEAPONS];
            for (int i = 0; i < MAX_WEAPONS; i++) {
                weaponsArray[i] = *getWeapon(i);
            }

            binarySearchWeaponByAttack(weaponsArray, MAX_WEAPONS, targetAttack);
            break;
        }
        case 2:
            displayWeapons();
            break;
        case 0:
            break;
        default:
            printf("[!] Invalid choice.\n");
            break;
    }
}

// Submenu for item picking and item usage
static void handleItemSubmenu(Player *player) {
    printf("\n========================================\n");
    printf("           ITEM MANAGEMENT\n");
    printf("========================================\n");
    printf("1. Pick Health Potion (+50 HP)\n");
    printf("2. Pick Steel Sword (+30 ATK)\n");
    printf("3. Pick Dungeon Key\n");
    printf("4. Pick Gold Treasure (+100 Score)\n");
    printf("5. Use / Consume Item from Inventory\n");
    printf("0. Back to Game Menu\n");
    printf("----------------------------------------\n");
    printf("Enter choice: ");

    int choice = getIntInput();
    switch (choice) {
        case 1:
            addItem(&player->inventory, "Health Potion", ITEM_POTION, 50);
            break;
        case 2:
            addItem(&player->inventory, "Steel Sword", ITEM_WEAPON, 30);
            break;
        case 3:
            addItem(&player->inventory, "Dungeon Key", ITEM_KEY, 0);
            player->hasKey = 1;
            addScore(player, 150);
            printf("[*] Dungeon Key acquired! You can now unlock the exit.\n");
            break;
        case 4:
            addItem(&player->inventory, "Gold Treasure", ITEM_TREASURE, 100);
            addScore(player, 100);
            break;
        case 5: {
            if (player->inventory.head == NULL) {
                printf("[!] Inventory is empty. Nothing to use.\n");
                break;
            }
            char itemName[MAX_ITEM_NAME_LEN];
            printf("Enter item name to use: ");
            getStringInput(itemName, sizeof(itemName));

            ItemNode *found = searchItem(&player->inventory, itemName);
            if (found != NULL) {
                if (found->type == ITEM_POTION) {
                    healPlayer(player, found->value);
                    removeItem(&player->inventory, found->name);
                } else if (found->type == ITEM_WEAPON) {
                    player->attack += found->value;
                    printf("[+] Equipped %s! Player Attack is now %d.\n", found->name, player->attack);
                    removeItem(&player->inventory, found->name);
                } else if (found->type == ITEM_KEY) {
                    printf("[*] The Dungeon Key is active and ready for the Exit room.\n");
                } else if (found->type == ITEM_TREASURE) {
                    printf("[*] Treasure already contributed to your total score!\n");
                } else {
                    printf("[*] Used %s.\n", found->name);
                    removeItem(&player->inventory, found->name);
                }
            } else {
                printf("[!] Item '%s' not found in inventory.\n", itemName);
            }
            break;
        }
        case 0:
            break;
        default:
            printf("[!] Invalid choice.\n");
            break;
    }
}

// Main In-Game Loop executing all options
void runGameLoop(Player *player, Leaderboard *leaderboard, HashTable *itemDb, TreeNode *dungeonTree) {
    Graph graph;
    initializeGraph(&graph);

    Stack movementStack;
    initializeStack(&movementStack);

    int running = 1;
    while (running && isPlayerAlive(player)) {
        // Check for Win condition
        if (player->hasKey && player->currentRoom == 8) {
            printf("\n========================================\n");
            printf("      CONGRATULATIONS, %s!\n", player->name);
            printf("      YOU HAVE ESCAPED THE DUNGEON!\n");
            printf("========================================\n");
            printf("Final Score: %d\n\n", player->score);
            addLeaderboardScore(leaderboard, player->name, player->score);
            saveLeaderboard(leaderboard, LEADERBOARD_FILE);
            displayLeaderboard(leaderboard);
            break;
        }

        displayGameMenuHeader(player, &graph);
        int choice = getIntInput();
        if (choice == -999) {
            running = 0;
            break;
        }

        switch (choice) {
            case 1:
                handleMove(player, &graph, &movementStack);
                break;
            case 2:
                handleExploreDungeon(dungeonTree, &graph, player->currentRoom);
                break;
            case 3:
                displayInventory(&player->inventory);
                break;
            case 4:
                handleItemSubmenu(player);
                break;
            case 5:
                handleItemSearch(itemDb);
                break;
            case 6:
                handleWeaponSearch();
                break;
            case 7:
                handleCombat(player);
                break;
            case 8:
                handleUndo(player, &movementStack, &graph);
                break;
            case 9:
                BFS(&graph, player->currentRoom, 8); // Shortest path to Exit (8)
                break;
            case 10:
                displayGraph(&graph);
                break;
            case 11:
                printf("\n========================================\n");
                printf("       DUNGEON HIERARCHY TREE\n");
                printf("========================================\n");
                displayTreeHierarchical(dungeonTree, 0);
                printf("\n========================================\n\n");
                break;
            case 12:
                displayLeaderboard(leaderboard);
                break;
            case 13:
                displayPlayer(player);
                break;
            case 0:
                printf("\nExiting current dungeon run...\n");
                running = 0;
                break;
            default:
                printf("\n[!] Invalid choice. Please enter a valid number (0 - 13).\n");
                break;
        }
    }

    // Check for Game Over condition
    if (!isPlayerAlive(player)) {
        printf("\n========================================\n");
        printf("               GAME OVER\n");
        printf("========================================\n");
        printf("Player: %s has fallen in the dungeon.\n", player->name);
        printf("Final Score: %d\n", player->score);
        printf("========================================\n\n");

        addLeaderboardScore(leaderboard, player->name, player->score);
        saveLeaderboard(leaderboard, LEADERBOARD_FILE);
    }

    // Free dynamic resources allocated during game run
    freeGraph(&graph);
    freeStack(&movementStack);
}

// Start Game Entry Controller
void startGame(void) {
    initializeWeapons();

    Leaderboard leaderboard;
    initializeLeaderboard(&leaderboard);
    loadLeaderboard(&leaderboard, LEADERBOARD_FILE);

    HashTable itemDb;
    initializeHashTable(&itemDb);
    populateDefaultItemDatabase(&itemDb);

    TreeNode *dungeonTree = buildDungeonTree();

    int inMainMenu = 1;
    while (inMainMenu) {
        showMainMenu();
        int choice = getIntInput();
        if (choice == -999) {
            inMainMenu = 0;
            break;
        }

        switch (choice) {
            case 1: {
                char playerName[MAX_NAME_LEN];
                printf("\nEnter your name: ");
                getStringInput(playerName, sizeof(playerName));

                Player player;
                initializePlayer(&player, playerName);
                printf("\nWelcome, %s! You enter the dark dungeon entrance...\n", player.name);

                runGameLoop(&player, &leaderboard, &itemDb, dungeonTree);

                // Free player resources including dynamic linked list
                freePlayer(&player);
                break;
            }
            case 2:
                showInstructions();
                break;
            case 3:
                displayLeaderboard(&leaderboard);
                break;
            case 4:
                printf("\nThank you for playing Dungeon Escape! Goodbye.\n");
                inMainMenu = 0;
                break;
            default:
                printf("\n[!] Invalid choice. Please enter 1, 2, 3, or 4.\n\n");
                break;
        }
    }

    // Clean up all persistent data structures
    freeTree(dungeonTree);
    freeHashTable(&itemDb);
    freeLeaderboard(&leaderboard);
}
