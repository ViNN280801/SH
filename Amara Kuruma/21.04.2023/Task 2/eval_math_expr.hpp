#ifndef EVAL_MATH_EXPR_HPP
#define EVAL_MATH_EXPR_HPP

#include "stack.hpp"
#include "stack_impl.hpp"

// Returns int value that represents order of operators to apply
int opOrder(char);

// Returns result of calculating
int calcSimplestExpr(int, int, char);

// Helper method that calculates simple expr and add result to a stack of numbers
void evalHelper(Stack<int> &, Stack<char> &);

// Calculates the whole math expr representes as a string
// Returns result of this calculation
int evaluate(std::string);

#endif // !EVAL_MATH_EXPR_HPP