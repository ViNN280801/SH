#include <iostream>
#include <fstream>

#include "menu.hpp"

bool isFileExists(const std::string &fname)
{
    std::ifstream ifs(fname);
    return ifs.good();
}

bool isInputIsNumber(const std::string &s)
{
    if (s.empty())
        return false;
    for (size_t i = 0; i < s.length(); i++)
        if (!isdigit(s[i]))
            return false;
    return true;
}

unsigned userInputToInt()
{
    std::string s;
    while (!isInputIsNumber(s))
    {
        std::getline(std::cin, s, '\n');
        if (!isInputIsNumber(s))
            std::cerr << "Вы ввели не число, попробуйте еще раз: ";
    }
    return std::stoi(s);
}

void printConsoleMenu(int choice, StudentList &sl)
{
    for (;;)
    {
        std::cout << "\nПодменю \"Консольный ввод/вывод\":\n1. Создать нового пользователя"
                  << "\n2. Считать определенного пользователя\n3. Вывести всех пользователей"
                  << "\n4. Редактировать пользователя\n5. Удалить пользователя"
                  << "\n6. Очистить список\n7. Рассчитать для каждой из групп потока процент отличников"
                  << "\n8. Удалить студентов по номеру группы"
                  << "\n9. Выход\nВведите пункт подменю \"Консольный ввод/вывод\": ";
        choice = userInputToInt();
        std::cout << '\n';

        if (choice == 9)
        {
            std::cout << "Выход из подменю \"Консольный ввод/вывод\"\n\n";
            break;
        }

        if (choice < 1 || choice > 9)
            std::cout << "Введенный пункт подменю не найден\n";
        else
        {
            size_t pos = 0;
            switch (choice)
            {
            case 1:
                sl.push_back();
                break;
            case 2:
                std::cout << "Введите индекс студента: ";
                pos = static_cast<size_t>(userInputToInt());
                std::cout << "\nИнформация о " << pos << " студенте:\n"
                          << sl.at(pos);
                break;
            case 3:
                std::cout << "Информация о всех студентах:\n";
                sl.print();
                break;
            case 4:
                std::cout << "Введите индекс студента: ";
                pos = static_cast<size_t>(userInputToInt());
                sl.change(pos);
                break;
            case 5:
                std::cout << "Введите индекс студента: ";
                pos = static_cast<size_t>(userInputToInt());
                sl.remove(pos);
                break;
            case 6:
                sl.clear();
                std::cout << "Список студентов очищен\n";
                break;
            case 7:
                sl.calcExcellentStudentsPercent();
                break;
            case 8:
                std::cout << "Введите номер группы: ";
                pos = static_cast<size_t>(userInputToInt());
                sl.removeByGroup(pos);
                break;
            }
        }
    }
}

void printFileMenu(int choice, StudentList &sl)
{
    std::string dbName;
    std::cout << "Введите имя файлы базы данных: ";
    std::getline(std::cin, dbName);

    if (!isFileExists(dbName))
    {
        std::ofstream ofs(dbName);
        if (!ofs.good())
            std::cout << "Ошибка создания файла\n";
        else
            std::cout << "База данных " << dbName << " была успешна создана\n";
        ofs.close();
    }
    else
        std::cout << "Файл с таким именем существует\n";

    for (;;)
    {
        std::cout << "\nПодменю \"Файловый ввод/вывод\":\n1. Создать нового пользователя"
                  << "\n2. Считать определенного пользователя\n3. Вывести всех пользователей"
                  << "\n4. Редактировать пользователя\n5. Удалить пользователя"
                  << "\n6. Очистить базу данных\n7. Рассчитать для каждой из групп потока процент отличников"
                  << "\n8. Удалить студентов по номеру группы"
                  << "\n9. Выход\nВведите пункт подменю \"Файловый ввод/вывод\": ";
        choice = userInputToInt();
        std::cout << '\n';

        if (choice == 9)
        {
            std::cout << "Выход из подменю \"Файловый ввод/вывод\"\n\n";
            break;
        }

        if (choice < 1 || choice > 9)
            std::cout << "Введенный пункт подменю не найден\n";
        else
        {
            sl.readDBToThisObj(dbName);
            size_t pos = 0;
            switch (choice)
            {
            case 1:
                sl.push_back();
                sl.writeStudentToFile(sl.back(), dbName);
                break;
            case 2:
                std::cout << "Введите индекс студента: ";
                pos = static_cast<size_t>(userInputToInt());
                std::cout << "\nИнформация о " << pos << " студенте:\n"
                          << sl.at(pos);
                break;
            case 3:
                std::cout << "Информация о всех студентах:\n";
                sl.readStudentsDB(dbName);
                break;
            case 4:
                std::cout << "Введите индекс студента: ";
                pos = static_cast<size_t>(userInputToInt());
                sl.change(pos);
                sl.writeStudentsListToFile(dbName);
                break;
            case 5:
                std::cout << "Введите индекс студента: ";
                pos = static_cast<size_t>(userInputToInt());
                sl.remove(pos);
                sl.writeStudentsListToFile(dbName);
                break;
            case 6:
                sl.clear();
                sl.writeStudentsListToFile(dbName);
                break;
            case 7:
                sl.readDBToThisObj(dbName);
                sl.calcExcellentStudentsPercent();
                break;
            case 8:
                std::cout << "Введите номер группы: ";
                pos = static_cast<size_t>(userInputToInt());
                sl.removeByGroup(pos);
                sl.writeStudentsListToFile(dbName);
                break;
            }
        }
    }
}

void printMenu()
{
    unsigned choice = 0;
    for (;;)
    {
        std::cout << "Меню:\n1. Консольный ввод/вывод\n2. Файловый ввод/вывод\n3. Выход\n"
                  << "Введите пункт меню: ";
        choice = userInputToInt();

        if (choice == 3)
        {
            std::cout << "Выход\n";
            break;
        }

        if (choice < 1 || choice > 3)
            std::cout << "Введенный пункт меню не найден\n";
        else
        {
            StudentList sl;

            switch (choice)
            {
            case 1:
                printConsoleMenu(choice, sl);
                break;
            case 2:
                printFileMenu(choice, sl);
                break;
            }
        }
    }
}
