#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

#include "wagons.hpp"

// Converts string to 'T' type
template <typename T>
T str_to_T(const std::string &str)
{
    T value;
    std::istringstream iss(str);
    iss >> value;
    return value;
}

// Returns true if string is a unsigned integer number (unsigned short, unsigned int, size_t, etc.)
bool is_uint_number(const std::string &str)
{
    // Iterator for 'str' variable
    std::string::const_iterator it{str.begin()};

    // Using 'while' loop to check if all symbols in string are digits
    while (it != str.end() && std::isdigit(*it))
    {
        // Incrementing iterator
        ++it;
    }

    return ((!str.empty()) && (it == str.end()));
}

// Returns user's input as signed integer number
template <typename T>
T input_to_int(std::string const &msg = "")
{
    // User's input string
    std::string users_input{};

    // Using 'while' loop and string input to avoid errors
    while (true)
    {
        if (msg != "")
            std::cout << msg;
        std::getline(std::cin, users_input, '\n');

        // If 'input' is contains only of digits -> break infinity loop
        if (is_uint_number(users_input))
            break;
        // Else: print message and back to the begininng of 'while' loop
        else
            std::cout << "You entered not an signed integer number. Try again.\n";
    }

    // Converting user's string to numeric type to return it as a result
    T num{str_to_T<T>(users_input)};

    // Returning converted user's inputted value to 'T' type
    return num;
}

int main()
{
    int wagonType{};
    while (wagonType != 3)
    {
        wagonType = input_to_int<int>(
            "1. Compartment (Kupe)\n2. Sleeping wagon\n3. Exit\nEnter wagon's type (1, 2): ");

        KupeWagon kw;
        SleepWagon sw;

        switch (wagonType)
        {
        case 1:
            kw.printPriceList();
            break;
        case 2:
            sw.printPriceList();
            break;
        case 3:
            break;
        default:
            std::cout << "Error: Incorrect wagon's type.\nTry again\n";
            break;
        }
    }

    return 0;
}
