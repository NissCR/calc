#include <iostream>
#include <iterator>
#include <sstream>
#include <algorithm>
#include "src/Parser.h"

std::vector<std::string> split(std::string &str, const char del = ' ') {
    if (del != ' ')
        std::replace(str.begin(), str.end(), del, ' ');

    std::vector<std::string> arr;
    std::istringstream stream(str);

    for (auto it = std::istream_iterator<std::string>(stream); it != std::istream_iterator<std::string>(); it++)
        arr.push_back(*it);

    return arr;
}

void ReplaceVars(std::string &formula, std::string str_vars) {
    std::vector<std::string> vars = split(str_vars);
    for (auto &var : vars) {
        std::vector<std::string> pair = split(var, '=');

        // Заменить все имена переменных на их значения
        size_t pos = 0;
        while ((pos = formula.find(pair[0], pos)) != std::string::npos) {
            formula.replace(pos, pair[0].length(), pair[1]);
            pos += pair[1].length();
        }
        //formula.replace(formula.find(pair[0]), size(pair[1]) - 1, pair[1]);
    }
}

int main(int argc, char *argv[]) {
    if (argc <= 1)
        std::cout << "Нет формулы";

    std::string vars;
    getline(std::cin, vars);

    std::string formula = argv[1];
    ReplaceVars(formula, vars);

    const char *expr = formula.c_str();

    Parser parser(expr);
    double result = Solve(parser.Parse());

    std::cout << result << std::endl;
}