#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "sorts.h"

#define N1 60000
#define N2 90000
#define N3 120000
#define N4 150000

void do_sort(enum TYPE_OF_SORT sort_type, int count_of_elements)
{
    // Allocating memory for array. Filling it with nulls
    int *unsorted_arr = (int *)calloc(count_of_elements, sizeof(int));
    if (!unsorted_arr)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Variable 'value' to write to it value from "test_numbers.txt"
    // Variable 'idx' as an index for array
    int value = 0, idx = 0;

    // Opening file in read mode
    FILE *file = fopen("test_numbers.txt", "r");
    if (!file)
    {
        fprintf(stderr, "Error opening test_numbers.txt: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Filling array with 'count_of_elements' test numbers from 'test_numbers.txt'
    while (idx < count_of_elements)
    {
        fscanf(file, "%d", &value);
        unsorted_arr[idx++] = value;
    }

    // Closing the file
    fclose(file);

    // Sorted arrays in ascending and descending order
    int *sorted_arr = copy_array(unsorted_arr, count_of_elements),
        *reverse_sorted_arr = copy_array(unsorted_arr, count_of_elements);
    qsort(sorted_arr, count_of_elements, sizeof(int), cmp_int_asc);
    qsort(reverse_sorted_arr, count_of_elements, sizeof(int), cmp_int_desc);

    // Sorting arrays with different sort algorithms
    printf("\n\33[1;36mCount of elements: %d\033[0m\033[1m\n", count_of_elements);
    switch (sort_type)
    {
    case QSORT:
    {
        printf("\33[1;33mSorting unsorted array\33[0m\33[1m\n");

        clock_t beginning_time = start_timer();      // Getting time before executing sort
        quick_sort(unsorted_arr, count_of_elements); // Performing sorting algorithm
        stop_timer_and_print_diff(beginning_time);   // Printing diff between start time and end time

        printf("\33[1;33mSorting sorted in ascending order array\33[0m\33[1m\n");

        beginning_time = start_timer();
        quick_sort(sorted_arr, count_of_elements);
        stop_timer_and_print_diff(beginning_time);

        printf("\33[1;33mSorting sorted in descending order array\33[0m\33[1m\n");
        beginning_time = start_timer();
        quick_sort(reverse_sorted_arr, count_of_elements);
        stop_timer_and_print_diff(beginning_time);
        break;
    }
    case DIRECT_MERGE_SORT:
    {
        printf("\33[1;33mSorting unsorted array\33[0m\33[1m\n");

        clock_t beginning_time = start_timer();
        merge_sort_direct(unsorted_arr, count_of_elements);
        stop_timer_and_print_diff(beginning_time);

        printf("\33[1;33mSorting sorted in ascending order array\33[0m\33[1m\n");

        beginning_time = start_timer();
        merge_sort_direct(sorted_arr, count_of_elements);
        stop_timer_and_print_diff(beginning_time);

        printf("\33[1;33mSorting sorted in descending order array\33[0m\33[1m\n");
        beginning_time = start_timer();
        merge_sort_direct(reverse_sorted_arr, count_of_elements);
        stop_timer_and_print_diff(beginning_time);
        break;
    }
    case NATURAL_MERGE_SORT:
    {
        printf("\33[1;33mSorting unsorted array\33[0m\33[1m\n");

        clock_t beginning_time = start_timer();
        merge_sort_natural(unsorted_arr, count_of_elements);
        stop_timer_and_print_diff(beginning_time);

        printf("\33[1;33mSorting sorted in ascending order array\33[0m\33[1m\n");

        beginning_time = start_timer();
        merge_sort_natural(sorted_arr, count_of_elements);
        stop_timer_and_print_diff(beginning_time);

        printf("\33[1;33mSorting sorted in descending order array\33[0m\33[1m\n");
        beginning_time = start_timer();
        merge_sort_natural(reverse_sorted_arr, count_of_elements);
        stop_timer_and_print_diff(beginning_time);
        break;
    }
    case TIMSORT:
    {
        printf("\33[1;33mSorting unsorted array\33[0m\33[1m\n");

        clock_t beginning_time = start_timer();
        timsort(unsorted_arr, count_of_elements);
        stop_timer_and_print_diff(beginning_time);

        printf("\33[1;33mSorting sorted in ascending order array\33[0m\33[1m\n");

        beginning_time = start_timer();
        timsort(sorted_arr, count_of_elements);
        stop_timer_and_print_diff(beginning_time);

        printf("\33[1;33mSorting sorted in descending order array\33[0m\33[1m\n");
        beginning_time = start_timer();
        timsort(reverse_sorted_arr, count_of_elements);
        stop_timer_and_print_diff(beginning_time);
        break;
    }
    default:
        break;
    }

    dealloc_int_ptr(unsorted_arr);
    dealloc_int_ptr(sorted_arr);
    dealloc_int_ptr(reverse_sorted_arr);
}

void invoke_sorts(int count_of_elements)
{
    do_sort(QSORT, count_of_elements);
    do_sort(DIRECT_MERGE_SORT, count_of_elements);
    do_sort(NATURAL_MERGE_SORT, count_of_elements);
    do_sort(TIMSORT, count_of_elements);
}

int main()
{
    invoke_sorts(N1);
    invoke_sorts(N2);
    invoke_sorts(N3);
    invoke_sorts(N4);

    return EXIT_SUCCESS;
}
