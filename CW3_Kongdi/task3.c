#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <stdbool.h>
#include <malloc.h>

void print_menu()
{
    printf("1. Начать работу\n2. Выход\nВвдите значение: ");
}

void print_submenu()
{
    printf("1. Ручной ввод\n2. Заполнение случайными числами\n3. Выход\nВвдите значение: ");
}

void print_int_arr(const int *parr, const size_t arr_size)
{
    printf("\n==== ==== ==== ==== ====\nArray:\n");
    for (size_t i = 0UL; i < arr_size; i++)
    {
        printf("arr[%ld] = %d\n", i, parr[i]);
    }
    printf("==== ==== ==== ==== ====\n\n");
}

// Возвращает "true", если указатель 'p' не содержит "NULL"
bool is_alloc_int_arr(const int *p)
{
    return (!p) ? false : true;
}

// Распределяет память для указателя типа 'int' размером 'arr_size'
// Совершает проверку на выделение памяти
int *alloc_mem_int_arr(const size_t arr_size)
{
    int *p = (int *)calloc(arr_size, sizeof(int));

    if (!is_alloc_int_arr(p))
    {
        printf("Can't allocate memory for array of integers. Exiting with \'-1\' status\n");
        exit(-1);
    }

    return p;
}

// Освоождает память указателя 'p'
void dealloc_mem_int_arr(int *p)
{
    free(p);
    p = NULL;
}

// Возвращает "true", если число 'value' чётное
bool is_even(const int value)
{
    return ((value % 2 == 0) ? true : false);
}

size_t filter(int *pint, const size_t psize, bool (*pred)(const int value), int *pint_filtered)
{
    size_t filtered_size = 0UL;

    for (size_t i = 0UL; i < psize; i++)
    {
        if (pred(pint[i]))
        {
            pint_filtered[filtered_size] = pint[i];
            filtered_size++;
        }
    }
    pint_filtered = (int *)realloc(pint_filtered, sizeof(int) * filtered_size);

    return filtered_size;
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

// Возвращает указатель на массив типа 'int', который заполняется пользователем
int *input_manual_int_arr(const size_t size)
{
    int *parr = alloc_mem_int_arr(size);

    for (size_t i = 0UL; i < size; i++)
    {
        printf("parr[%ld] = ", i);
        parr[i] = input_int();
    }

    return parr;
}

// Возвращает указатель на массив типа 'int', который заполнен случайными числами
// "rand % __num1" возвращает числа от 0 до '__num1'
// добавляя '__num2' даёт число между '__num2' и '__num1 + __num2'
int *input_random_int_arr(const size_t size, const int num1, const int num2)
{
    srand(time(NULL));
    int *parr = alloc_mem_int_arr(size);

    // Заполнение случайными числами
    for (size_t i = 0UL; i < size; i++)
    {
        parr[i] = rand() % num1 + num2;
    }

    return parr;
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
                    printf("Введите размер массива: ");
                    size_t size = input_int();
                    int *arr_manual = input_manual_int_arr(size);
                    print_int_arr(arr_manual, size);

                    // Заполнение числами от 1 до 10 (просто чтобы заполнить массив числами)
                    int *arr_manual_filtered = input_random_int_arr(size, 10, 1);
                    print_int_arr(arr_manual_filtered, filter(arr_manual, size, is_even, arr_manual_filtered));

                    dealloc_mem_int_arr(arr_manual);
                    dealloc_mem_int_arr(arr_manual_filtered);
                    break;
                }
                case random_submenu:
                {
                    srand(time(NULL));

                    printf("Введите размер массива: ");
                    size_t size = input_int();

                    // Заполнение числами от 1 до 10
                    int *arr_random = input_random_int_arr(size, 10, 1);
                    print_int_arr(arr_random, size);

                    int *arr_random_filtered = input_random_int_arr(size, 10, 1);
                    print_int_arr(arr_random_filtered, filter(arr_random, size, is_even, arr_random_filtered));

                    dealloc_mem_int_arr(arr_random);
                    dealloc_mem_int_arr(arr_random_filtered);
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