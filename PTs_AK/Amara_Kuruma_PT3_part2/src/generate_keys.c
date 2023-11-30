#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/generate_keys.h"

// Function to generate additional keys to reach the desired count
void generate_additional_keys(int *keys, int count, int min, int max)
{
    int range = max - min;

    // Generate count keys in the specified range
    for (int i = 0; i < count; i++)
        keys[i] = min + rand() % range;
}

// Function to generate the test set of 100 keys
void generate_test_keys(int *test_keys)
{
    // Read keys from the file "test_numbers.txt"
    int keys_from_file[MAX_KEYS_COUNT], keys_from_file_count = 0;

    FILE *file = fopen("test_numbers.txt", "r");
    if (file)
    {
        while (fscanf(file, "%d", &keys_from_file[keys_from_file_count]) == 1)
        {
            keys_from_file_count++;
            if (keys_from_file_count >= MAX_KEYS_COUNT)
                break;
        }
        fclose(file);
    }

    int additional_key_count = MAX_KEYS_COUNT - keys_from_file_count, additional_keys[additional_key_count];

    // Initialize the random number generator with current time stamp as a seed
    srand((unsigned)time(NULL));

    // Generate additional keys
    generate_additional_keys(additional_keys, additional_key_count, 10000000UL, 100000000UL);

    // Combine keys from the file and additional keys
    for (int i = 0; i < keys_from_file_count; i++)
        test_keys[i] = keys_from_file[i];

    for (int i = keys_from_file_count; i < MAX_KEYS_COUNT; i++)
        test_keys[i] = additional_keys[i - keys_from_file_count];
}

void shuffle(int *array, int size)
{
    srand((unsigned)time(NULL));

    for (int i = size - 1; i > 0; i--)
    {
        // Generate a random index between 0 and i (inclusive)
        int j = rand() % (i + 1);

        // Swap the elements at indices i and j
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}
