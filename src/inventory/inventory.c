#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

// Convert item type enum to human-readable string
const char* getItemTypeName(ItemType type) {
    switch (type) {
        case ITEM_WEAPON:   return "Weapon";
        case ITEM_POTION:   return "Potion";
        case ITEM_SHIELD:   return "Shield";
        case ITEM_KEY:      return "Key";
        case ITEM_TREASURE: return "Treasure";
        default:            return "Unknown";
    }
}

// Initialize an empty singly linked list inventory
void initializeInventory(Inventory *inv) {
    if (inv == NULL) return;
    inv->head = NULL;
    inv->count = 0;
}

// Add a new item node to the end of the linked list using dynamic memory allocation
void addItem(Inventory *inv, const char *name, ItemType type, int value) {
    if (inv == NULL || name == NULL) return;

    // Allocate memory dynamically for new linked list node
    ItemNode *newNode = (ItemNode *)malloc(sizeof(ItemNode));
    if (newNode == NULL) {
        printf("Memory allocation failed for new inventory item.\n");
        return;
    }

    strncpy(newNode->name, name, MAX_ITEM_NAME_LEN - 1);
    newNode->name[MAX_ITEM_NAME_LEN - 1] = '\0';
    newNode->type = type;
    newNode->value = value;
    newNode->next = NULL;

    // Insertion into linked list
    if (inv->head == NULL) {
        inv->head = newNode;
    } else {
        ItemNode *current = inv->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    inv->count++;

    printf("[+] Added '%s' (%s, Value: %d) to inventory.\n", newNode->name, getItemTypeName(type), value);
}

// Remove an item node from the linked list by name and free its allocated memory
int removeItem(Inventory *inv, const char *name) {
    if (inv == NULL || inv->head == NULL || name == NULL) {
        return 0;
    }

    ItemNode *current = inv->head;
    ItemNode *prev = NULL;

    while (current != NULL) {
        if (strcasecmp(current->name, name) == 0) {
            if (prev == NULL) {
                // Removing head node
                inv->head = current->next;
            } else {
                // Removing middle or tail node
                prev->next = current->next;
            }
            free(current);
            inv->count--;
            return 1;
        }
        prev = current;
        current = current->next;
    }

    return 0; // Item not found
}

// Search for an item in the linked list using linear traversal
ItemNode* searchItem(const Inventory *inv, const char *name) {
    if (inv == NULL || name == NULL) return NULL;

    ItemNode *current = inv->head;
    while (current != NULL) {
        if (strcasecmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Display the linked list visually and as a structured inventory list
void displayInventory(const Inventory *inv) {
    if (inv == NULL || inv->head == NULL) {
        printf("\n========================================\n");
        printf("        INVENTORY (LINKED LIST)\n");
        printf("========================================\n");
        printf("  Inventory is empty!\n");
        printf("  HEAD -> NULL\n");
        printf("========================================\n\n");
        return;
    }

    printf("\n========================================\n");
    printf("        INVENTORY (LINKED LIST)\n");
    printf("========================================\n");

    // Display visual linked list structure for viva demonstration
    printf("Visual Chain:\nHEAD -> ");
    ItemNode *curr = inv->head;
    while (curr != NULL) {
        printf("[%s] -> ", curr->name);
        curr = curr->next;
    }
    printf("NULL\n\n");

    // Detailed table of items
    printf("  %-4s  %-16s  %-10s  %-8s\n", "No.", "Item Name", "Type", "Value");
    printf("  -----------------------------------------------\n");
    curr = inv->head;
    int idx = 1;
    while (curr != NULL) {
        printf("  [%d]   %-16s  %-10s  +%-8d\n", idx++, curr->name, getItemTypeName(curr->type), curr->value);
        curr = curr->next;
    }
    printf("  Total items: %d\n", inv->count);
    printf("========================================\n\n");
}

// Free all nodes in the linked list to prevent memory leaks
void freeInventory(Inventory *inv) {
    if (inv == NULL) return;

    ItemNode *current = inv->head;
    while (current != NULL) {
        ItemNode *temp = current;
        current = current->next;
        free(temp);
    }
    inv->head = NULL;
    inv->count = 0;
}

