#include "funcs.h"
#include "constants.h"

// Вспомогательная функция абстрагирующаяся от задания размера
// буфера как аргумент, в который будет записываться ввод пользователя
// Возвращает введённое число
// Осуществляет проверки на корректность ввода
int inputInt()
{
    return inputIntBasic(BUFFER_SIZE);
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
