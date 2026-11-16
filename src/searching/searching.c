#include <stdio.h>
#include <string.h>
#include "searching.h"

// Linear Search: Iterates through singly linked list items sequentially
ItemNode* linearSearchInventory(const Inventory *inv, const char *itemName) {
    if (inv == NULL || itemName == NULL) return NULL;

    printf("\n[Searching] Performing Linear Search on Inventory...\n");
    ItemNode *current = inv->head;
    int step = 1;

    while (current != NULL) {
        printf("  Step %d: Checking item '%s'...\n", step++, current->name);
        if (strcasecmp(current->name, itemName) == 0) {
            printf("[+] Item Found via Linear Search!\n");
            return current;
        }
        current = current->next;
    }

    printf("[-] Item '%s' not found in inventory.\n", itemName);
    return NULL;
}

// Linear Search on Weapon Array by name
int linearSearchWeaponByName(const Weapon weapons[], int size, const char *name) {
    if (weapons == NULL || name == NULL) return -1;

    printf("\n[Searching] Performing Linear Search on Weapons Array...\n");
    for (int i = 0; i < size; i++) {
        printf("  Step %d: Comparing with '%s' (ATK: %d)...\n", i + 1, weapons[i].name, weapons[i].attack);
        if (strcasecmp(weapons[i].name, name) == 0) {
            printf("[+] Weapon Found via Linear Search!\n");
            return i;
        }
    }

    printf("[-] Weapon '%s' not found.\n", name);
    return -1;
}

// Binary Search on sorted weapon array by attack value (O(log n))
int binarySearchWeaponByAttack(const Weapon weapons[], int size, int targetAttack) {
    if (weapons == NULL || size <= 0) return -1;

    printf("\n========================================\n");
    printf("        BINARY SEARCH IN PROGRESS\n");
    printf("========================================\n");
    printf("Target Attack Value: %d\n", targetAttack);
    printf("Using Binary Search on sorted weapon array...\n\n");

    int low = 0;
    int high = size - 1;
    int step = 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        printf("  [Iteration %d] Search range [%d..%d], Mid Index: %d (%s, ATK: %d)\n",
               step++, low, high, mid, weapons[mid].name, weapons[mid].attack);

        if (weapons[mid].attack == targetAttack) {
            printf("\n>>> Weapon Found! <<<\n");
            printf("  Name  : %s\n", weapons[mid].name);
            printf("  Attack: %d\n", weapons[mid].attack);
            printf("========================================\n\n");
            return mid;
        } else if (weapons[mid].attack < targetAttack) {
            printf("  -> Target (%d) > Mid (%d). Searching right half.\n", targetAttack, weapons[mid].attack);
            low = mid + 1;
        } else {
            printf("  -> Target (%d) < Mid (%d). Searching left half.\n", targetAttack, weapons[mid].attack);
            high = mid - 1;
        }
    }

    printf("\n[-] No weapon found with attack value %d.\n", targetAttack);
    printf("========================================\n\n");
    return -1;
}
