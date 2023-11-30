#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <time.h>

/* Печатает на экран переданный массив */
void printDoubleArray(double *arr, int size)
{
    for (int index = 0; index < size; index++)
    {
        printf("массив[%d] = %0.3f\n", index, arr[index]);
    }
}

void printDoubleMatrix(double **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%0.3f\t", matrix[i][j]);
        }
        printf("\n");
    }
}

/* Обрабатывает ошибку ввода пользователем символа или строки,
когда его просят ввести число. Возвращает число, введённое пользователем */
int inputInt()
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

// Распределет память для матрицы типа 'double'
double **allocMemoryForDoubleMatrix(int rows, int cols)
{
    double **pp = (double **)calloc(cols, sizeof(double *));

    if (!pp)
    {
        printf("Can't allocate memory for each row of matrix. Exiting with \'-1\' status\n");
        exit(-1);
    }

    for (int row = 0; row < rows; row++)
    {
        pp[row] = (double *)calloc(rows, sizeof(double));

        if (!pp[row])
        {
            printf("Can't allocate memory for each column of matrix. Exiting with \'-1\' status\n");
            exit(-1);
        }
    }

    return pp;
}

/* Освобождение памяти для матрицы */
void deallocMemoryForDoubleMatrix(double **pp, int rows)
{
    for (int row = 0; row < rows; row++)
    {
        free(pp[row]);
        pp[row] = NULL;
    }

    free(pp);
    pp = NULL;
}

int main(void)
{
    /* Подключение русского языка */
    setlocale(LC_ALL, "rus");

    /* Переменная отвечающая за выбор пунктов меню */
    int menu_var = 0, submenu_var = 0;

    /* Меню */
    while (true)
    {
        printf("1. Начало работы\n2. Выход\nВвод: ");
        submenu_var = inputInt();

        if (submenu_var == 1)
        {
            /* Подменю */
            while (true)
            {
                printf("1. Ручной ввод\n2. Заполнение случайными числами\n3. Выход\nВвод: ");
                menu_var = inputInt();
                if (menu_var == 1)
                {
                    int m = 0;
                    printf("Введите размер количество строк/колонок (матрица квадратная): ");
                    while (true)
                    {
                        m = inputInt();

                        if ((m > 7) || (m < 0))
                            printf("Неверно введён размер. Попробуйте снова: ");
                        else
                            break;
                    }

                    /* Выделение памяти */
                    double *p = (double *)calloc((size_t)(m * m), sizeof(double));

                    /* Проверка на правильность выделения памяти */
                    if (p == NULL)
                    {
                        printf("Не удалось выделить память для массива. Принудительный выход.\n");
                        exit(-1);
                    }

                    /* Ручное заполнение */
                    for (int i = 0; i < (m * m); i++)
                    {
                        printf("p[%d] = ", i);
                        scanf("%lf", &p[i]);
                    }

                    double **matrix = allocMemoryForDoubleMatrix(m, m);

                    int index = 0;
                    for (int i = 0; i < m; i++)
                    {
                        if ((i % 2) == 0)
                        {
                            for (int j = 0; j < m; j++)
                            {
                                matrix[i][j] = p[index];
                                index++;
                            }
                        }
                        else
                        {
                            for (int j = m - 1; j >= 0; j--)
                            {
                                matrix[i][j] = p[index];
                                index++;
                            }
                        }
                    }

                    printDoubleArray(p, m * m);
                    printDoubleMatrix(matrix, m, m);

                    /* Освобождение памяти */
                    deallocMemoryForDoubleMatrix(matrix, m);
                    free(p);
                    p = NULL;
                }
                else if (menu_var == 2)
                {
                    /* Устанавливает в качестве базы текущее время */
                    srand(time(NULL));

                    /* Число от 1 до 7 */
                    int m = rand() % 7 + 1;

                    /* Выделение памяти */
                    double *p = (double *)calloc((size_t)(m * m), sizeof(double));

                    /* Проверка на правильность выделения памяти */
                    if (p == NULL)
                    {
                        printf("Не удалось выделить память для массива. Принудительный выход.\n");
                        exit(-1);
                    }

                    /* Заполнение случайными числами */
                    for (int i = 0; i < (m * m); i++)
                    {
                        double f = (double)rand() / RAND_MAX;
                        p[i] = 1 + f * 9;
                    }

                    double **matrix = allocMemoryForDoubleMatrix(m, m);

                    int index = 0;
                    for (int i = 0; i < m; i++)
                    {
                        if ((i % 2) == 0)
                        {
                            for (int j = 0; j < m; j++)
                            {
                                matrix[i][j] = p[index];
                                index++;
                            }
                        }
                        else
                        {
                            for (int j = m - 1; j >= 0; j--)
                            {
                                matrix[i][j] = p[index];
                                index++;
                            }
                        }
                    }

                    printDoubleArray(p, m * m);
                    printDoubleMatrix(matrix, m, m);

                    /* Освобождение памяти */
                    deallocMemoryForDoubleMatrix(matrix, m);
                    free(p);
                    p = NULL;
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
            /* Конец подменю */
        }
        else if (submenu_var == 2)
        {
            printf("Выход ...\n");
            exit(0);
        }
        else if (submenu_var != 1 && submenu_var != 2)
        {
            printf("Ошибка ввода, попробуйте ещё раз\n");
        }
    }
    /* Конец меню */
}