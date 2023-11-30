#include <string>

#include "eval_math_expr.hpp"

int opOrder(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

int calcSimplestExpr(int a, int b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        return 0;
    }
}

void evalHelper(Stack<int> &vals, Stack<char> &signs)
{
    int val2{vals.top()};
    vals.pop();

    int val1{vals.top()};
    vals.pop();

    char op{signs.top()};
    signs.pop();

    vals.push(calcSimplestExpr(val1, val2, op));
}

int evaluate(std::string expr)
{
    size_t i{};

    // Stack of integer values
    Stack<int> values;
    // Stack of math signs
    Stack<char> signs;

    for (; i < expr.length(); i++)
    {
        // If current symbol is whitespace -> skip
        if (expr[i] == ' ')
            continue;
        // Current token is an opening
        // brace, push it to 'signs'
        else if (expr[i] == '(')
            signs.push(expr[i]);

        // Current token is a number, push
        // it to Stack for numbers
        else if (isdigit(expr[i]))
        {
            int val{};
            // There may be more than one
            // digits in number
            while (i < expr.length() &&
                   isdigit(expr[i]))
            {
                val = (val * 10) + (expr[i] - '0');
                i++;
            }
            values.push(val);
            // 'i' point to the symbol next to the digit, since loop increases it
            // We need to skip 1 token pos -> decrease the 'i' by 1
            i--;
        }
        // If symbol is closing bracket -> solve entire expr
        else if (expr[i] == ')')
        {
            while (!signs.empty() && signs.top() != '(')
                evalHelper(values, signs);
            // Deleting opening brace
            if (!signs.empty())
                signs.pop();
        }
        // If symbol is a math sign
        else
        {
            // While top of 'signs' has same or greater
            // opOrder to current token, which
            // is an operator. Apply operator on top
            // of 'signs' to top two elements in values Stack.
            while (!signs.empty() && opOrder(signs.top()) >= opOrder(expr[i]))
                evalHelper(values, signs);
            // Push current token to 'signs'.
            signs.push(expr[i]);
        }
    }
    // Entire expression has been parsed at this
    // point, apply remaining signs to remaining
    // values.
    while (!signs.empty())
        evalHelper(values, signs);

    // Top of 'values' contains result, return it.
    return values.top();
}
