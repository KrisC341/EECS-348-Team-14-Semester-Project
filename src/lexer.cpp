#include <iostream>
#include <string>
#include <cctype>
#include "lexer.h"

using std::string;

// Sets nextToken to next token from input
Token scanToken(const string &input, size_t &pos) {
    Token result;
    //std::cout << "Pos: " << pos << std::endl;
    //std::cout << "Char: " << input[pos] << std::endl;
    //the above two comments were used for debugging

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

    //grabs the current character being tokenized
    char currentChar = input[pos];

    // Number lexer
    if (std::isdigit(currentChar)) {
        string num;
        while (pos < input.size() && ((std::isdigit(input[pos])) || (currentChar == '.'))) { //checks for decimal and number
            num += input[pos]; //creates a new digit for the actual number
            pos++;
        }
        result.type = TOKEN_NUMBER; //alters token attributes to numerical
        result.value = num;
        return result;
    }

    // Operator lexer
    switch (currentChar) {
        case '+': //+ operator
            pos++;
            result.type = TOKEN_PLUS;
            result.value = "+";
            return result;
        case '-': //- operator
            pos++;
            result.type = TOKEN_MINUS;
            result.value = "-";
            return result;
        case '*': //this case detects both * operator and ** operator for exponentiation
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
        case '/': // / operator
            pos++;
            result.type = TOKEN_SLASH;
            result.value = "/";
            return result;
        case '%': // modulo operator
            pos++;
            result.type = TOKEN_MODULO;
            result.value = "%";
            return result;
        case '(': // both of the following cases are for parenthetical grouping
            pos++;
            result.type = TOKEN_LPAREN;
            result.value = "(";
            return result;
        case ')':
            pos++;
            result.type = TOKEN_RPAREN;
            result.value = ")";
            return result;
        default: // this case is reached if the detected character does not match any operator or potential operand, meaning it is an unknown character and should file as an error
            pos++;
            result.type = TOKEN_INVALID;
            result.value = "ERROR";
            throw std::runtime_error("Unknown characters");
            return result;
    }

}
