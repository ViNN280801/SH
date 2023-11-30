#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <time.h>

#include "constants.h"
#include "mytypes.h"

// Макрос разницы двух чисел
#define DIFFERENCE(x, y) (x - y)

// Возвращает модуль числа
uint module(kint number)
{
    return (number < 0) ? (number * (-1)) : number;
}

// Возвращает модуль разности двух чисел
uint diff_module(kint num1, kint num2)
{
    return module(DIFFERENCE(num1, num2));
}

// Распределяет память для массива типа 'unsigned int'
// Осуществляет проверку на правильность выделения памяти
puint alloc_mem_uint_arr(ksize_t size)
{
    puint p = (puint)calloc(size, sizeof(uint));

    if (!p)
    {
        printf("Не удалось выделить память для массива. Статус выхода =\'-1\'\n");
        exit(-1);
    }

    return p;
}

// Освобождение памяти для массива типа 'unsigned int'
void dealloc_mem_uint_arr(puint arr)
{
    free(arr);
    arr = NULL;
}

// Возвращает массив заданного размера, заполненный числами типа 'unsigned int'
puint random_fill_uint_arr(ksize_t size, kuint min, kuint max)
{
    srand(time(NULL));
    puint arr = alloc_mem_uint_arr(size);

    for (size_t i = 0UL; i < size; i++)
    {
        // Случайные числа от 'min' до 'max'
        arr[i] = rand() % max + min;
    }

    return arr;
}

void print_uint_arr(kpuint arr, ksize_t size)
{
    printf("Массив неотрицательных чисел:\n");
    for (size_t i = 0UL; i < size; i++)
    {
        printf("parr[%ld] = %u\n", i, arr[i]);
    }
    printf("\n");
}

// Возвращает индекс элемента, заданного как аргумент 'elem'
// Если не нашёл такого элемента, возвращается 0
size_t find_elem_index(kpuint arr, ksize_t size, kuint elem)
{
    // Индекс элемента 'elem'
    size_t elem_index = 0UL;

    // Ищем индекс элемента, который совпадает с значением 'elem'
    for (size_t i = 0UL; i < size; i++)
    {
        if (arr[i] == elem)
        {
            elem_index = i;
            return elem_index;
        }
    }

    // Если такого элемента нет (не нашли в предыдущем цикле)
    // Выводим соответствующее сообщение
    if ((elem != arr[0]) && (elem_index == 0))
        printf("Такого элемента нет.\n");

    return 0UL;
}

// Возвращает сумму элементов до элемента 'elem'
// 'arr' - массив, в котором происходит поиск
// 'size' - размер массива, в котором происходит поиск
ullong sum_before_certain_elem(kpuint arr, ksize_t size, kuint elem)
{
    ksize_t elem_index = find_elem_index(arr, size, elem);

    ullong sum = 0ULL;

    // Суммируем элементы перед 'elem'
    for (size_t i = 0UL; i < elem_index; i++)
    {
        sum += arr[i];
    }

    return sum;
}

// Возвращает сумму элементов после элемента 'elem'
// 'arr' - массив, в котором происходит поиск
// 'size' - размер массива, в котором происходит поиск
ullong sum_after_certain_elem(kpuint arr, ksize_t size, kuint elem)
{
    ksize_t elem_index = find_elem_index(arr, size, elem);

    ullong sum = 0ULL;

    // Суммируем элементы после 'elem'
    for (size_t i = elem_index + 1; i < size; i++)
    {
        sum += arr[i];
    }

    return sum;
}

// Находит и возвращает минимальный элемент в массиве типа 'unsigned int'
// 'arr' - массив, в котором происходит поиск
// 'size' - размер массива, в котором происходит поиск
uint find_min(kpuint arr, ksize_t size)
{
    uint min = arr[0];

    for (size_t i = 0UL; i < size; i++)
    {
        // Если минимальный элемент больше, чем 'arr[i]'
        // присваиваем значение 'arr[i]' в 'min'
        if (min > arr[i])
            min = arr[i];
    }

    return min;
}

// Находит и возвращает индекс минимального элемента в массиве типа 'unsigned int'
// 'arr' - массив, в котором происходит поиск
// 'size' - размер массива, в котором происходит поиск
size_t find_index_of_min(kpuint arr, ksize_t size)
{
    uint min = find_min(arr, size);

    for (size_t i = 0UL; i < size; i++)
    {
        // Находим такой элемент в массиве
        // возращаем его индекс
        if (min == arr[i])
            return i;
    }

    return 0UL;
}

// Возвращает индекс элемента, для которого сумма элементов
// стоящих до него, наименее отличается от суммы элементов,
// стоящих после него
size_t mindiff_sumbefore_sumafter(kpuint arr, ksize_t size)
{
    puint sums_arr = alloc_mem_uint_arr(size);

    // Заполнение массива модулем разности сумм, чтобы найти минимальную разницу
    for (size_t i = 0UL; i < size; i++)
    {
        sums_arr[i] = diff_module(sum_before_certain_elem(arr, size, arr[i]),
                                  sum_after_certain_elem(arr, size, arr[i]));
    }

    // Находим минимальный элемент в таком массиве
    size_t mindiff_index = find_index_of_min(sums_arr, size);

    // Освобождаем выделенную память для массива модуля разности сумм
    // до и после определённого элемента
    dealloc_mem_uint_arr(sums_arr);

    return mindiff_index;
}

// Возвращает индекс элемента, для которого сумма элементов
// стоящих до него, наименее отличается от суммы элементов,
// стоящих после него
// 'min' - минимальное сгенерированное число
// 'max' - максимальное сгенерированное число
size_t task1(kuint min, kuint max)
{
    puint arr = random_fill_uint_arr(UINT_ARR_SIZE, min, max);
    print_uint_arr(arr, UINT_ARR_SIZE);

    size_t certain_index = mindiff_sumbefore_sumafter(arr, UINT_ARR_SIZE);
    dealloc_mem_uint_arr(arr);

    return certain_index;
}

// Вспомогательная функция для 'task1()'
// Выводит индекс элемента, для которого сумма элементов
// стоящих до него, наименее отличается от суммы элементов,
// стоящих после него
void print_task1(kuint min, kuint max)
{
    printf("Index = %ld\n", task1(min, max));
}

int main()
{
    // Установка русского языка
    setlocale(LC_ALL, "rus");
    print_task1(1U, 10U);

    return 0;
}
