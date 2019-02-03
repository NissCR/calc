#ifndef CALC_PARSER_H
#define CALC_PARSER_H

#include <string>
#include "Expression.h"

class Parser {
public:
    explicit Parser(const char *input);

    Expression Parse();

private:
    const char *m_input; // Часть строки, которую ещё не распарсили

    std::string ParseToken(); // Парсит один токен
    Expression ParseSimpleExpression(); // Парсит простое выражение
    Expression ParseBinaryExpression(int min_priority); // Парсит бинарное выражение
};

int GetPriority(const std::string &);

double Solve(const Expression &);

#endif //CALC_PARSER_H
