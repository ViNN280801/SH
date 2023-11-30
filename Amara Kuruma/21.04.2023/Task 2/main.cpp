#include <iostream>

#include "eval_math_expr.hpp"

int main()
{
    std::string exprToCalc;
    for (;;)
    {
        std::cout << "Enter expression which you want to calculate: ";
        std::getline(std::cin, exprToCalc, '\n');
        std::cout << evaluate(exprToCalc) << std::endl;
        std::cout << "Do you want to exit? y/N: ";
        std::getline(std::cin, exprToCalc, '\n');
        if (exprToCalc == "Y" || exprToCalc == "y" ||
            exprToCalc == "Yes" || exprToCalc == "yes")
            break;
    }
    return EXIT_SUCCESS;
}
