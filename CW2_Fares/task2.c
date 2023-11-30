#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <time.h>

/* Для доступа к функции memset() */
#include <string.h>

/* Инициализация переменой, хранящей в себе кол-во элементов массива */
static const int N = 40;

/* Функция возвращает "true", если в последовательности '_sequence' если
чётное число расположено после нечётного, в другом случае
возвращает "false" */
bool is_even_placed_after_odd(int *_sequence, int size)
{
    for (int index = 0; index < size; index++)
    {
        /* Если элемент последовательности '_sequence' под индексом [index] нечётный
        и элемент под индексом [index + 1] чётный, то возвращаем "true"
        Также, обязательна проверка значения [index + 1], чтобы было не больше размера
        массива 'size', иначе выйдем за пределы массива */
        if ((_sequence[index] % 2 != 0) && (_sequence[index + 1] % 2 == 0) && ((index + 1) < size))
        {
            return true;
        }
    }

    /* Во всех остальных случаях, возвращается "false" */
    return false;
}

/* Печатает на экран переданный массив */
void print_int_array(int *arr)
{
    for (int index = 0; index < N; index++)
    {
        printf("массив[%d] = %d\n", index, arr[index]);
    }
}

/* Печатает в обратном порядке на экран консоли
только положительные элементы массива 'arr' */
void print_positive_in_int_array(int *arr, int size)
{
    printf("Распечатывание только положительных элементов в обратном порядке: \n");
    /* Чтобы задать обратный порядок, необходимо развернуть
    цикл и начать с (size - 1) элемента */
    for (int index = size - 1; index >= 0; index--)
    {
        /* Если элемент положительный, печатаем на экран */
        if (arr[index] > 0)
        {
            printf("массив[%d] = %d\n", index, arr[index]);
        }
    }
}

/* Печатает в обратном порядке на экран консоли
только отрицательные элементы массива 'arr' */
void print_negative_in_int_array(int *arr, int size)
{
    printf("Распечатывание только отрицательных элементов в обратном порядке: \n");
    for (int index = size - 1; index >= 0; index--)
    {
        /* Если элемент отрицательный, печатаем на экран */
        if (arr[index] < 0)
        {
            printf("массив[%d] = %d\n", index, arr[index]);
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
    while (true)
    {
        printf("1. Ручной ввод\n2. Заполнение случайными числами\n3. Выход\n");
        menu_var = input_int();
        if (menu_var == 1)
        {
            /* Инициализация массива с заполнением всех элементов нулями */
            int arr[N];
            /* Функция memset заполняет первые n байт области памяти, на которую
            указывает аргумент destination, символом, код которого указывается аргументом c. */
            memset(arr, 0, sizeof(int) * N);

            /* Использование цикла for для присвоения каждому
            элементу пользовательского значения */
            for (int index = 0; index < N; index++)
            {
                printf("массив[%d] = ", index);
                arr[index] = input_int();
            }

            /* Если ни одно чётное число не следует после нечётного,
            печатаем на экран только отрицательные элементы массива */
            if (!is_even_placed_after_odd(&arr[0], N))
            {
                print_negative_in_int_array(&arr[0], N);
            }
            /* В ином случае печатаем только все положительные */
            else
            {
                print_positive_in_int_array(&arr[0], N);
            }
        }
        else if (menu_var == 2)
        {
            /* Устанавливает в качестве базы текущее время */
            srand(time(NULL));

            int arr[N];
            memset(arr, 0, sizeof(int) * N);

            for (int index = 0; index < N; index++)
            {
                arr[index] = rand() % 10 - 5;
            }

            /* Обеспечение распечатывания массива, путём передачи
            адреса 0-ого элемента массива */
            print_int_array(&arr[0]);

            /* Если ни одно чётное число не следует после нечётного,
            печатаем на экран только отрицательные элементы массива */
            if (!is_even_placed_after_odd(&arr[0], N))
            {
                print_negative_in_int_array(&arr[0], N);
            }
            /* В ином случае печатаем только все положительные */
            else
            {
                print_positive_in_int_array(&arr[0], N);
            }
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