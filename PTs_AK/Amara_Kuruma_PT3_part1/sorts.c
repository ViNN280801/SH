#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include "sorts.h"

int cmp_int_asc(const void *a, const void *b) { return (*(int *)a - *(int *)b); }
int cmp_int_desc(const void *a, const void *b) { return (*(int *)b - *(int *)a); }

void dealloc_int_ptr(int *p)
{
    if (p)
        free(p);
    p = NULL;
}

void swap_ints(int *a, int *b, int *assignments)
{
    // 5 and 3

    *a += *b; // 8 3
    *b -= *a; // 8 -5
    *b *= -1; // 8 5
    *a -= *b; // 3 5

    (*assignments)++;
}

void qSortAscending(int *arr, size_t size, size_t low, size_t high, int *assignments, int *comparisons)
{
    size_t i = low, j = high;

    // Select pivot value
    int pivot = arr[(i + j) / 2], tmp = 0;

    while (i <= j && i < size && j < size)
    {
        while (arr[i] < pivot && i < size)
        {
            i++;
            (*comparisons)++;
        }
        while (arr[j] > pivot && j < size)
        {
            j--;
            (*comparisons)++;
        }
        if (i <= j && i < size && j < size)
        {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
            (*comparisons)++;
            (*assignments) += 3;
        }
        (*comparisons)++;
    }
    // Recursive call sorting to left side from pivot
    if (j > low && j < size)
    {
        qSortAscending(arr, size, low, j, assignments, comparisons);
        (*comparisons)++;
    }
    // Recursive call sorting to right side from pivot
    if (i < high && i < size)
    {
        qSortAscending(arr, size, i, high, assignments, comparisons);
        (*comparisons)++;
    }
}

void quick_sort(int arr[], int size)
{
    int assignments = 0, comparisons = 0;
    qSortAscending(arr, size, 0, size - 1, &assignments, &comparisons);

    printf("%s(): Count of assignments: %d\n", __func__, assignments);
    printf("%s(): Count of comparisons: %d\n", __func__, comparisons);
    printf("%s(): Additional memory usage: %lu bytes\n", __func__, 0ul);
}

int next_run(int run) { return (run <= 1) ? 0 : (int)ceil(run / 2.0); }

void in_place_merge(int arr[], int start, int end, int *assignments, int *comparisons)
{
    int run = end - start + 1;

    for (run = next_run(run); run > 0; run = next_run(run))
    {
        for (int i = start; i + run <= end; i++)
        {
            int j = i + run;
            if (arr[i] > arr[j])
            {
                swap_ints(&arr[i], &arr[j], assignments);
                (*comparisons)++;
            }
        }
    }
}

void inPlaceMergeSort(int arr[], int s, int e, int *assignments, int *comparisons)
{
    if (s == e)
        return;

    // Calculating mid to slice the
    // array in two halves
    int mid = (s + e) / 2;

    // Recursive calls to sort left
    // and right subarrays
    inPlaceMergeSort(arr, s, mid, assignments, comparisons);
    inPlaceMergeSort(arr, mid + 1, e, assignments, comparisons);

    in_place_merge(arr, s, e, assignments, comparisons);
}

void merge_sort_direct(int arr[], int size)
{
    int assignments = 0, comparisons = 0;

    inPlaceMergeSort(arr, 0, size - 1, &assignments, &comparisons);

    printf("%s(): Count of assignments: %d\n", __func__, assignments);
    printf("%s(): Count of comparisons: %d\n", __func__, comparisons);
    printf("%s(): Additional memory usage: %lu bytes\n", __func__, 0ul);
}

void merge(int arr[], int l, int m, int r, int *assignments, int *comparisons, size_t *additional_memory_usage)
{
    int n1 = m - l + 1,
        n2 = r - m;

    // Create temporary arrays
    int L[n1], R[n2];
    *additional_memory_usage += (n1 + n2) * sizeof(int);

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
            (*comparisons)++;
            (*assignments)++;
        }
        else
        {
            arr[k] = R[j];
            j++;
            (*comparisons)++;
            (*assignments)++;
        }
        k++;
        (*comparisons)++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
        (*comparisons)++;
        (*assignments)++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
        (*comparisons)++;
        (*assignments)++;
    }
}

void mergeSort(int arr[], int l, int r, int *assignments, int *comparisons, size_t *additional_memory_usage)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m, assignments, comparisons, additional_memory_usage);
        mergeSort(arr, m + 1, r, assignments, comparisons, additional_memory_usage);

        // Merge the sorted halves
        merge(arr, l, m, r, assignments, comparisons, additional_memory_usage);
    }
}

void merge_sort_natural(int arr[], int size)
{
    int assignments = 0, comparisons = 0;
    size_t additional_memory_usage = 0ul;

    mergeSort(arr, 0, size - 1, &assignments, &comparisons, &additional_memory_usage);

    printf("%s(): Count of assignments: %d\n", __func__, assignments);
    printf("%s(): Count of comparisons: %d\n", __func__, comparisons);
    printf("%s(): Additional memory usage: %lu bytes\n", __func__, additional_memory_usage);
}

void insertionSortForTimsort(int arr[], int left, int right, int *assignments, int *comparisons)
{
    for (int i = left + 1; i <= right; i++)
    {
        int key = arr[i], j = i - 1;
        while (j >= left && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
            (*assignments)++;
            (*comparisons)++;
        }
        arr[j + 1] = key;
        (*assignments)++;
    }
}

void timsort(int arr[], int n)
{
    int assignments = 0, comparisons = 0;
    size_t additional_memory_usage = 0ul;

    for (int i = 0; i < n; i += RUN)
        insertionSortForTimsort(arr, i, min((i + RUN - 1), (n - 1)), &assignments, &comparisons);

    for (int size = RUN; size < n; size = 2 * size)
    {
        for (int left = 0; left < n; left += 2 * size)
        {
            int mid = min((left + size - 1), (n - 1));
            int right = min((left + 2 * size - 1), (n - 1));
            merge(arr, left, mid, right, &assignments, &comparisons, &additional_memory_usage);
        }
    }

    printf("%s(): Count of assignments: %d\n", __func__, assignments);
    printf("%s(): Count of comparisons: %d\n", __func__, comparisons);
    printf("%s(): Additional memory usage: %lu bytes\n", __func__, additional_memory_usage);
}

int *copy_array(int *a, int size)
{
    int *b = (int *)calloc(size, sizeof(int));
    if (!b)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++)
        b[i] = a[i];

    return b;
}

void print_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        printf("arr[%d] = %d\n", i, arr[i]);
}

clock_t start_timer() { return clock(); }

void stop_timer_and_print_diff(clock_t beginning_time)
{
    clock_t endTime = clock();
    double duration_ms = ((double)(endTime - beginning_time) / CLOCKS_PER_SEC) * 1000.0;
    printf("\033[1;34mExecution time: %.3fms\033[0m\033[1m\n\n", duration_ms);
}
