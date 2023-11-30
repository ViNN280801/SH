#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "../include/hash_table.h"
#include "../include/generate_keys.h"

int main()
{
    srand((unsigned)time(NULL));

    // Create an array to store 100 keys (50 random and 50 from test_numbers.txt)
    int set[MAX_KEYS_COUNT];

    // Generate 50 random keys in the range [10000000; 100000000)
    for (int i = 0; i < MAX_KEYS_COUNT / 2; i++)
        set[i] = 10000000 + rand() % (100000000 - 10000000);

    // Read 50 values from test_numbers.txt and add them to the array
    FILE *file = fopen("test_numbers.txt", "r");
    if (!file)
    {
        fprintf(stderr, "Error opening test_numbers.txt: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    // Filling 50 numbers from file 'text_numbers.txt'
    for (int i = MAX_KEYS_COUNT / 2; i < MAX_KEYS_COUNT; i++)
    {
        if (fscanf(file, "%d", &set[i]) != 1)
        {
            fprintf(stderr, "Error reading from test_numbers.txt: %s\n", strerror(errno));
            fclose(file);
            return EXIT_FAILURE;
        }
    }

    // Reordering elements in the set
    shuffle(set, MAX_KEYS_COUNT);

    HashTable *hashTable = init_hash_table();

    // Moving to the beginning of the file
    rewind(file);

    // Filling hash table with all test numbers from 'test_numbers.txt'
    int value = 0;
    while (fscanf(file, "%d", &value) == 1)
        insert(hashTable, value, value);

    // Closing file
    fclose(file);

    // Search for values in the hash table
    int totalComparisons = 0;

    for (int i = 0; i < MAX_KEYS_COUNT; i++)
    {
        int comparisons = 0,
            searchResult = search(hashTable, set[i], &comparisons);
        totalComparisons += comparisons;

        if (searchResult != EMPTY_VALUE)
            printf("Key %d \033[1;32mfound\033[0m\033[1m in the hash table. Comparisons: %d\n", set[i], comparisons);
        else
            printf("Key %d \033[1;31mnot found\033[0m\033[1m in the hash table. Comparisons: %d\n", set[i], comparisons);
    }

    // Calculate and display the average number of comparisons
    double averageComparisons = (double)totalComparisons / MAX_KEYS_COUNT;
    printf("Average comparisons per key: %.2lf\n", averageComparisons);

    // Calculate and display the memory used by the hash table
    size_t hashTableMemory = sizeof(HashTable) + (sizeof(Hash) * hashTable->capacity);
    printf("Memory used by hash table: %lu bytes\n", hashTableMemory);

    // Clean up the hash table
    destroy_hash_table(hashTable);

    return EXIT_SUCCESS;
}
