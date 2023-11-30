#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <time.h>

#include "mytypes.h"

// Выделяет память для матрицы с элементами типа 'double'
ppdouble alloc_mem_ppdouble(ksize_t rows, ksize_t cols)
{
    ppdouble pp = (ppdouble)calloc(cols, sizeof(pdouble));

    if (!pp)
    {
        printf("Не удалось выделить память для каждой строки матрицы. Статус выхода =\'-1\'\n");
        exit(-1);
    }

    for (size_t row = 0UL; row < rows; row++)
    {
        pp[row] = (pdouble)calloc(rows, sizeof(double));

        if (!pp[row])
        {
            printf("Не удалось выделить память для каждой колонки матрицы. Статус выхода =\'-1\'\n");
            exit(-1);
        }
    }

    return pp;
}

// Освобождает память для матрицы типа 'double'
void dealloc_mem_ppdouble(ppdouble pp, ksize_t rows)
{
    for (size_t row = 0UL; row < rows; row++)
    {
        free(pp[row]);
    }

    free(pp);
    pp = NULL;
}

// Возвращает матрицу типа 'double' заполненную случайными числами
// от 'min' до 'max'
ppdouble input_random_ppdouble(ksize_t rows, ksize_t cols, kdouble min, kdouble max)
{
    ppdouble matrix = alloc_mem_ppdouble(rows, cols);

    srand(time(NULL));

    for (size_t row = 0UL; row < rows; row++)
    {
        for (size_t col = 0UL; col < cols; col++)
        {
            double f = (double)rand() / RAND_MAX;
            matrix[row][col] = min + f * (max - min);
        }
    }

    return matrix;
}

// Печатает матрицу с элементами типа 'double'
void print_ppdouble(ppdouble matrix, ksize_t rows, ksize_t cols)
{
    for (size_t i = 0UL; i < rows; i++)
    {
        for (size_t j = 0UL; j < cols; j++)
        {
            printf("%0.3f\t", matrix[i][j]);
        }
        printf("\n");
    }
}

// Сортирует каждую колонку матрицы в порядке возрастания
void sort_each_column_in_matrix(ppdouble matrix, ksize_t rows, ksize_t cols)
{
    // Итерация по колонкам матрицы
    for (size_t col = 0; col < cols; col++)
    {
        // Итерация по строкам матрицы
        for (size_t row = 0; row < rows - 1; row++)
        {
            // Пузырьковая сортировка
            for (size_t i = 0; i < rows - row - 1; i++)
            {
                if (matrix[i + 1][col] < matrix[i][col])
                {
                    double tmp = matrix[i][col];
                    matrix[i][col] = matrix[i + 1][col];
                    matrix[i + 1][col] = tmp;
                }
            }
        }
    }
}

void perform_task4(ksize_t rows, ksize_t cols, double min, double max)
{
    // Заполняем матрицу случайными значениями типа 'double'
    ppdouble matrix = input_random_ppdouble(rows, cols, min, max);

    printf("Изначальная матрица:\n");
    print_ppdouble(matrix, rows, cols);

    // Сортируем каждую колонку по возрастанию элементов (сверху вниз)
    sort_each_column_in_matrix(matrix, rows, cols);

    printf("Отсортированная по столбцам матрица:\n");
    print_ppdouble(matrix, rows, cols);

    // Освобождаем ранее выделеннёю память
    dealloc_mem_ppdouble(matrix, rows);
}

int main()
{
    setlocale(LC_ALL, "rus");
    perform_task4(5UL, 5UL, -1.0, 1.0);

    return 0;
}
