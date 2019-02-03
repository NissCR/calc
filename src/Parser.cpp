#include "Parser.h"
#include "Tokens.h"
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
#include <stdexcept>

Parser::Parser(const char* input) : m_input(input){
    // Удаление всех пробелов
    /*std::string tmp(inp);
    tmp.erase(std::remove_if(tmp.begin(), tmp.end(), isspace), tmp.end());
    input = tmp.data();*/
}

std::string Parser::ParseToken() {
    while (std::isspace(*m_input)) ++m_input;

    // Если начинается с цифры, парсим число
    if(std::isdigit(*m_input)) {
        std::string number;
        int dot_count = 0;
        while(std::isdigit(*m_input) || *m_input == '.'){
            // Может быть только одна точка
            if(*m_input == '.' && ++dot_count > 1)
                throw std::runtime_error("Некорректное число");
            number.push_back(*m_input++);
        }
        return number;
    }

    // Проверка всех известных токенов - операции, токены
    for(auto token : TOKENS){
        if(std::strncmp(m_input, token.c_str(), token.size()) == 0){
            m_input += token.size();
            return token;
        }
    }

    // Неизвестный токен или символ конца строки (\0)
    return "";
}

Expression Parser::ParseSimpleExpression() {
    // Парссим первый токен
    auto  token = ParseToken();

    if(token.empty())
        throw  std::runtime_error("Неверная входная строка");

    // Если число, добавляем
    if(std::isdigit(token[0]))
        return Expression(token);

    // Если скобки, парсим и возвращаем выражение в скобках
    if(token == "(") {
        auto result = Parse();
        if(ParseToken() != ")")
            throw  std::runtime_error("Ожидалось ')'");
        return result;
    }

    // Иначе, это унарная операция - парсим её аргумент
    auto arg = ParseSimpleExpression();
    return Expression(token, arg);
}

int GetPriority(const std::string& operation){
    if (operation == TOKENS[PLUS]) return 1;
    if (operation == TOKENS[MINUS]) return 1;
    if (operation == TOKENS[MULTIPL]) return 2;
    if (operation == TOKENS[DIV]) return 2;
    if (operation == TOKENS[MOD]) return 2;
    if (operation == TOKENS[POW]) return 3;
    return 0; // Не бинарная операция
}

Expression Parser::ParseBinaryExpression(int min_priority) {
    auto left_expr = ParseSimpleExpression();// Парсим выражение слева

    // Парсинг операции и проверка её приоритета
    for(;;){
        auto operation = ParseToken();// Попытка распарсить бинарную операцию
        int priority = GetPriority(operation);
        // Если операция не бинарная или её приоритет слишком низкий
        if(priority <= min_priority) {
            m_input -= operation.size();// Возвращаем токен
            return left_expr;
        }

        // Парсим выражение справа. Текущая операция задаёт приоритет
        auto right_expr = ParseBinaryExpression(priority);
        // Обновление выражения слева
        left_expr = Expression(operation, left_expr, right_expr);
    }
}

Expression Parser::Parse() {
    return ParseBinaryExpression(0);
}

double Solve(const Expression& expr){
    switch (expr.args.size()) {
        //Число
        case 0:
            return std::stod(expr.token);
        // Унарная операция
        case 1: {
            auto num = Solve(expr.args[0]);
            if(expr.token == TOKENS[PLUS]) return num;
            if(expr.token == TOKENS[MINUS]) return -num;
            if(expr.token == TOKENS[ABS]) return fabs(num);
            if(expr.token == TOKENS[SIN]) return sin(num);
            if(expr.token == TOKENS[ASIN]) return asin(num);
            if(expr.token == TOKENS[COS]) return cos(num);
            if(expr.token == TOKENS[ACOS]) return acos(num);
            if(expr.token == TOKENS[LN]) return log(num);
            if(expr.token == TOKENS[LOG]) return log10(num);
            throw std::runtime_error("Неизвестный унарный оператор");
        }
        // Бинарная операция
        case 2: {
            auto left = Solve(expr.args[0]);
            auto right = Solve(expr.args[1]);
            if(expr.token == TOKENS[PLUS]) return left + right;
            if(expr.token == TOKENS[MINUS]) return left - right;
            if(expr.token == TOKENS[MULTIPL]) return left * right;
            if(expr.token == TOKENS[DIV]) return left / right;
            if(expr.token == TOKENS[MOD]) return (int)left % (int)right;
            if(expr.token == TOKENS[POW]) return pow(left, right);
            throw std::runtime_error("Неизвестный бинарный оператор");
        }

        default:
            throw std::runtime_error("Неизвестный тип выражения");
    }
}