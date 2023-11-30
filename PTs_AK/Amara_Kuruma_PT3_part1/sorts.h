#ifndef SORTS_H
#define SORTS_H

#include <time.h>

#define RUN 32
#define min(a, b) ((a < b) ? a : b)

enum TYPE_OF_SORT
{
    QSORT,
    DIRECT_MERGE_SORT,
    NATURAL_MERGE_SORT,
    TIMSORT
};

// Compare funcs
int cmp_int_asc(const void *a, const void *b);
int cmp_int_desc(const void *a, const void *b);

// Deallocates memory from integer pointer
void dealloc_int_ptr(int *p);

// Sorts array in ascending order
void quick_sort(int arr[], int size);
void merge_sort_direct(int arr[], int size);
void merge_sort_natural(int arr[], int size);
void timsort(int arr[], int size);

// Copying one array to another
int *copy_array(int *a, int size);

// Prints array to the terminal
void print_array(int arr[], int size);

// Starts the timer
clock_t start_timer();

// Stops the timer and print the execution time
void stop_timer_and_print_diff(clock_t beginning_time);
#endif // !SORTS_H
