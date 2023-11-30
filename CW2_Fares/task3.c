#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

/* Для доступа к функции memset() */
#include <string.h>

/* Инициализация переменных, хранящих в себе
размеры двумерного массива */
static const int N = 5;
static const int M = 4;

/* Печатает на экран переданный массив */
void print_int_array(int *arr, int size)
{
    for (int index = 0; index < size; index++)
    {
        printf("массив[%d] = %d\n", index, arr[index]);
    }
}

/* Печатает на экран двумерный массив */
void print_2d_array(int rows, int cols, int arr[rows][cols])
{
    /* Итерация по строкам */
    for (int row = 0; row < rows; row++)
    {
        /* Итерация по колонкам */
        for (int col = 0; col < cols; col++)
        {
            printf("%d\t", arr[row][col]);
        }
        printf("\n");
    }
}

/* Возвращает указатель на одномерный массив, который
содержит в себе сохранённый первый столбец исходной матрицы */
int *save_first_column(int rows, int cols, int arr[rows][cols])
{
    /* Инициализация переменной, которая будет хранить в себе первый столбец */
    int first_column[cols];

    /* Заполнение нулевыми значениями массива 'first_column' */
    memset(first_column, 0, sizeof(int) * cols);

    /* Так как нужно сохранить первый столбец (0 столбец)
    то итерируем по строкам, а столбец остаётся неизменным, т.е. 0 */
    for (int row = 0; row < rows; row++)
    {
        first_column[row] = arr[row][0];
    }

    /* Инициализация указателя на массив, чтобы вернуть этот указатель */
    int *p = &(first_column[0]);

    return p;
}

/* Возвращает сумму всех отрицательных элементов матрицы */
int sum_of_negative(int rows, int cols, int arr[rows][cols])
{
    /* Инициализация переменной, которая будет
    содержать в себе сумму всех отрицательных элементов */
    int sum = 0;

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            /* Если элемент отрицательный, прибавляем его к переменной 'sum' */
            if (arr[row][col] < 0)
            {
                sum += arr[row][col];
            }
        }
    }

    return sum;
}

/* Преобразует исходную матрицу следующим образом:
В каждой нечётной строке заменяет суммой всех
отрицательных элементов элемент i-ой строки первого столбца (0-ого столбца) */
void transformed_matrix(int rows, int cols, int arr[rows][cols])
{
    /* Инициализация переменной 'sum', хранящей в себе значение суммы
    всех отрицательных элементов матрицы */
    int sum = sum_of_negative(rows, cols, arr);

    for (int row = 0; row < N; row++)
    {
        /* Если строка 'row' - нечётная */
        if ((row % 2) != 0)
        {
            /* Заменяем элемент i-ой строки первого столбца на сумму, вычисленную ранее */
            arr[row][0] = sum;
        }
    }
}

/* Обрабатывает ошибку ввода пользователем символа или строки,
когда его просят ввести число. Возвращает число, введённое пользователем */
int input_int()
{
    /* Инициализация массива */
    char buf[256] = {0};
    scanf("%s", buf);

    /* int atoi(const char *str)
    Функция atoi() конвертирует строку, на которую указывает параметр str,
    в величину типа int. Строка должна содержать корректную запись целого числа.
    В противном случае возвращается 0 */
    while ((atoi(buf) == 0) && (buf[0] != '0'))
    {
        printf("Ошибка ввода. Введите число: ");
        scanf("%s", buf);
    }
    return atoi(buf);
}

int main(void)
{
    /* Подключение русского языка */
    setlocale(LC_ALL, "rus");

    /* Переменная отвечающая за выбор пунктов меню */
    int menu_var = 0;

    /* Меню */
    while (1)
    {
        printf("1. Ручной ввод\n2. Заполнение случайными числами\n3. Выход\nВведите значение: ");
        menu_var = input_int();
        if (menu_var == 1)
        {
            /* Объявление переменной двумерного массива */
            int arr_2d[N][M];

            /* Заполнение всех элементов двумерного массива нулями
            (Инициализация элементов, заполненных так называемым "информационным мусором") */
            memset(arr_2d, 0, sizeof(arr_2d));

            /* Ручное заполнение 2d массива */
            for (int row = 0; row < N; row++)
            {
                for (int col = 0; col < M; col++)
                {
                    printf("2D массив[%d][%d] = ", row, col);
                    arr_2d[row][col] = input_int();
                }
            }

            printf("\nИсходная матрица:\n");
            print_2d_array(N, M, arr_2d);

            /* Инициализация указателя, который хранит в себе ссылку на первый элемент массива,
            содержащего в себе первую (нулевой) колонку исходной матрицы */
            printf("Первая колонка исходной матрицы:\n");
            int *p = save_first_column(N, M, arr_2d);

            /* Распечатывание на экран сохраненной первой (нулевой) колонки исходной матрицы  */
            print_int_array(p, N);

            /* Присвоение указателю специального значения NULL,
            тем самым определяя его как указатель, указывающий вникуда */
            p = NULL;

            /* Преобразуем матрицу и печатаем её на экран консоли */
            transformed_matrix(N, M, arr_2d);
            print_2d_array(N, M, arr_2d);
        }
        else if (menu_var == 2)
        {
            /* Устанавливает в качестве базы текущее время */
            srand(time(NULL));

            int arr_2d[N][M];
            memset(arr_2d, 0, sizeof(arr_2d));

            for (int row = 0; row < N; row++)
            {
                for (int col = 0; col < M; col++)
                {
                    arr_2d[row][col] = rand() % 10 - 5;
                }
            }

            printf("\nИсходная матрица:\n");
            print_2d_array(N, M, arr_2d);

            printf("Первая колонка исходной матрицы:\n");
            int *p = save_first_column(N, M, arr_2d);
            print_int_array(p, N);
            p = NULL;

            transformed_matrix(N, M, arr_2d);
            print_2d_array(N, M, arr_2d);
        }
        else if (menu_var == 3)
        {
            printf("Выход ...\n");
            break;
        }
        else
        {
            printf("Ошибка ввода, попробуйте ещё раз\n");
        }
    }
    /* Конец меню */
}