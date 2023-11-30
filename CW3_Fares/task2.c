#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <time.h>

static const short int BITS_IN_ONE_BYTE = 8U;

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

/* Принимает целое число без знака (для примера взят тип unsigned char)
чтобы значения варьировались от 0 до 255
Возвращает число, полученное отзеркаливанием битов
Пример:
10010100 -> 00101001 (2)
148 -> 41 (10)
224 -> 51 (8)
 */
unsigned char mirroringBits(unsigned char value)
{
    unsigned char result = 0;

    /* Итерация по битам в размере типа 'unsigned char'
    То есть 'sizeof(unsigned char)' = 1 байт, так как в 1 байте 8 бит, то умножаем
    количество байт на количество битов в 1-ом байте */
    for (size_t i = 0; i < (sizeof(value) * BITS_IN_ONE_BYTE); i++)
    {
        int bit = value & 1;
        result <<= 1;
        result += bit;
        value >>= 1;
    }

    return result;
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
                printf("1. Ручной ввод\n2. Случайное число\n3. Выход\nВвод: ");
                submenu_var = inputInt();
                if (submenu_var == 1)
                {
                    printf("Введите число: ");
                    unsigned char number = inputInt();
                    unsigned char mirror = mirroringBits(number);
                    printf("Десятичная СС:\n%u\t%u\n", number, mirror);
                    printf("Восьмеричная СС:\n%o\t%o\n", number, mirror);
                }
                else if (submenu_var == 2)
                {
                    /* Устанавливает в качестве базы текущее время */
                    srand(time(NULL));

                    unsigned int number = rand() % 10 + 1;
                    unsigned int mirror = mirroringBits(number);
                    printf("%u\t%u\n", number, mirror);
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