#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashing.h"

// Initialize hash table with NULL buckets
void initializeHashTable(HashTable *ht) {
    if (ht == NULL) return;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ht->buckets[i] = NULL;
    }
    ht->totalEntries = 0;
}

// Polynomial hash function for strings modulo HASH_TABLE_SIZE
// Uses case-insensitive hashing so "Potion" and "potion" map to the same bucket
int hashFunction(const char *key) {
    if (key == NULL) return 0;

    unsigned long hash = 5381;
    for (int i = 0; key[i] != '\0'; i++) {
        char c = (char)tolower((unsigned char)key[i]);
        hash = ((hash << 5) + hash) + (unsigned long)c; // hash * 33 + c
    }
    return (int)(hash % HASH_TABLE_SIZE);
}

// Insert item into hash table with separate chaining for collision resolution
void insertHash(HashTable *ht, const char *name, const char *type, int value, const char *description) {
    if (ht == NULL || name == NULL) return;

    int bucket = hashFunction(name);

    // Check if key already exists in this bucket (update if found)
    HashNode *curr = ht->buckets[bucket];
    while (curr != NULL) {
        if (strcasecmp(curr->name, name) == 0) {
            curr->value = value;
            if (type) strncpy(curr->type, type, MAX_HASH_STR_LEN - 1);
            if (description) strncpy(curr->description, description, 79);
            return;
        }
        curr = curr->next;
    }

    // Allocate new hash node dynamically
    HashNode *newNode = (HashNode *)malloc(sizeof(HashNode));
    if (newNode == NULL) {
        printf("Memory allocation failed for hash node.\n");
        return;
    }

    strncpy(newNode->name, name, MAX_HASH_STR_LEN - 1);
    newNode->name[MAX_HASH_STR_LEN - 1] = '\0';

    if (type) {
        strncpy(newNode->type, type, MAX_HASH_STR_LEN - 1);
        newNode->type[MAX_HASH_STR_LEN - 1] = '\0';
    } else {
        strcpy(newNode->type, "Item");
    }

    newNode->value = value;

    if (description) {
        strncpy(newNode->description, description, 79);
        newNode->description[79] = '\0';
    } else {
        strcpy(newNode->description, "");
    }

    // Insert at front of bucket chain (Separate Chaining)
    newNode->next = ht->buckets[bucket];
    ht->buckets[bucket] = newNode;
    ht->totalEntries++;
}

// Search for item in hash table using hash calculation followed by bucket chain traversal
HashNode* searchHash(const HashTable *ht, const char *name) {
    if (ht == NULL || name == NULL) return NULL;

    int bucket = hashFunction(name);
    printf("\n[Hashing] Calculated Hash Index for '%s' -> Bucket [%d]\n", name, bucket);

    HashNode *curr = ht->buckets[bucket];
    int step = 1;
    while (curr != NULL) {
        printf("  [Bucket %d, Step %d] Checking '%s'...\n", bucket, step++, curr->name);
        if (strcasecmp(curr->name, name) == 0) {
            printf("  [+] Item Found in Hash Table!\n");
            return curr;
        }
        curr = curr->next;
    }

    printf("  [-] Item '%s' not found in Bucket [%d].\n", name, bucket);
    return NULL;
}

// Delete item from hash table
int deleteHash(HashTable *ht, const char *name) {
    if (ht == NULL || name == NULL) return 0;

    int bucket = hashFunction(name);
    HashNode *curr = ht->buckets[bucket];
    HashNode *prev = NULL;

    while (curr != NULL) {
        if (strcasecmp(curr->name, name) == 0) {
            if (prev == NULL) {
                ht->buckets[bucket] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            ht->totalEntries--;
            return 1;
        }
        prev = curr;
        curr = curr->next;
    }
    return 0;
}

// Display entire hash table structure showing all buckets and chains
void displayHashTable(const HashTable *ht) {
    printf("\n========================================\n");
    printf("   HASH TABLE (SEPARATE CHAINING)\n");
    printf("========================================\n");

    if (ht == NULL) {
        printf("  Hash table uninitialized.\n");
        printf("========================================\n\n");
        return;
    }

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        printf("  [%d] ", i);
        HashNode *curr = ht->buckets[i];
        if (curr == NULL) {
            printf("Empty\n");
        } else {
            while (curr != NULL) {
                printf("[%s (%s: %d)]", curr->name, curr->type, curr->value);
                if (curr->next != NULL) printf(" -> ");
                curr = curr->next;
            }
            printf(" -> NULL\n");
        }
    }
    printf("  Total items indexed: %d\n", ht->totalEntries);
    printf("========================================\n\n");
}

// Free all allocated nodes across all buckets in the hash table
void freeHashTable(HashTable *ht) {
    if (ht == NULL) return;

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        HashNode *curr = ht->buckets[i];
        while (curr != NULL) {
            HashNode *temp = curr;
            curr = curr->next;
            free(temp);
        }
        ht->buckets[i] = NULL;
    }
    ht->totalEntries = 0;
}

// Populate the dungeon item encyclopedia
void populateDefaultItemDatabase(HashTable *ht) {
    if (ht == NULL) return;

    insertHash(ht, "Health Potion", "Potion", 50, "Restores 50 health points.");
    insertHash(ht, "Greater Potion", "Potion", 100, "Completely restores health.");
    insertHash(ht, "Dagger", "Weapon", 15, "Fast, lightweight rogue blade.");
    insertHash(ht, "Bow", "Weapon", 25, "Ranged elven recurve bow.");
    insertHash(ht, "Axe", "Weapon", 40, "Heavy double-bladed battleaxe.");
    insertHash(ht, "Sword", "Weapon", 50, "Tempered knightly steel longsword.");
    insertHash(ht, "Hammer", "Weapon", 70, "Massive dwarven warhammer.");
    insertHash(ht, "Legendary Sword", "Weapon", 100, "Mythical blade that banishes ancient evil.");
    insertHash(ht, "Iron Shield", "Shield", 20, "Defensive iron buckler.");
    insertHash(ht, "Dungeon Key", "Key", 0, "Enchanted golden key needed to unlock the Exit.");
    insertHash(ht, "Gold Treasure", "Treasure", 100, "Gleaming chest of ancient coins.");
}
