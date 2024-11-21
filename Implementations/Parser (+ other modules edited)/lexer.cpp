#include <iostream>
#include <string>
#include <cctype>
#include "lexer.h"

using std::string;

// Sets nextToken to next token from input
Token scanToken(const string &input, size_t &pos) {
    Token result;
    std::cout << "Pos: " << pos << std::endl;
    std::cout << "Char: " << input[pos] << std::endl;
    // Whitespace skipper
    while (pos < input.size() && std::isspace(input[pos])) {
        pos++;
    }

    // Find input end
    if (pos >= input.size()) {
        result.type = TOKEN_END;
        result.value = "";
        return result;
    }

    char currentChar = input[pos];

    // Number lexer
    if (std::isdigit(currentChar)) {
        string num;
        while (pos < input.size() && ((std::isdigit(input[pos])) || (currentChar == '.'))) { //checks for decimal and number
            num += input[pos];
            pos++;
        }
        result.type = TOKEN_NUMBER;
        result.value = num;
        return result;
    }

    // Operator lexer
    switch (currentChar) {
        case '+':
            pos++;
            result.type = TOKEN_PLUS;
            result.value = "+";
            return result;
        case '-':
            pos++;
            result.type = TOKEN_MINUS;
            result.value = "-";
            return result;
        case '*':
            pos++;
            if (pos < input.size() && input[pos] == '*') {
                pos++;
                result.type = TOKEN_EXPONENT;
                result.value = "**";
            } else {
                result.type = TOKEN_STAR;
                result.value = "*";
            }
            return result;
        case '/':
            pos++;
            result.type = TOKEN_SLASH;
            result.value = "/";
            return result;
        case '%':
            pos++;
            result.type = TOKEN_MODULO;
            result.value = "%";
            return result;
        case '(':
            pos++;
            result.type = TOKEN_LPAREN;
            result.value = "(";
            return result;
        case ')':
            pos++;
            result.type = TOKEN_RPAREN;
            result.value = ")";
            return result;
        default:
            pos++;
            result.type = TOKEN_INVALID;
            result.value = "ERROR";
            return result;
    }

}
