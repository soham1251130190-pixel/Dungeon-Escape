#ifndef SEARCHING_H
#define SEARCHING_H

#include "weapons.h"
#include "inventory.h"

// Searching function prototypes
// Linear Search works on unsorted collections such as the player inventory.
ItemNode* linearSearchInventory(const Inventory *inv, const char *itemName);

// Binary Search works on the sorted weapon array by attack power in O(log n) time.
int binarySearchWeaponByAttack(const Weapon weapons[], int size, int targetAttack);

// Binary Search helper by weapon name (if sorted by name)
int linearSearchWeaponByName(const Weapon weapons[], int size, const char *name);

#endif // SEARCHING_H
