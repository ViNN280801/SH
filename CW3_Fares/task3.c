#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <time.h>

/* Печатает на экран переданный массив */
void printCharArray(char *arr, int size)
{
    for (int index = 0; index < size; index++)
    {
        printf("массив[%d] = %c\n", index, arr[index]);
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

/* Предикат, который возвращает "true", если английская буква
в нижнем регистре */
bool isLower(char ch)
{
    return ((ch == 'a') || (ch == 'b') || (ch == 'c') || (ch == 'd') ||
            (ch == 'e') || (ch == 'f') || (ch == 'g') || (ch == 'h') ||
            (ch == 'i') || (ch == 'j') || (ch == 'k') || (ch == 'l') ||
            (ch == 'm') || (ch == 'n') || (ch == 'o') || (ch == 'p') ||
            (ch == 'q') || (ch == 'r') || (ch == 's') || (ch == 't') ||
            (ch == 'u') || (ch == 'v') || (ch == 'w') || (ch == 'x') ||
            (ch == 'z') || (ch == 'z'))
               ? true
               : false;
}

/* Отфильтровывает все буквы в верхнем регистре, возвращает размер отфильтрованного массива */
int filter(char *arr, int arr_size, bool (*isLetterLowerPredicate)(char), char *new_arr)
{
    int new_size = 0;

    for (int i = 0; i < arr_size; i++)
    {
        /* Если буква в нижнем регистре, записываем её в массив */
        if (isLetterLowerPredicate(arr[i]))
        {
            new_arr[new_size] = arr[i];
            new_size++;
        }
    }

    return new_size;
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
        menu_var = inputInt();

        if (menu_var == 1)
        {
            /* Подменю */
            while (true)
            {
                printf("1. Ручной ввод\n2. Случайная последовательность сиволов\n3. Выход\nВвод: ");
                submenu_var = inputInt();
                if (submenu_var == 1)
                {
                    printf("Введите размер массива: ");
                    int arr_size = inputInt();
                    char arr[arr_size], filtered_arr[arr_size];

                    /* Ручное заполнение массива */
                    for (int i = 0; i < arr_size; i++)
                    {
                        printf("arr[%d] = ", i);
                        getchar();
                        scanf("%c", &arr[i]);
                    }

                    printf("Исходный массив:\n");
                    printCharArray(&arr[0], arr_size);
                    printf("Новый массив:\n");
                    printCharArray(&filtered_arr[0], filter(&arr[0], arr_size, isLower, &filtered_arr[0]));
                }
                else if (submenu_var == 2)
                {
                    /* Устанавливает в качестве базы текущее время */
                    srand(time(NULL));

                    /* Размер массива варьируется от 0 до 10 */
                    int arr_size = rand() % 10 + 1;
                    char arr[arr_size], filtered_arr[arr_size];

                    /* Автоматическое заполнение половины 
                    массива заглавными английскими буквами */
                    for (int i = 0; i < (arr_size / 2); i++)
                    {
                        arr[i] = rand() % 26 + 'A';
                    }

                    /* Автоматическое заполнение второй половины 
                    массива строчными английскими буквами */
                    for (int i = (arr_size / 2); i < arr_size; i++)
                    {
                        arr[i] = rand() % 26 + 'a';
                    }

                    printf("Исходный массив:\n");
                    printCharArray(&arr[0], arr_size);
                    printf("Новый массив:\n");
                    printCharArray(&filtered_arr[0], filter(&arr[0], arr_size, isLower, &filtered_arr[0]));
                }
                else if (submenu_var == 3)
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
        if (menu_var == 2)
        {
            printf("Выход ...\n");
            exit(0);
        }
        else if (menu_var != 1 && menu_var != 2)
        {
            printf("Ошибка ввода, попробуйте ещё раз\n");
        }
    }
    /* Конец меню */
}