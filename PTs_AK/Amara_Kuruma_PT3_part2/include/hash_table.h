#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define DEFAULT_CAPACITY 100 // Default capacity of the hash table
#define EMPTY_VALUE -1       // Key -1 indicates an empty slot

// Structure for a hash table entry
typedef struct Hash
{
    int key;
    int value;
} Hash;

// Define the structure for the hash table
typedef struct HashTable
{
    Hash *table;  // Ptr on the table
    int capacity; // Maximum capacity of the table
    int size;     // Current count of elements in the table
} HashTable;

// Initialize the hash table (allocating memory)
HashTable *init_hash_table();

// Resizing the hash table
void resize_hash_table(HashTable *hashTable, int new_capacity);

// Hash function which method is division
int hash(int key, int capacity);

// Insert a key-value pair into the hash table
void insert(HashTable *hashTable, int key, int value);

// Search for a key in the hash table
int search(HashTable *hashTable, int key, int *comparisons);

// Delete a key from the hash table
void delete_key(HashTable *hashTable, int key);

// Prints all elements from the hash table to terminal
// Format: "key:value; " -> "145:10; "
void print_hash_table(HashTable *hashTable);

// Clean up and free memory
void destroy_hash_table(HashTable *hashTable);

#endif // !HASH_TABLE_H
