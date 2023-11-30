#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>

#include "constants.h"

// Заполняет коробку с лотками яиц значениями 0 или 1,
// где 1 - целое яйцо, 0 - разбитое
// используется тип 'unsigned' для меньшей затратности на память
// 'unsined' подрузумевает под собой 'unsigned char', который содержит 1 байт
// следовательно беззнаковое 8 битное число (от 00000000 до 11111111) или
// от 1 до 255
void random_fill_boxes_and_trays(unsigned box[BOX_ROWS][BOX_COLS][TRAY_ROWS][TRAY_COLS])
{
    srand(time(NULL));

    /* Итерация по коробке: */
    // Итерация по рядам лотков в коробке
    for (int box_row = 0; box_row < BOX_ROWS; box_row++)
    {
        // Итерация по стопкам лотков в коробке
        for (int box_col = 0; box_col < BOX_COLS; box_col++)
        {
            /* Итерация внутри яичного лотка */
            // Итерация по рядам лотка
            for (int tray_row = 0; tray_row < TRAY_ROWS; tray_row++)
            {
                // Итерация по "колонкам" лотка
                for (int tray_col = 0; tray_col < TRAY_COLS; tray_col++)
                {
                    // Такой 'rand()' будет генерировать 0 или 1
                    box[box_row][box_col][tray_row][tray_col] = rand() % 2;
                }
            }
            /* Итерация внутри яичного лотка закончена */
        }
    }
    /* Итерация по коробке закончена */
}

void print_box_with_egg_trays(unsigned box[BOX_ROWS][BOX_COLS][TRAY_ROWS][TRAY_COLS])
{
    for (int box_row = 0; box_row < BOX_ROWS; box_row++)
    {
        for (int box_col = 0; box_col < BOX_COLS; box_col++)
        {
            for (int tray_row = 0; tray_row < TRAY_ROWS; tray_row++)
            {
                for (int tray_col = 0; tray_col < TRAY_COLS; tray_col++)
                {
                    printf("%u ", box[box_row][box_col][tray_row][tray_col]);
                }
                printf("\t");
            }
            printf("\n");
        }
    }
}

// Вычисляет и возвращает процент разбитых яиц
double percentage_of_broken_eggs(unsigned box[BOX_ROWS][BOX_COLS][TRAY_ROWS][TRAY_COLS])
{
    // Количество разбитых яиц
    int count = 0;

    for (int box_row = 0; box_row < BOX_ROWS; box_row++)
    {
        for (int box_col = 0; box_col < BOX_COLS; box_col++)
        {
            for (int tray_row = 0; tray_row < TRAY_ROWS; tray_row++)
            {
                for (int tray_col = 0; tray_col < TRAY_COLS; tray_col++)
                {
                    // Если яйцо разбито, увеличиваем переменную 'count'
                    if (box[box_row][box_col][tray_row][tray_col] == 0)
                        count++;
                }
            }
        }
    }

    return (((double)count * 100.0) / EGG_COUNT_IN_ONE_BOX);
}

// Печатает индексы разбитых яиц с поясненими
void print_indeces_of_broken_eggs(unsigned box[BOX_ROWS][BOX_COLS][TRAY_ROWS][TRAY_COLS])
{
    printf("Битые яйца находятся по следующим индексам:\n");
    for (int box_row = 0; box_row < BOX_ROWS; box_row++)
    {
        for (int box_col = 0; box_col < BOX_COLS; box_col++)
        {
            for (int tray_row = 0; tray_row < TRAY_ROWS; tray_row++)
            {
                for (int tray_col = 0; tray_col < TRAY_COLS; tray_col++)
                {
                    // Если разбитое, выводим соответсвующее сообщение
                    if (box[box_row][box_col][tray_row][tray_col] == 0)
                    {
                        printf("Ряд №%d\t\tСтопка №%d\nРяд лотка №%d\tКолонка лотка №%d\n",
                               box_row, box_col, tray_row, tray_col);
                    }
                }
                printf("\n");
            }
        }
    }
}

void perform_task5()
{
    unsigned box[BOX_ROWS][BOX_COLS][TRAY_ROWS][TRAY_COLS];
    random_fill_boxes_and_trays(box);
    print_box_with_egg_trays(box);
    printf("Процент разбитых яиц = %0.2f%%\n", percentage_of_broken_eggs(box));
    print_indeces_of_broken_eggs(box);
}

int main()
{
    setlocale(LC_ALL, "rus");
    perform_task5();

    return 0;
}
