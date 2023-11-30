#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <time.h>

#include "constants.h"
#include "mytypes.h"

// Возвращает введённое число
// Осуществляет проверки на корректность ввода
int inputIntBasic(ksize_t buf_size)
{
    char buf[buf_size];
    scanf("%s", buf);

    // Функция atoi() конвертирует строку, на которую указывает параметр str, в
    // величину типа int. Строка должна содержать корректную запись целого числа.
    // В противном случае возвращается 0.
    while ((atoi(buf) == 0) && (buf[0] != '0'))
    {
        printf("Вы ввели не число. Попроуйте ещё раз: ");
        scanf("%s", buf);
    }

    // Возвращаем результат ввода
    return atoi(buf);
}

// Вспомогательная функция абстрагирующаяся от задания размера
// буфера как аргумент, в который будет записываться ввод пользователя
// Возвращает введённое число
// Осуществляет проверки на корректность ввода
int inputInt()
{
    return inputIntBasic(BUFFER_SIZE);
}

// Распределяет память для массива типа 'int'
// Осуществляет проверку на правильность выделения памяти
pint alloc_mem_int_arr(ksize_t size)
{
    pint p = (pint)calloc(size, sizeof(int));

    if (!p)
    {
        printf("Не удалось выделить память для массива. Статус выхода =\'-1\'\n");
        exit(-1);
    }

    return p;
}

// Освобождение памяти для массива типа 'unsigned int'
void dealloc_mem_int_arr(pint arr)
{
    free(arr);
    arr = NULL;
}

// Возвращает массив заданного размера, заполненный числами типа 'int'
pint random_fill_int_arr(ksize_t size, kint min, kint max)
{
    srand(time(NULL));
    pint arr = alloc_mem_int_arr(size);

    for (size_t i = 0UL; i < size; i++)
    {
        // Случайные числа от 'min' до 'max'
        arr[i] = rand() % max + min;
    }

    return arr;
}

void print_int_arr(kpint arr, ksize_t size)
{
    printf("Массив чисел:\n");
    for (size_t i = 0UL; i < size; i++)
    {
        printf("parr[%ld] = %d\n", i, arr[i]);
    }
    printf("\n");
}

// Возвращает первый отрицательный элемент в массиве
// Если отрицательных элементов нет, печатает сообщение и возвращает 0
size_t find_1st_negative_elem(pint arr, ksize_t size)
{
    // Поиск первого отрицательного элемента в массиве
    for (size_t i = 0UL; i < size; i++)
    {
        if (arr[i] < 0)
        {
            return i;
        }
    }

    printf("В массиве нет отрицательных элементов.\n");
    return 0UL;
}

// Возвращает ссылку на новый массив с удалённым первым отрицательным элементом
// Если отрицательных элементов нет, выводит соответствующее сообщение
pint delete_1st_negative_from_int_arr(pint arr, ksize_t size)
{
    size_t index = find_1st_negative_elem(arr, size);

    if ((index == 0UL) && (arr[0UL] >= 0))
        printf("Удаление первого отрицательного элемента отклонено.\n");

    // Выделяем на 1 ячейку памяти меньше для нового массива, так как
    // не собираемся вносить в новый массив этот элемент
    pint new_arr = alloc_mem_int_arr(size - 1UL);

    // Заполнение всеми элементами, кроме первого отрицательного
    for (size_t i = 0UL, i_new = 0UL; (i < size) && (i_new < (size - 1UL)); i++, i_new++)
    {
        new_arr[i_new] = arr[i];

        // Если наткнулись на индекс первого отрицательного элемента
        // совершаем декремент для переменной 'i_new'
        // чтобы запись произошла в верном порядке
        if (i == index)
            i_new--;
    }

    return new_arr;
}

// Возвращает массив с удалённым первым отрицательным элементом
pint task2(kint min, kint max)
{
    pint arr = random_fill_int_arr(INT_ARR_SIZE, min, max);
    print_int_arr(arr, INT_ARR_SIZE);
    return delete_1st_negative_from_int_arr(arr, INT_ARR_SIZE);
}

// Вспомогательная функция для 'task2()'
// Возвращает массив с удалённым первым отрицательным элементом
void print_task2(kint min, kint max)
{
    print_int_arr(task2(min, max), INT_ARR_SIZE - 1UL);
}

int main()
{
    // Установка русского языка
    setlocale(LC_ALL, "rus");
    print_task2(-5, 10);

    return 0;
}
