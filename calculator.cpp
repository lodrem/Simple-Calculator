#include "calculator.hpp"
#include "helper.hpp"

#include <iostream>

namespace calculator {

    /**
     * Init calculator
     */
    void Calculator::init() {
        while( ! isExit) {
            input();
            parse();
            printResult();
        }
    }

    /**
     * Read command
     */
    void Calculator::input() {
        std::getline(std::cin, expression);
    }

    /**
     * Output result
     */
    void Calculator::printResult() {
        std::cout << "Result: " << result.toStr() << std::endl;
    }

    /**
     * Parse command
     */
    void Calculator::parse() {
        helper::removeAllSpace(expression);
        if( ! isValidExpr(expression)) {
            throw "Invalid expression";
        } else {
        }
    }

    /**
     * Check if expression is valid
     */
    bool Calculator::isValidExpr(const std::string& expr) {
        unsigned short idx;
        unsigned short parentheseCount = 0;
        const std::map<char, Symbol> op = {
            {'+', plus},
            {'-', minus},
            {'*', multiple},
            {'/', divide}
        };
        std::map<Symbol, bool> nextSym = {
            {digit, true},
            {plus, false},
            {minus, true},
            {multiple, false},
            {divide, false},
            {open, true},
            {close, false}
        };
        for(idx = 0; idx < expr.size(); ++ idx) {
            const char& sym = expr[idx];
            if(sym == '(') {
                if( ! nextSym[open]) return false;
                ++ parentheseCount;
                nextSym[digit] = nextSym[minus] = nextSym[open] = true;
                nextSym[plus] = nextSym[multiple] = nextSym[divide] = nextSym[close] = false;
            } else if(sym == ')') {
                if(parentheseCount == 0 || ! nextSym[close]) {
                    return false;
                } else {
                    -- parentheseCount;
                }
                nextSym[digit] = nextSym[open] = false;
                nextSym[plus] = nextSym[minus] = nextSym[multiple] = nextSym[divide] = nextSym[close] = true;
            } else if(isdigit(sym)) {
                if( ! nextSym[digit]) return false;
                nextSym[digit] = nextSym[plus] = nextSym[minus] = nextSym[multiple] = nextSym[divide] = nextSym[close] = true;
                nextSym[open] = false;
            } else if(helper::isOperator(sym)) {
                if( ! nextSym[op.at(sym)]) return false;
                nextSym[digit] = nextSym[open] = true;
                nextSym[plus] = nextSym[minus] = nextSym[multiple] = nextSym[divide] = nextSym[close] = false;
            } else if( ! isspace(sym)) {
                return false;
            }
        }
        if(parentheseCount > 0) return false;
        return true;
    }

}
