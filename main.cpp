#include <iostream>
#include "src/Parser.h"
int errors;

void test(const char* input, double expected) {
    try {
        std::cout << "Input: " << input << std::endl;
        Parser parser(input);
        double result = calc(parser.Parse());
        if (result == expected) return;
        std::cout << input << " = " << expected << " : error, got " << result << '\n';
    }
    catch (std::exception& e) {
        std::cout << input << " : exception: " << e.what() << '\n';
    }
    ++errors;
}

void testing(const char* input, double expected) {
    try{
        Parser parser(input);
        auto result = calc(parser.Parse());
        //if(result == expected) return;
        std::cout << input << " = " << result << " exp: " << expected << std::endl;
    } catch (std::exception& e) {
        std::cout << input << ". Exception: " << e.what() << std::endl;
    }
}

int main() {
    /*test("0", 0);
    test("1", 1);
    test("9", 9);
    test("10", 10);
    test("+1", 1);
    test("-1", -1);
    test("(1)", 1);
    test("(-1)", -1);
    test("abs(-1)", 1);
    test("1+20", 21);
    test("1 + 20", 21);
    test("1+20+300", 321);
    test("1+20+300+4000", 4321);
    test("-1+20", 19);
    test("--1+20", 21);
    test("---1+20", 19);
    test("(1+20)", 21);
    test("-2*3", -6);
    test("2*-3", -6);
    test("1++2", 3);
    test("1+10*2", 21);
    test("10*2+1", 21);
    test("(1+20)*2", 42);
    test("2*(1+20)", 42);
    test("(1+2)*(3+4)", 21);
    test("2*3+4*5", 26);
    test("100+2*10+3", 123);
    test("2^3", 8);
    test("2^3*5+2", 42);
    test("5*2^3+2", 42);
    test("2+5*2^3", 42);
    test("1+2^3*10", 81);
    test("2^3+2*10", 28);
    test("5 * 4 + 3 * 2 + 1", 27);
    test("2.5", 2.5);
    test("2..5", 2.5);
    test("sin(2)", 0.909297);*/

    std::cout << "Done with " << errors << " errors.\n";
}