#include <stdbool.h>

struct HashTable;
struct Binding;

/* Creates and Initializes a HashTable and returns it */
struct HashTable *create();

/* Hashes the key */
unsigned int hash(const char *key);

/*
    Add key -> value pair if it doesn't already exist and return true
    Update the value of the key if it already existed and return false
*/
bool add(struct HashTable *table, const char *key, int value);

/* Searches for the binding by its key, NULL if it doesn't exist */
struct Binding *find(struct HashTable *table, const char *key);

/* Remove a binding with key 'key' from the table */
bool remove(struct HashTable *table, const char *key);

/* Delete all dynamicaly allocated memories of the HashTable */
void delete_table(struct HashTable *table);