#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int get_matrix_size()
{
    int m = 0;
    for (;;)
    {
        printf("Enter size of the square matrix (size < 8): ");
        assert(scanf("%d", &m) != EOF);
        if (m > 0 && m < 8)
            break;
    }

    return m;
}

// n - count of real numbers.
// Returns NULL if can't allocate memory.
double *get_real_numbers(int n)
{
    if (n <= 0)
        return NULL;

    double *nums = calloc(n, sizeof(double));
    if (!nums)
    {
        printf("Can't allocate memory\n");
        return NULL;
    }
    
    for (int i = 0; i < n; ++i)
    {
        assert(printf("nums[%d] = ", i) > 0);
        assert(scanf("%lf", &nums[i]) != EOF);
    }

    return nums;
}

double **arrange_nums_in_matrix(double const *const nums, int n)
{
    if (!nums || n < 0)
        return NULL;
    double **matrix = calloc(n, sizeof(double));
    if (!matrix)
    {
        printf("Can't allocate memory for matrix\n");
        return NULL;
    }
    for (int i = 0; i < n; ++i)
    {
        matrix[i] = calloc(n, sizeof(double));
        if (!matrix[i])
        {
            assert(printf("Can't allocate memory for %d column\n", i) > 0);
            return NULL;
        }
    }

    int index = 0;
    for (int col = 0; col < n; ++col) 
    {
        if (col % 2 == 0)
        {
            // Fill downwards
            for (int row = 0; row < n; ++row)
                matrix[row][col] = nums[index++];
        } 
        else 
        {
            // Fill upwards
            for (int row = n - 1; row >= 0; --row)
                matrix[row][col] = nums[index++];
        }
    }

    return matrix;
}

// p - matrix with elements of type 'double'.
// n - size of square matrix.
void print_sqmatrix(double const *const *const p, int n)
{
    if (n <= 0 || !p || !p[0])
        return;

    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < n; ++col)
            assert(printf("%lf\t", p[row][col]) > 0);
        printf("\n");
    }
}

int main()
{
    int m = get_matrix_size();
    double *nums = get_real_numbers(m * m);
    if (!nums)
    {
        printf("Smth went wrong in get_real_numbers() function\n");
        return 1;
    }

    printf("Elements:\n");
    for (int i = 0; i < m * m; ++i)
        assert(printf("%lf ", nums[i]) > 0);
    printf("\n\n");

    double **matrix = arrange_nums_in_matrix(nums, m);
    if (!matrix)
    {
        printf("Smth went wrong in arrange_nums_in_matrix() function\n");
        return 1;
    }

    printf("Matrix:\n");
    print_sqmatrix((double const *const *const)matrix, m);

    if (nums)
        free(nums);
    
    for (int i = 0; i < m; ++i) 
        if (matrix[i])
            free(matrix[i]);
    if (matrix)
        free(matrix);

    return 0;
}

