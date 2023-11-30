#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../include/hash_table.h"

HashTable *init_hash_table()
{
    HashTable *hashTable = (HashTable *)calloc(1, sizeof(HashTable));
    if (!hashTable)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    hashTable->capacity = DEFAULT_CAPACITY;
    hashTable->size = 0;

    hashTable->table = (Hash *)calloc(hashTable->capacity, sizeof(Hash));
    if (!hashTable->table)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Initialize all entries with empty value
    for (int i = 0; i < hashTable->capacity; i++)
    {
        hashTable->table[i].key = EMPTY_VALUE;
        hashTable->table[i].value = EMPTY_VALUE;
    }

    return hashTable;
}

HashTable *init_hash_table_helper(int new_capacity)
{
    HashTable *hashTable = (HashTable *)calloc(1, sizeof(HashTable));
    if (!hashTable)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    hashTable->capacity = new_capacity;
    hashTable->size = 0;

    hashTable->table = (Hash *)calloc(hashTable->capacity, sizeof(Hash));
    if (!hashTable->table)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Initialize all entries with empty value
    for (int i = 0; i < hashTable->capacity; i++)
    {
        hashTable->table[i].key = EMPTY_VALUE;
        hashTable->table[i].value = EMPTY_VALUE;
    }

    return hashTable;
}

void resize_hash_table(HashTable *hashTable, int new_capacity)
{
    // Initializing new hash table
    HashTable *newHashTable = init_hash_table_helper(new_capacity);

    // Rehash all existing elements into the new hash table
    for (int i = 0; i < hashTable->capacity; i++)
        if (hashTable->table[i].key != EMPTY_VALUE)
            insert(newHashTable, hashTable->table[i].key, hashTable->table[i].value);

    // Replace the old hash table with the new one and update the capacity
    free(hashTable->table);
    hashTable->table = newHashTable->table;
    hashTable->capacity = new_capacity;

    // Free the memory of the old hash table structure
    free(newHashTable);
    newHashTable = NULL;
}

int hash(int key, int capacity) { return (key % capacity + capacity) % capacity; }

void insert(HashTable *hashTable, int key, int value)
{
    // Increasing memory for hash table if it's necessary
    if (hashTable->size >= hashTable->capacity / 2)
        resize_hash_table(hashTable, hashTable->capacity * 2);

    int index = hash(key, hashTable->capacity), original_index = index; // Storing the original index
                                                                        // for loop termination check

    // Filling of slots to resolve collisions
    do
    {
        if (hashTable->table[index].key == EMPTY_VALUE)
        {
            // Inserting the key and value
            hashTable->table[index].key = key;
            hashTable->table[index].value = value;
            hashTable->size++;
            return;
        }
        index = (index + 1) % hashTable->capacity;
    } while (index != original_index);
}

int search(HashTable *hashTable, int key, int *comparisons)
{
    *comparisons = 0;
    int index = hash(key, hashTable->capacity), count = 0;

    // Linear probing to find the key
    while (count < hashTable->capacity)
    {
        if (hashTable->table[index].key == key)
            return hashTable->table[index].value;
        index = (index + 1) % hashTable->capacity;
        count++;
    }

    *comparisons = count;

    // Key not found
    return EMPTY_VALUE;
}

void delete_key(HashTable *hashTable, int key)
{
    int index = hash(key, hashTable->capacity);

    // Filling hash table to find and delete the key
    int count = 0;
    while (count < hashTable->capacity)
    {
        if (hashTable->table[index].key == key)
        {
            hashTable->table[index].key = EMPTY_VALUE;
            hashTable->table[index].value = EMPTY_VALUE;
            hashTable->size--;
            return;
        }
        index = (index + 1) % hashTable->capacity;
        count++;
    }
}

void print_hash_table(HashTable *hashTable)
{
    for (int i = 0; i < hashTable->size; i++)
        printf("%d:%d; ", hashTable->table->key, hashTable->table->value);
    printf("\n");
}

void destroy_hash_table(HashTable *hashTable)
{
    free(hashTable->table);
    hashTable->table = NULL;

    free(hashTable);
    hashTable = NULL;
}
