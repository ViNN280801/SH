#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define BYTE_SIZE 8

void print_menu()
{
    printf("1. Начать работу\n2. Выход\nВвдите значение: ");
}

void print_submenu()
{
    printf("1. Ручной ввод\n2. Заполнение случайными символами\n3. Выход\nВвдите значение: ");
}

void print_sequence_dec(const unsigned char *sequence, const size_t size)
{
    printf("seq(10):\n");
    // Итерация по последовательности символов для вывода кодов каждого символа
    for (size_t i = 0UL; i < size; i++)
    {
        printf("%d\t", (int)sequence[i]);
    }
    printf("\n");
}

void print_sequence_oct(const unsigned char *sequence, const size_t size)
{
    printf("seq(8):\n");
    // Итерация по последовательности символов для вывода кодов каждого символа
    for (size_t i = 0UL; i < size; i++)
    {
        printf("%o\t", sequence[i]);
    }
    printf("\n");
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
                    unsigned char seq[BYTE_SIZE] = {'0'};
                    printf("Введите последовательность символов: ");
                    scanf("%s", seq);

                    print_sequence_dec(seq, BYTE_SIZE);
                    print_sequence_oct(seq, BYTE_SIZE);

                    for (int i = 0; i < BYTE_SIZE; i++)
                    {
                        // Если код символа чётный
                        if ((seq[i] % 2) == 0)
                            // Замена младщего бита единицей
                            seq[i] ^= 1 << 0;
                        // В ином случае
                        else
                        {
                            // Замена двух младших битов на 0
                            seq[i] ^= 1 << 0;
                            seq[i] &= ~(1 << 1);
                        }
                    }

                    print_sequence_dec(seq, BYTE_SIZE);
                    print_sequence_oct(seq, BYTE_SIZE);

                    break;
                }
                case random_submenu:
                {
                    srand(time(NULL));

                    unsigned char seq[BYTE_SIZE] = {'0'};

                    for (int i = 0; i < BYTE_SIZE; i++)
                    {
                        // Генерация случайных маленьких английских букв
                        seq[i] = rand() % 26 + 'a';
                    }

                    print_sequence_dec(seq, BYTE_SIZE);
                    print_sequence_oct(seq, BYTE_SIZE);

                    for (int i = 0; i < BYTE_SIZE; i++)
                    {
                        // Если код символа чётный
                        if ((seq[i] % 2) == 0)
                            // Замена младщего бита единицей
                            seq[i] ^= 1 << 0;
                        // В ином случае
                        else
                        {
                            // Замена двух младших битов на 0
                            seq[i] ^= 1 << 0;
                            seq[i] &= ~(1 << 1);
                        }
                    }

                    print_sequence_dec(seq, BYTE_SIZE);
                    print_sequence_oct(seq, BYTE_SIZE);
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