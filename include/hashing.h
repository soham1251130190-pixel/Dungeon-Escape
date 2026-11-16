#ifndef HASHING_H
#define HASHING_H

#define HASH_TABLE_SIZE 10
#define MAX_HASH_STR_LEN 30

// Node in the hash table bucket chain (Separate Chaining)
// Hash table provides fast item lookup using string hashing and separate chaining.
typedef struct HashNode {
    char name[MAX_HASH_STR_LEN];
    char type[MAX_HASH_STR_LEN];
    int value;
    char description[80];
    struct HashNode *next;
} HashNode;

// Hash table containing array of bucket head pointers
typedef struct {
    HashNode *buckets[HASH_TABLE_SIZE];
    int totalEntries;
} HashTable;

// Function prototypes
void initializeHashTable(HashTable *ht);
int hashFunction(const char *key);
void insertHash(HashTable *ht, const char *name, const char *type, int value, const char *description);
HashNode* searchHash(const HashTable *ht, const char *name);
int deleteHash(HashTable *ht, const char *name);
void displayHashTable(const HashTable *ht);
void freeHashTable(HashTable *ht);
void populateDefaultItemDatabase(HashTable *ht);

#endif // HASHING_H
