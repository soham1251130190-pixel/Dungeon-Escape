#ifndef WEAPONS_H
#define WEAPONS_H

#define MAX_WEAPONS 6
#define MAX_WEAPON_NAME_LEN 30

// Structure representing a weapon item in the database
typedef struct {
    char name[MAX_WEAPON_NAME_LEN];
    int attack;
} Weapon;

// Array stores fixed list of weapons sorted by attack value for binary search
void initializeWeapons(void);
void displayWeapons(void);
int getWeaponCount(void);
const Weapon* getWeapon(int index);
int findWeapon(const char *name);

#endif // WEAPONS_H

