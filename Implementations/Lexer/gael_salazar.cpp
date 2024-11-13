#include <iostream>
#include <string>
#include <cctype>

using std::string;

enum TokenType {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_MODULO,
    TOKEN_EXPONENT,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_END,
    TOKEN_INVALID
};

struct Token {
    TokenType type;
    string value;
};

// Sets nextToken to next token from input
Token scanToken(const string &input, size_t &pos) {
    Token result;
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
        while (pos < input.size() && std::isdigit(input[pos])) {
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

int main() {
    size_t pos = 0;
    string input = "-(36+5)*2";
    Token currentToken;
    do {
        currentToken = scanToken(input, pos);
        std::cout << currentToken.value << std::endl;
    } while (currentToken.type != TOKEN_END);

    return 0;
}
