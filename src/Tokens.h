#ifndef CALC_TOKENS_H
#define CALC_TOKENS_H

#include <string>
#include <vector>

static const std::vector<std::string> TOKENS = {"+", "-", "*", "/", "(", ")", "^", "%", "abs", "sin", "asin", "cos",
                                                "acos", "tan", "atan", "ln", "lg"};
enum OPERATORS { PLUS, MINUS, MULTIPL, DIV, OPBR, CLBR, POW, MOD, ABS, SIN, ASIN, COS, ACOS, TAN, ATAN, LN, LG };

#endif //CALC_TOKENS_H
