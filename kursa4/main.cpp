#include <iostream>
#include <locale>

#include "student.hpp"
#include "menu.hpp"

int main()
{
    // Обеспечиваем поддержку русского языка
    setlocale(LC_ALL, "rus");

    // StudentList sl;

    // unsigned g1[5] = {5, 5, 5, 5, 5};
    // sl.push_back("k d q", 4, g1, 4500);

    // unsigned g2[5] = {4, 5, 4, 5, 4};
    // sl.push_back("h n t", 4, g2, 3200);

    // unsigned g3[5] = {4, 3, 4, 3, 3};
    // sl.push_back("o k a", 5, g3, 0);

    // unsigned g4[5] = {2, 3, 2, 2, 3};
    // sl.push_back("b t m", 4, g4, 0);

    // unsigned g5[5] = {5, 5, 5, 5, 5};
    // sl.push_back("o p g", 6, g5, 4500);

    // unsigned g6[5] = {5, 5, 5, 5, 5};
    // sl.push_back("m u f", 4, g6, 4500);

    // unsigned g7[5] = {5, 5, 5, 5, 5};
    // sl.push_back("p i m", 4, g7, 4500);

    // std::cout << sl;

    // sl.writeStudentsListToFile("db");

    printMenu();

    return 0;
}
