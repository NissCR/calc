#ifndef CALC_EXPRESSION_H
#define CALC_EXPRESSION_H

#include <string>
#include <vector>

struct Expression {
    std::string token;
    std::vector<Expression> args;

    Expression(std::string token) : token(token) {} // Числа

    Expression(std::string token, Expression left_expression) :
        token(token), args{left_expression} {} // Унарные операции
    Expression(std::string token, Expression left_expression, Expression right_expression) :
        token(token), args{left_expression, right_expression} {} // Бинарные операции
};

#endif //CALC_EXPRESSION_H
