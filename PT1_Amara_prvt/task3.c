#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <time.h>

#include "constants.h"
#include "mytypes.h"

// Возвращает модуль числа
double module(kdouble number)
{
    return (number < 0) ? (number * (-1)) : number;
}

// Возвращает максимальный по модулю элемент в последовательности
// 'arr' - массив, в котором происходит поиск
// 'size' - размер массива, в котором происходит поиск
double find_max(kpdouble arr, ksize_t size)
{
    double max = arr[0];

    for (size_t i = 0UL; i < size; i++)
    {
        // Если максимальный элемент меньше, чем 'arr[i]'
        // присваиваем значение 'arr[i]' в 'max'
        if (max < arr[i])
            max = arr[i];
    }

    return max;
}

// Печатает массив с элементами типа 'double'
void print_pdouble(kpdouble arr, ksize_t size)
{
    printf("Массив чисел:\n");
    for (size_t i = 0UL; i < size; i++)
    {
        printf("parr[%ld] = %0.3f\n", i, arr[i]);
    }
    printf("\n");
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

// Выделяет память для массива с элементами типа 'double'
pdouble alloc_mem_pdouble(ksize_t size)
{
    pdouble p = (pdouble)calloc(size, sizeof(double));

    if (!p)
    {
        printf("Не удалось выделить память для масссива с элементами типа 'double'. Статус выхода =\'-1\'\n");
        exit(-1);
    }

    return p;
}

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

// Освобождает память для массива типа 'double'
void dealloc_mem_pdouble(pdouble p)
{
    free(p);
    p = NULL;
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

// Возвращает все максимальные по модулю элементы из матрицы
pdouble all_max_from_rows(ppdouble matrix, ksize_t rows, ksize_t cols)
{
    // Так как в массиве будет содержаться максимальные по модулю элементы каждой строки
    // выделяем память, используя количество строк матрицы
    pdouble arr = alloc_mem_pdouble(rows);

    for (size_t i = 0UL; i < rows; i++)
    {
        double tmp[cols];

        for (size_t j = 0UL; j < cols; j++)
        {
            // Заполняем временный статический массив модулями элементов каждой строки отдельно
            tmp[j] = module(matrix[i][j]);
        }

        // Находим наибольший элемент во временном массиве
        double max = find_max(tmp, MATRIX_B_COLS);

        // Заполняем 'arr' всеми максимальными по модулю значениями
        arr[i] = max;
    }

    return arr;
}

// Возвращает 0 если все числа (по модулю) в строке матрицы одинаковые
// 1 в ином случае
int is_all_same_in_row(ppdouble matrix, ksize_t rows, ksize_t cols, ksize_t certain_col)
{
    for (size_t i = 0UL; i < rows; i++)
    {
        double tmp = matrix[i][certain_col];

        for (size_t j = 0UL; j < cols; j++)
        {
            if (tmp != matrix[i][j])
                return 1;
        }
    }

    return 0;
}

// Меняет знак максимального по модулю элемента в каждой строке матрицы на противоположный
void change_sign_of_modulemax_in_each_row(ppdouble matrix, ksize_t rows, ksize_t cols)
{
    pdouble arr = all_max_from_rows(matrix, rows, cols);
    print_pdouble(arr, rows);

    // Итерация по строкам матрицы
    for (size_t i = 0UL; i < rows; i++)
    {
        // Итерация по столбцам матрицы
        for (size_t j = 0UL; j < cols; j++)
        {
            // Провекрка на то, чтобы все элементы строки матрицы были одинаковые
            if (is_all_same_in_row(matrix, rows, cols, j) == 1)
            {
                // Итерация по элементам массива
                for (size_t arr_index = 0UL; arr_index < rows; arr_index++)
                {
                    // Если нашли совпадение элемента из массива максимальных
                    // по модулю элементов, заменяем знак
                    if (arr[arr_index] == module(matrix[i][j]))
                    {
                        matrix[i][j] *= (-1.0);
                    }
                }
            }
        }
    }

    dealloc_mem_pdouble(arr);
}

void perform_task3(ksize_t rows, ksize_t cols)
{
    // Заполняем матрицу случайными числами
    ppdouble matrix = input_random_ppdouble(rows, cols, -10.5, 10.5);

    // Выводим матрицу
    print_ppdouble(matrix, rows, cols);

    // Изменяем знак максимальных по модулю элементов на противоположный
    change_sign_of_modulemax_in_each_row(matrix, rows, cols);

    // Выводим матрицу
    print_ppdouble(matrix, rows, cols);

    // Освобождаем память матрицы
    dealloc_mem_ppdouble(matrix, rows);
}

int main()
{
    setlocale(LC_ALL, "rus");
    perform_task3(MATRIX_B_ROWS, MATRIX_B_COLS);

    return 0;
}
