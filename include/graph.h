#ifndef GRAPH_H
#define GRAPH_H

#define MAX_ROOMS 9
#define MAX_ROOM_NAME_LEN 50
#define MAX_DESC_LEN 150

// Adjacency List Node representing connected room edges
// Graph represents the navigable connections between rooms.
typedef struct AdjListNode {
    int dest;
    int weight; // step distance
    struct AdjListNode *next;
} AdjListNode;

// Vertex representing a dungeon room
typedef struct {
    char name[MAX_ROOM_NAME_LEN];
    char description[MAX_DESC_LEN];
    int hasItem;
    int hasEnemy;
    int isExplored;
    AdjListNode *head;
} RoomVertex;

// Graph structure containing array of room adjacency lists
typedef struct {
    int numVertices;
    RoomVertex rooms[MAX_ROOMS];
} Graph;

// Function prototypes
void initializeGraph(Graph *g);
void addEdge(Graph *g, int src, int dest, int weight, int isBidirectional);
void displayGraph(const Graph *g);
void displayConnectedRooms(const Graph *g, int currentRoom);
int isValidMove(const Graph *g, int currentRoom, int targetRoom);
void BFS(const Graph *g, int startRoom, int targetRoom);
void DFS(const Graph *g, int startRoom);
void freeGraph(Graph *g);
const char* getRoomNameById(const Graph *g, int roomId);

#endif // GRAPH_H
