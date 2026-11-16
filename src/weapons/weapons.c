#include <stdio.h>
#include <string.h>
#include "weapons.h"

// Fixed array storing the weapons database
// Array is maintained in sorted order of attack value (15, 25, 40, 50, 70, 100)
// This enables efficient Binary Search on weapons.
static Weapon weaponDatabase[MAX_WEAPONS];
static int isInitialized = 0;

void initializeWeapons(void) {
    // Array stores fixed list of weapons sorted by attack value.
    strcpy(weaponDatabase[0].name, "Dagger");
    weaponDatabase[0].attack = 15;

    strcpy(weaponDatabase[1].name, "Bow");
    weaponDatabase[1].attack = 25;

    strcpy(weaponDatabase[2].name, "Axe");
    weaponDatabase[2].attack = 40;

    strcpy(weaponDatabase[3].name, "Sword");
    weaponDatabase[3].attack = 50;

    strcpy(weaponDatabase[4].name, "Hammer");
    weaponDatabase[4].attack = 70;

    strcpy(weaponDatabase[5].name, "Legendary Sword");
    weaponDatabase[5].attack = 100;

    isInitialized = 1;
}

void displayWeapons(void) {
    if (!isInitialized) {
        initializeWeapons();
    }

    printf("\n========================================\n");
    printf("         WEAPON ARSENAL (ARRAY)\n");
    printf("========================================\n");
    printf("  %-4s  %-18s  %-10s\n", "ID", "Weapon Name", "Attack Power");
    printf("  --------------------------------------\n");
    for (int i = 0; i < MAX_WEAPONS; i++) {
        printf("  [%d]   %-18s  +%-10d\n", i + 1, weaponDatabase[i].name, weaponDatabase[i].attack);
    }
    printf("========================================\n\n");
}

int getWeaponCount(void) {
    return MAX_WEAPONS;
}

const Weapon* getWeapon(int index) {
    if (!isInitialized) {
        initializeWeapons();
    }
    if (index >= 0 && index < MAX_WEAPONS) {
        return &weaponDatabase[index];
    }
    return NULL;
}

// Linear lookup helper by name in the weapon array
int findWeapon(const char *name) {
    if (!isInitialized) {
        initializeWeapons();
    }
    if (name == NULL) return -1;

    for (int i = 0; i < MAX_WEAPONS; i++) {
        if (strcasecmp(weaponDatabase[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

