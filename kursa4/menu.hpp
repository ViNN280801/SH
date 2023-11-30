#ifndef MENU_HPP
#define MENU_HPP

#include "student.hpp"

bool isFileExists(const std::string &);

bool isInputIsNumber(const std::string &);

unsigned userInputToInt();

void printMenu();

void printConsoleMenu(int, StudentList &);

void printFileMenu(int, StudentList &);

#endif // !MENU_HPP
