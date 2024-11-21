#include <string>

using std::string;

// Token types
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
    TOKEN_INVALID,
    TOKEN_START
};

// Token structure
struct Token {
    TokenType type;   // Type of the token (e.g., number, operator)
    string value;     // The string value of the token
};

// Function to scan the next token from the input
Token scanToken(const string &input, size_t &pos);