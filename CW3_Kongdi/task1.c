#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <malloc.h>
#include <stdbool.h>

void print_menu()
{
    printf("1. Начать работу\n2. Выход\nВвдите значение: ");
}

void print_submenu()
{
    printf("1. Ручной ввод\n2. Заполнение случайными числами\n3. Выход\nВвдите значение: ");
}

void print_matrix(int **matrix, const size_t rows, const size_t cols)
{
    printf("\n==== ==== ==== ==== ==== ==== ==== ==== ====\nMatrix:\n");
    for (size_t row = 0UL; row < rows; row++)
    {
        for (size_t col = 0UL; col < cols; col++)
        {
            printf("%d\t", matrix[row][col]);
        }
        printf("\n");
    }
    printf("==== ==== ==== ==== ==== ==== ==== ==== ====\n\n");
}

// Возвращает "true", если память для матрицы выделена успешно
bool is_alloc_int_matrix(const int **matrix, const size_t rows)
{
    for (size_t row = 0UL; row < rows; row++)
    {
        if (!matrix[row])
            return false;
    }
    if (!matrix)
        return false;

    return true;
}

// Возвращает указатель на указатель на значение типа "int"
// Распределяет память для матрицы типа "int" с проверками
int **alloc_mem_int_matrix(const size_t rows, const size_t cols)
{
    int **pp = (int **)calloc(cols, sizeof(int *));

    if (!pp)
    {
        printf("Can't allocate memory for each row of matrix. Exiting with \'-1\' status\n");
        exit(-1);
    }

    for (size_t row = 0UL; row < rows; row++)
    {
        pp[row] = (int *)calloc(rows, sizeof(int));

        if (!pp[row])
        {
            printf("Can't allocate memory for each column of matrix. Exiting with \'-1\' status\n");
            exit(-1);
        }
    }

    return pp;
}

// Освобождает память матрицы
void dealloc_mem_int_matrix(int **matrix, const size_t rows)
{
    for (size_t row = 0UL; row < rows; row++)
    {
        free(matrix[row]);
    }

    free(matrix);
    matrix = NULL;
}

void fill_matrix_with_some_value(int **matrix, const size_t rows, const size_t cols, const int some_value)
{
    for (size_t row = 0UL; row < rows; row++)
    {
        for (size_t col = 0UL; col < cols; col++)
        {
            // Заполнение диагонали значением 'some_value'
            if (row == col)
                matrix[row][col] = some_value;
            // Заполнение элементов выше диагонали нулями
            else if (row < col)
                matrix[row][col] = 0;
            // Заполнение элементов ниже диагонали убывающими значениями
            // от 'some_value'
            else
                matrix[row][col] = some_value - row + col;
        }
    }
}

// Возвращает число, введённое пользователем
// Обрабатывает возможный ввод символов или строки
int input_int()
{
    char buffer[256] = {0};
    scanf("%s", buffer);
    while ((atoi(buffer) == 0) && (buffer[0] != '0'))
    {
        printf("Вы ввели не число. Попробуйте снова: ");
        scanf("%s", buffer);
    }
    return atoi(buffer);
}

enum Menu
{
    start_menu = 1,
    exit_menu = 2
};

enum subMenu
{
    manual_submenu = 1,
    random_submenu = 2,
    exit_submenu = 3
};

// Выполняет определённое действие
void perform_some_functionality()
{
    while (1)
    {
        print_menu();
        enum Menu input_menu = input_int();

        switch (input_menu)
        {
        case start_menu:
        {
            int flag = 0;

            while (flag != 1)
            {
                print_submenu();
                enum subMenu input_submenu;
                input_submenu = input_int();

                switch (input_submenu)
                {
                case manual_submenu:
                {
                    printf("Введите m для построения квадратной матрицы: ");
                    int m = input_int();
                    int **matrix_man = alloc_mem_int_matrix((size_t)m, (size_t)m);
                    fill_matrix_with_some_value(matrix_man, (size_t)m, (size_t)m, m);
                    print_matrix(matrix_man, (size_t)m, (size_t)m);
                    dealloc_mem_int_matrix(matrix_man, (size_t)m);
                    break;
                }
                case random_submenu:
                {
                    srand(time(NULL));
                    int m = rand() % 10 + 1; // от 1 до 10
                    printf("m = %d\n", m);
                    int **matrix_man = alloc_mem_int_matrix((size_t)m, (size_t)m);
                    fill_matrix_with_some_value(matrix_man, (size_t)m, (size_t)m, m);
                    print_matrix(matrix_man, (size_t)m, (size_t)m);
                    dealloc_mem_int_matrix(matrix_man, (size_t)m);
                    break;
                }
                case exit_submenu:
                {
                    printf("Выход из подменю ...\n");
                    flag = 1;
                    break;
                }
                default:
                    printf("Неверный ввод, попробуйте снова\n");
                    break;
                }
            }
            break;
        }
        case exit_menu:
        {
            printf("Выход из программы ...\n");
            exit(1);
        }
        default:
            printf("Неверный ввод, попробуйте снова\n");
            break;
        }
    }
}

int main()
{
    // Подключение локализации русского языка
    setlocale(LC_ALL, "rus");
    perform_some_functionality();

    return 0;
}