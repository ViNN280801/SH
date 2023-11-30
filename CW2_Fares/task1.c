#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/* Инициализация известных членов последовательности h_i */
static const double h1 = 1.01;
static const double h2 = 0.75;

/* Инициализация переменной количества членов в последовательности */
static const int N = 42;

/* Вычисляет и возвращает '_n'-ый член последовательности */
double h_n(int _n)
{
    if (_n == 1)
    {
        return h1;
    }
    else if (_n == 2)
    {
        return h2;
    }
    else
    {
        return 0.25 * _n + 2 * sin(h_n(_n - 1)) - 0.35 * cos(h_n(_n - 2));
    }
}

/* Вычисляет и возвращает сумму '_n'-ых членов последовательности */
double sum(int _n)
{
    double sum_ = 0.0;

    for (int i = 1; i <= _n; i++)
    {
        sum_ += h_n(i);
    }

    return sum_;
}

int main(void)
{
    // Подключение русского языка
    setlocale(LC_ALL, "rus");

    printf("%lf\n", sum(N));
}
