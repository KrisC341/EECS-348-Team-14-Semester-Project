#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

#include "Lexer.cpp"
#include "AST.cpp"

// forward declarations
std::unique_ptr<treeNode> parseE();
std::unique_ptr<treeNode> parseT();
std::unique_ptr<treeNode> parseF();
std::unique_ptr<treeNode> parsePrimary();

// initialize the lexer with the user's input
std::string input;
size_t pos = 0;
Token currentToken;

// initialize lexer and advance token
void initializeLexer(const std::string& userInput) {
    input = userInput;
    pos = 0;
    currentToken = scanToken(input, pos);
}

void advanceToken() {
    currentToken = scanToken(input, pos);
}

// parses expressions involving '+' and '-'
std::unique_ptr<treeNode> parseE() {
    auto left = parseT();  // start by parsing the first term
    while (currentToken.type == TOKEN_PLUS || currentToken.type == TOKEN_MINUS) {
        TokenType op = currentToken.type;
        advanceToken();
        auto right = parseT();
        if (op == TOKEN_PLUS) {
            left = std::make_unique<Add>(left.release(), right.release());
        } else if (op == TOKEN_MINUS) {
            left = std::make_unique<Sub>(left.release(), right.release());
        }
    }
    return left;
}

// parses terms involving '*', '/', and '%'
std::unique_ptr<treeNode> parseT() {
    auto left = parseF();  // start by parsing the first factor
    while (currentToken.type == TOKEN_STAR || currentToken.type == TOKEN_SLASH || currentToken.type == TOKEN_MODULO) {
        TokenType op = currentToken.type;
        advanceToken();
        auto right = parseF();
        if (op == TOKEN_STAR) {
            left = std::make_unique<Multi>(left.release(), right.release());
        } else if (op == TOKEN_SLASH) {
            left = std::make_unique<Div>(left.release(), right.release());
        } else if (op == TOKEN_MODULO) {
            left = std::make_unique<Modulo>(left.release(), right.release());
        }
    }
    return left;
}

// parses factors like numbers, negations, parentheses, and exponents
std::unique_ptr<treeNode> parseF() {
    auto base = parsePrimary();  // Parse the base for exponentiation
    while (currentToken.type == TOKEN_EXPONENT) {
        advanceToken();
        auto exponent = parsePrimary();
        base = std::make_unique<Exponent>(base.release(), exponent.release());
    }
    return base;
}

// parses primary expressions (numbers, parentheses, negations)
std::unique_ptr<treeNode> parsePrimary() {
    if (currentToken.type == TOKEN_LPAREN) {  // check for '('
        advanceToken();  // consume '('
        auto node = parseE();  // parse the expression inside parentheses
        if (currentToken.type != TOKEN_RPAREN) {  // ensure that ')' is present
            throw std::runtime_error("Expected closing parenthesis");
        }
        advanceToken();  // consume ')'
        return node;
    } else if (currentToken.type == TOKEN_MINUS) {  // unary negation
        advanceToken();  // consume '-'
        auto node = parsePrimary();  // get the expression
        return std::make_unique<Negate>(node.release());  // negate it
    } else if (currentToken.type == TOKEN_NUMBER) {  // number
        int value = std::stoi(currentToken.value);  // convert the token value to integer
        advanceToken();  // consume the number
        return std::make_unique<Integer>(value);  // create a leaf node for the number
    }
    throw std::runtime_error("Unexpected token in parsePrimary");
}

void runTestCases() {   // test cases
    struct TestCase {
        std::string input; // arithmetic expression to evaluate
        int expected;      // expected result of evaluation
    };

    // define test cases
    TestCase testCases[] = {
        {"2+3", 5},
        {"4-1", 3},
        {"5*6", 30},
        {"8/2", 4},
        {"7%3", 1},
        {"(2+3)*4", 20},
        {"4*(1+(2-3))", 4}, // THIS CASE IS CURRENTLY FAILING 2x paren?
        {"-5", -5},
        {"-(3+4)", -7},
        {"2**3", 8},
        {"(2+3)**2", 25},
        {"2+3*4", 14}, 
        {"(2+3)*(4+5)", 45},
        {"1-2-3", -4} 
    };

    for (const auto& testCase : testCases) {
        try {
            initializeLexer(testCase.input);          // initialize lexer with input
            auto syntaxTree = parseE();              // parse the input
            int result = syntaxTree->getValue();    // evaluate the result
            std::cout << "Input: " << testCase.input 
                      << " | Result: " << result
                      << " | Expected: " << testCase.expected 
                      << " | " << (result == testCase.expected ? "PASS" : "FAIL") 
                      << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Input: " << testCase.input 
                      << " | Error: " << e.what() << std::endl;
        }
    }
}

int main() {
    runTestCases();
    return 0;
}
