#include <sstream>

#include "rational_number.hpp"

// Converts boolean 0 or 1 to words "True" and "False"
char const *boolToWord(bool flag)
{
    return flag ? "True" : "False";
}

// Returns string parameter as T
template <typename T>
T str_to_T(const std::string &__str)
{
    T value;
    std::istringstream iss(__str);
    iss >> value;
    return value;
}

// Returns true if string is a floating number (float, double, etc.)
bool is_floating_number(const std::string &__str)
{
    // Iterator for '__str' variable
    std::string::const_iterator it = __str.begin();

    // Count of points in string (must be 1 point in number)
    // Same thing with minus sign
    unsigned int count_point{0U}, count_minus{0U};

    // Iterating by symbols in string
    while (it != __str.end())
    {
        // Counting all minuses in string
        if ((*it == '-'))
            count_minus++;

        // Counting all points in string
        if ((*it == '.'))
            count_point++;

        // Incrementing iterator
        ++it;
    }

    // Exception case when point stay in the beginning of string
    if (__str.at(0UL) == '.')
        return false;

    // Moving iterator to the begin of string
    it = __str.begin();

    // If number contains less or 1 point or minus -> continue
    if (count_point <= 1U && count_minus <= 1U)
    {
        // Using 'while' loop to check if all symbols in string are digits
        while (it != __str.end() && (std::isdigit(*it) || (*it) == '.' || (*it) == '-'))
        {
            // Incrementing iterator
            ++it;
        }
    }

    return ((!__str.empty()) && (it == __str.end()));
}

// Returns user's input as floating number
template <typename T>
T input_to_floating(const char *__msg = "")
{
    // User's input string
    std::string users_input{};

    // Using 'while' loop and string input to avoid errors
    while (true)
    {
        std::cout << __msg;
        std::cin >> users_input;

        // If 'input' is contains only of digits -> break infinity loop
        if (is_floating_number(users_input))
            break;
        // Else: print message and back to the begininng of 'while' loop
        else
            std::cout << "You entered not an floating number. Try again.\n";
    }

    // Converting user's string to numeric type to return it as a result
    T num{str_to_T<T>(users_input)};

    // Returning converted user's inputted value to 'T' type
    return num;
}

int main()
{
    for (;;)
    {
        /* Block of declaring rational numbers */
        double numerator1{input_to_floating<double>("Enter numerator of 1st number: ")},
            denumerator1{input_to_floating<double>("Enter denumerator of 1st number: ")};

        rational_number num1(numerator1, denumerator1);
        std::cout << "First number is " << num1.to_double() << "\n"
                  << "Numerator = " << num1.getNumerator()
                  << "\tDenumerator = " << num1.getDenumerator() << std::endl
                  << std::endl;

        double numerator2{input_to_floating<double>("Enter numerator of 2nd number: ")},
            denumerator2{input_to_floating<double>("Enter denumerator of 2nd number: ")};

        rational_number num2(numerator2, denumerator2);
        std::cout << "Second number is " << num2.to_double() << "\n"
                  << "Numerator = " << num2.getNumerator()
                  << "\tDenumerator = " << num2.getDenumerator() << std::endl
                  << std::endl;
        /* End of block of declaring rational numbers */

        /* Block of comparing */
        float compChoice{0.0f};
        while (compChoice != 5.0f)
        {
            std::cout << "Which compare operations do you want to produce?\n1. num1 = num2?\n2. num1 != num2?\n"
                      << "3. num1 < num2?\n4. num1 > num2?\n5. Exit from comparing menu\nEnter number: ";
            compChoice = input_to_floating<float>();
            switch (static_cast<unsigned>(compChoice))
            {
            case 1:
                std::cout << "Result is " << boolToWord(num1 == num2) << std::endl;
                if (num1 == num2)
                    std::cout << num1 << " = " << num2 << std::endl;
                else
                    std::cout << num1 << " != " << num2 << std::endl;
                break;
            case 2:
                std::cout << "Result is " << boolToWord(num1 != num2) << std::endl;
                if (num1 != num2)
                    std::cout << num1 << " != " << num2 << std::endl;
                else
                    std::cout << num1 << " = " << num2 << std::endl;
                break;
            case 3:
                std::cout << "Result is " << boolToWord(num1 < num2) << std::endl;
                if (num1 < num2)
                    std::cout << num1 << " < " << num2 << std::endl;
                else
                    std::cout << num1 << " > " << num2 << std::endl;
                break;
            case 4:
                std::cout << "Result is " << boolToWord(num1 > num2) << std::endl;
                if (num1 > num2)
                    std::cout << num1 << " > " << num2 << std::endl;
                else
                    std::cout << num1 << " < " << num2 << std::endl;
                break;
            default:
                std::cout << "Invalid input, try again" << std::endl;
                break;
            }
        }
        /* End of block of comparing */

        /* Block of exiting */
        float exit{input_to_floating<float>("Do you want to exit?\n1. Yes\n2. No\nEnter 1 or 2: ")};
        if (exit == 1.0f)
            break;
        std::endl(std::cout);
    }

    return EXIT_SUCCESS;
}