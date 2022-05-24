#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

const int BUCKET_COUNT = 1024;
const int HASH_SALT = 65599;

struct Binding
{
    const char *key;
    int value;
    struct Binding *next;
};

struct HashTable
{
    struct Binding *buckets[1024];
};

struct HashTable *create()
{
    struct HashTable *table = malloc(sizeof(struct HashTable));

    for (int i = 0; i < 1024; i++)
        table->buckets[i] = NULL;

    return table;
}

unsigned int hash(const char *key)
{

    unsigned int h = 0;

    for (int i = 0; key[i] != '\0'; i++)
        h = h * HASH_SALT + (unsigned int)key[i];

    return h % BUCKET_COUNT;
}

bool add(struct HashTable *table, const char *key, int value)
{

    unsigned int h = hash(key);

    struct Binding *binding = table->buckets[h];

    while (binding != NULL)
    {
        if (strcmp(key, binding->key) == 0)
        {
            binding->value = value;
            return false;
        }
        binding = binding->next;
    }

    struct Binding *newElement = malloc(sizeof(struct Binding)); // The new key->value pair to be added

    newElement->key = key;
    newElement->value = value;
    newElement->next = table->buckets[h];

    table->buckets[h] = newElement;

    return true;
}

struct Binding *find(struct HashTable *table, const char *key)
{

    unsigned int h = hash(key);

    struct Binding *binding = table->buckets[h];

    while (binding != NULL)
    {
        if (strcmp(key, binding->key) == 0)
            return binding;

        binding = binding->next;
    }

    return NULL;
}

void delete_ptr(void *ptr)
{
    free(ptr);
    ptr = NULL;
}

bool remove(struct HashTable *table, const char *key)
{

    unsigned int h = hash(key);

    struct Binding *prev = NULL, *binding = table->buckets[h];

    while (binding != NULL)
    {
        if (strcmp(key, binding->key) == 0)
        {

            if (prev == NULL)
                table->buckets[h] = binding->next;
            else
                prev->next = binding->next;

            delete_ptr(binding);

            return true;
        }

        prev = binding;
        binding = binding->next;
    }

    return false;
}

void delete_table(struct HashTable *table)
{

    for (int i = 0; i < BUCKET_COUNT; i++)
    {
        struct Binding *binding = table->buckets[i];
        struct Binding *next;

        while (binding != NULL)
        {
            next = binding->next;
            delete_ptr(binding);
            binding = next;
        }
    }

    delete_ptr(table);
}