#ifndef GENERATE_KEYS_H
#define GENERATE_KEYS_H

// Define the maximum number of keys to generate
#define MAX_KEYS_COUNT 100

// Function to generate keys for the test set
void generate_test_keys(int *test_keys);

// Reorder  the elements in the given array
void shuffle(int *array, int size);

#endif // !GENERATE_KEYS_H