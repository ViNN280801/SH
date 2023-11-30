#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <time.h>

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
void dealloc_mem_uint_arr(puint arr)
{
    free(arr);
    arr = NULL;
}

// Освобождение памяти для массива типа 'unsigned int'
void dealloc_mem_int_arr(pint arr)
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

void print_uint_arr(kpuint arr, ksize_t size)
{
    printf("Массив неотрицательных чисел:\n");
    for (size_t i = 0UL; i < size; i++)
    {
        printf("parr[%ld] = %u\n", i, arr[i]);
    }
    printf("\n");
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
