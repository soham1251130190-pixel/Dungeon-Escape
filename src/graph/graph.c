#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

// Helper to create an adjacency list edge node
static AdjListNode* createAdjNode(int dest, int weight) {
    AdjListNode *newNode = (AdjListNode *)malloc(sizeof(AdjListNode));
    if (newNode == NULL) {
        printf("Memory allocation failed for graph edge.\n");
        return NULL;
    }
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Initialize the 9-room dungeon graph with descriptions and connected edges
void initializeGraph(Graph *g) {
    if (g == NULL) return;

    g->numVertices = MAX_ROOMS;

    const char *names[MAX_ROOMS] = {
        "Entrance",
        "Armory",
        "Library",
        "Dark Hall",
        "Potion Room",
        "Monster Room",
        "Treasure Room",
        "Boss Room",
        "Exit"
    };

    const char *descriptions[MAX_ROOMS] = {
        "The ancient stone archway where your journey began. It feels relatively safe.",
        "An old armory. Rusty weapon racks line the wall. A pristine weapon might be here.",
        "A quiet sanctuary of forgotten scrolls and lore. No enemies linger here.",
        "A pitch-black corridor. You hear menacing growls echoing down the passageway.",
        "An alchemical laboratory filled with glass vials and healing draughts.",
        "A grim chamber covered in bones. Fierce dungeon monsters lurk here!",
        "A glittering vault! The Dungeon Key is locked inside a gilded chest.",
        "A massive chamber radiating heat. The Dungeon Dragon guards the gateway!",
        "The enchanted gateway to the outer world. Requires the Dungeon Key to escape."
    };

    for (int i = 0; i < MAX_ROOMS; i++) {
        strncpy(g->rooms[i].name, names[i], MAX_ROOM_NAME_LEN - 1);
        g->rooms[i].name[MAX_ROOM_NAME_LEN - 1] = '\0';

        strncpy(g->rooms[i].description, descriptions[i], MAX_DESC_LEN - 1);
        g->rooms[i].description[MAX_DESC_LEN - 1] = '\0';

        g->rooms[i].hasItem = (i == 1 || i == 4 || i == 6); // Armory, Potion, Treasure
        g->rooms[i].hasEnemy = (i == 5 || i == 7);           // Monster, Boss
        g->rooms[i].isExplored = (i == 0);
        g->rooms[i].head = NULL;
    }

    // Connect dungeon rooms (Graph represents room connections)
    // 0: Entrance <-> 1: Armory, 3: Dark Hall
    addEdge(g, 0, 1, 1, 1);
    addEdge(g, 0, 3, 1, 1);

    // 1: Armory <-> 2: Library, 4: Potion Room
    addEdge(g, 1, 2, 1, 1);
    addEdge(g, 1, 4, 1, 1);

    // 4: Potion Room <-> 5: Monster Room
    addEdge(g, 4, 5, 1, 1);

    // 3: Dark Hall <-> 5: Monster Room, 6: Treasure Room
    addEdge(g, 3, 5, 1, 1);
    addEdge(g, 3, 6, 1, 1);

    // 5: Monster Room <-> 7: Boss Room
    addEdge(g, 5, 7, 1, 1);

    // 6: Treasure Room <-> 7: Boss Room
    addEdge(g, 6, 7, 1, 1);

    // 7: Boss Room <-> 8: Exit
    addEdge(g, 7, 8, 1, 1);
}

// Add edge to adjacency list (supports bidirectional corridors)
void addEdge(Graph *g, int src, int dest, int weight, int isBidirectional) {
    if (g == NULL || src < 0 || src >= g->numVertices || dest < 0 || dest >= g->numVertices) {
        return;
    }

    AdjListNode *node = createAdjNode(dest, weight);
    if (node != NULL) {
        node->next = g->rooms[src].head;
        g->rooms[src].head = node;
    }

    if (isBidirectional) {
        AdjListNode *revNode = createAdjNode(src, weight);
        if (revNode != NULL) {
            revNode->next = g->rooms[dest].head;
            g->rooms[dest].head = revNode;
        }
    }
}

// Display full graph adjacency list representation
void displayGraph(const Graph *g) {
    if (g == NULL) return;

    printf("\n========================================\n");
    printf("     DUNGEON GRAPH (ADJACENCY LIST)\n");
    printf("========================================\n");
    for (int i = 0; i < g->numVertices; i++) {
        printf(" [%d] %-14s -> ", i, g->rooms[i].name);
        AdjListNode *curr = g->rooms[i].head;
        if (curr == NULL) {
            printf("None");
        }
        while (curr != NULL) {
            printf("[%d: %s]", curr->dest, g->rooms[curr->dest].name);
            if (curr->next != NULL) printf(" -> ");
            curr = curr->next;
        }
        printf("\n");
    }
    printf("========================================\n\n");
}

// Display available connected paths from current room
void displayConnectedRooms(const Graph *g, int currentRoom) {
    if (g == NULL || currentRoom < 0 || currentRoom >= g->numVertices) return;

    printf("\nAvailable paths from %s:\n", g->rooms[currentRoom].name);
    AdjListNode *curr = g->rooms[currentRoom].head;
    int idx = 1;
    while (curr != NULL) {
        printf("  %d. Move to %s (Room ID: %d)\n", idx++, g->rooms[curr->dest].name, curr->dest);
        curr = curr->next;
    }
    printf("  0. Stay in current room\n");
}

// Check if a move from currentRoom to targetRoom is valid
int isValidMove(const Graph *g, int currentRoom, int targetRoom) {
    if (g == NULL || currentRoom < 0 || currentRoom >= g->numVertices) return 0;

    AdjListNode *curr = g->rooms[currentRoom].head;
    while (curr != NULL) {
        if (curr->dest == targetRoom) {
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

// BFS Algorithm: Finds the shortest path to target room (Exit) and prints path + distance
void BFS(const Graph *g, int startRoom, int targetRoom) {
    if (g == NULL || startRoom < 0 || startRoom >= g->numVertices || targetRoom < 0 || targetRoom >= g->numVertices) {
        printf("[!] Invalid room IDs for BFS.\n");
        return;
    }

    int visited[MAX_ROOMS] = {0};
    int parent[MAX_ROOMS];
    int dist[MAX_ROOMS];

    for (int i = 0; i < MAX_ROOMS; i++) {
        parent[i] = -1;
        dist[i] = -1;
    }

    // Queue for BFS traversal
    int queue[MAX_ROOMS];
    int front = 0, rear = 0;

    visited[startRoom] = 1;
    dist[startRoom] = 0;
    queue[rear++] = startRoom;

    while (front < rear) {
        int u = queue[front++];

        if (u == targetRoom) break;

        AdjListNode *curr = g->rooms[u].head;
        while (curr != NULL) {
            int v = curr->dest;
            if (!visited[v]) {
                visited[v] = 1;
                dist[v] = dist[u] + 1;
                parent[v] = u;
                queue[rear++] = v;
            }
            curr = curr->next;
        }
    }

    printf("\n========================================\n");
    printf("      SHORTEST PATH SEARCH (BFS)\n");
    printf("========================================\n");
    printf("Origin : [%d] %s\n", startRoom, g->rooms[startRoom].name);
    printf("Target : [%d] %s\n", targetRoom, g->rooms[targetRoom].name);

    if (!visited[targetRoom]) {
        printf("Result : No reachable path found to target room.\n");
        printf("========================================\n\n");
        return;
    }

    // Reconstruct path from target to start using parent array
    int path[MAX_ROOMS];
    int pathLen = 0;
    int curr = targetRoom;
    while (curr != -1) {
        path[pathLen++] = curr;
        curr = parent[curr];
    }

    printf("Shortest Path:\n  ");
    for (int i = pathLen - 1; i >= 0; i--) {
        printf("[%d] %s", path[i], g->rooms[path[i]].name);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
    printf("Total Rooms / Steps Distance: %d\n", dist[targetRoom]);
    printf("========================================\n\n");
}

// Recursive helper for Depth-First Search (DFS)
static void dfsRecursive(const Graph *g, int current, int visited[]) {
    visited[current] = 1;
    printf("  -> [%d] %s\n", current, g->rooms[current].name);

    AdjListNode *curr = g->rooms[current].head;
    while (curr != NULL) {
        if (!visited[curr->dest]) {
            // Recursion: DFS explores deep paths first
            dfsRecursive(g, curr->dest, visited);
        }
        curr = curr->next;
    }
}

// DFS Algorithm: Explores all reachable dungeon rooms recursively
void DFS(const Graph *g, int startRoom) {
    if (g == NULL || startRoom < 0 || startRoom >= g->numVertices) {
        printf("[!] Invalid start room for DFS.\n");
        return;
    }

    int visited[MAX_ROOMS] = {0};
    printf("\n========================================\n");
    printf("    DEPTH-FIRST EXPLORATION (DFS)\n");
    printf("========================================\n");
    printf("Starting recursive DFS exploration from %s:\n", g->rooms[startRoom].name);

    dfsRecursive(g, startRoom, visited);

    printf("========================================\n\n");
}

// Free all dynamically allocated adjacency list nodes
void freeGraph(Graph *g) {
    if (g == NULL) return;

    for (int i = 0; i < g->numVertices; i++) {
        AdjListNode *curr = g->rooms[i].head;
        while (curr != NULL) {
            AdjListNode *temp = curr;
            curr = curr->next;
            free(temp);
        }
        g->rooms[i].head = NULL;
    }
}

// Get name of a room safely
const char* getRoomNameById(const Graph *g, int roomId) {
    if (g == NULL || roomId < 0 || roomId >= g->numVertices) return "Unknown";
    return g->rooms[roomId].name;
}
