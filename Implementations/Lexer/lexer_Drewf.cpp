#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <optional>

struct Token {
    std::string type;  // holds token type
    std::string value; // holds token value
};

class Lexer {
public:
    Lexer(const std::string& input) : input_string(input), current_index(0) {}

    std::optional<Token> scanToken() {
        // skip whitespace
        while (current_index < input_string.size() && std::isspace(input_string[current_index])) {
            current_index++;
        }
        // end of input check
        if (current_index >= input_string.size()) {
            nextToken = std::nullopt;
            return nextToken;
        }

        // looks at each token pattern and tries to match the current index to one of the patterns
        for (const auto& [type, pattern] : token_patterns) {
            std::regex regex(pattern);
            std::smatch match;
            // extracts the substring from the current index, and tries to match it
            std::string remaining_input = input_string.substr(current_index);
            // attempts to match regex against the remaining input and creates a token if a match is found
            if (std::regex_search(remaining_input, match, regex) && match.position() == 0) {
                std::string token_value = match.str(0);
                nextToken = Token{type, token_value};
                tokens.push_back(*nextToken);
                current_index += match.length(0);
                std::cout << "Scanned Token: " << nextToken->type << " - " << nextToken->value << std::endl;
                return nextToken;
            }
        }

        // if no valid token is matched, move to next character
        current_index++;
        return scanToken();
    }

    // tokenizes the input
    void tokenize() {
        while (scanToken()) {}  // continue scanning until end of input
        std::cout << "Tokenization complete." << std::endl;
    }

    const std::vector<Token>& getTokens() const { return tokens; }

private:
    std::string input_string;   // holds the input string
    size_t current_index;   // keeps track of the current index
    std::optional<Token> nextToken; // optional token that stores the current or next token to be processed
    std::vector<Token> tokens;  // stores all tokens found in the input

    const std::vector<std::pair<std::string, std::string>> token_patterns = {
        {"NUMBER", R"(\b\d+\b)"},   // integer numbers
        {"IDENTIFIER", R"(\b[a-zA-Z_]\w*\b)"},  // identifiers (variable names, keywords)
        {"LPAREN", R"(\()"},    // left parentheses
        {"RPAREN", R"(\))"},    // right parentheses
        {"EXPONENT", R"(\*\*)"},    // exponentiation operator
        {"OPERATOR", R"([+\-*/])"}, // arithmetic operators
    };
};

int main() {
    std::string input = "1 + 2 * (x - 3)**4 /5";  // sample input with exponentiation
    Lexer lexer(input);
    lexer.tokenize();

    std::cout << "All tokens:" << std::endl;
    for (const auto& token : lexer.getTokens()) {
        std::cout << "Type: " << token.type << ", Value: " << token.value << std::endl;
    }

    return 0;
}