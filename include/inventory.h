#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX_ITEM_NAME_LEN 30

// Item types classification
typedef enum {
    ITEM_WEAPON,
    ITEM_POTION,
    ITEM_SHIELD,
    ITEM_KEY,
    ITEM_TREASURE
} ItemType;

// Linked list node representing an item in the player's inventory
// Linked List dynamically grows and shrinks as items are picked up or used.
typedef struct ItemNode {
    char name[MAX_ITEM_NAME_LEN];
    ItemType type;
    int value;
    struct ItemNode *next;
} ItemNode;

// Inventory wrapper structure
typedef struct {
    ItemNode *head;
    int count;
} Inventory;

// Function prototypes
void initializeInventory(Inventory *inv);
void addItem(Inventory *inv, const char *name, ItemType type, int value);
int removeItem(Inventory *inv, const char *name);
ItemNode* searchItem(const Inventory *inv, const char *name);
void displayInventory(const Inventory *inv);
void freeInventory(Inventory *inv);
const char* getItemTypeName(ItemType type);

#endif // INVENTORY_H

