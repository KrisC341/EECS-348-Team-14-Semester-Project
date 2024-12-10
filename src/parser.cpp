#include <iostream>
#include <string>
#include <cctype>
#include "lexer.h"
#include "ast.h"

using namespace std;

//declares all parsing functions in hierarchical order
treeNode* parseE(const string& input, size_t& pos);
treeNode* parseT(const string& input, size_t& pos);
treeNode* parseP(const string& input, size_t& pos);
treeNode* parseF(const string& input, size_t& pos);

Token prevToken;  //to keep track of past tokens for context (particularly for unary operators)
Token nextToken;

//Function to parse Expressions
treeNode* parseE(const string& input, size_t& pos) {
    treeNode* a = parseT(input, pos);
    while (true) {
        if (::nextToken.type == TokenType::TOKEN_PLUS) { //checks and parses + operators
            if (prevToken.type == TokenType::TOKEN_NUMBER || prevToken.type == TokenType::TOKEN_RPAREN) { 
                //the token is addition if it matches conditions above
                prevToken = nextToken;
                nextToken = scanToken(input, pos);
                if ((::nextToken.type == TokenType::TOKEN_NUMBER) || (::nextToken.type == TokenType::TOKEN_LPAREN)) { //if true, the operator has an operand to right 
                    treeNode* b = parseT(input, pos);
                    a = new Add(a, b);
                }
                else {
                    throw runtime_error("Operator with no operand.");
                }
            }
            else {
                //the token is positive unary if it doesn't match the conditions above
                prevToken = nextToken;
                nextToken = scanToken(input, pos);
                if ((::nextToken.type == TokenType::TOKEN_NUMBER) || (::nextToken.type == TokenType::TOKEN_LPAREN)) { //if true, the operator has an operand to right
                    treeNode* b = parseF(input, pos);
                    a = new Plus(b);
                }
                else {
                    throw runtime_error("Operator with no operand.");
                }
            }
        }
        else if (::nextToken.type == TokenType::TOKEN_MINUS) {  //checks and parses - operators
            if (prevToken.type == TokenType::TOKEN_NUMBER || prevToken.type == TokenType::TOKEN_RPAREN) {
                //the token is subtraction if it matches conditions above
                prevToken = nextToken;
                nextToken = scanToken(input, pos);
                if ((::nextToken.type == TokenType::TOKEN_NUMBER) || (::nextToken.type == TokenType::TOKEN_LPAREN)) { //if true, the operator has an operand to right
                    treeNode* b = parseT(input, pos);
                    a = new Sub(a, b);
                }
                else {
                    throw runtime_error("Operator with no operand.");
                }
            }
            else {
                //the token is negative unary if it doesn't match conditions above
                prevToken = nextToken;
                nextToken = scanToken(input, pos);
                if ((::nextToken.type == TokenType::TOKEN_NUMBER) || (::nextToken.type == TokenType::TOKEN_LPAREN)) { //if true, the operator has an operand to right
                    treeNode* b = parseF(input, pos);
                    a = new Negate(b);
                }
                else {
                    throw runtime_error("Operator with no operand.");
                }
            }
        }
        else {
            return a;
            break;
        }
    }
}

//Function to parse Terms
treeNode* parseT(const string& input, size_t& pos) {
    treeNode* a = parseP(input, pos);
    while (true) {
        if (::nextToken.type == TokenType::TOKEN_STAR) { //checks and parses * operators
            if ((::prevToken.type == TokenType::TOKEN_NUMBER) || (::prevToken.type == TokenType::TOKEN_RPAREN)) { //checks for valid operands to the left of operator
                prevToken = nextToken;
                nextToken = scanToken(input, pos);
                if ((::nextToken.type == TokenType::TOKEN_NUMBER) || (::nextToken.type == TokenType::TOKEN_LPAREN) || (::nextToken.type == TokenType::TOKEN_PLUS) || (::nextToken.type == TokenType::TOKEN_MINUS)) { //checks to ensure operator has a valid operand to right
                    treeNode* b = parseP(input, pos);
                    a = new Multi(a, b);
                }
                else {
                    throw runtime_error("Operator with no operand.");
                }

            }
            else {
                throw runtime_error("Operator with no operand.");
            }
        }
        else if (::nextToken.type == TokenType::TOKEN_SLASH) { //checks and parses / operators
            if ((::prevToken.type == TokenType::TOKEN_NUMBER) || (::prevToken.type == TokenType::TOKEN_RPAREN)) { //checks for valid operands to the left of operator
                prevToken = nextToken;
                nextToken = scanToken(input, pos);
                if ((::nextToken.type == TokenType::TOKEN_NUMBER) || (::nextToken.type == TokenType::TOKEN_LPAREN) || (::nextToken.type == TokenType::TOKEN_PLUS) || (::nextToken.type == TokenType::TOKEN_MINUS)) { //checks to ensure operator has a valid operand to right
                    treeNode* b = parseP(input, pos);
                    a = new Div(a, b);
                }
                else {
                    throw runtime_error("Operator with no operand.");
                }
            }
            else {
                throw runtime_error("Operator with no operand.");
            }
        }
        else if (::nextToken.type == TokenType::TOKEN_MODULO) { //checks and parses % operators
            if ((::prevToken.type == TokenType::TOKEN_NUMBER) || (::prevToken.type == TokenType::TOKEN_RPAREN)) { //checks for valid operands to the left of operator
                prevToken = nextToken;
                nextToken = scanToken(input, pos);
                if ((::nextToken.type == TokenType::TOKEN_NUMBER) || (::nextToken.type == TokenType::TOKEN_LPAREN) || (::nextToken.type == TokenType::TOKEN_PLUS) || (::nextToken.type == TokenType::TOKEN_MINUS)) { //checks to ensure operator has a valid operand to right
                    treeNode* b = parseP(input, pos);
                    a = new Mod(a, b);
                }
                else {
                    throw runtime_error("Operator with no operand.");
                }
            }
            else {
                throw runtime_error("Operator with no operand.");
            }
        }
        else {
            return a;
            break;
        }
    }

}

//function to parse through exponentations, P is simply used as an arbitrary reference to exponentiation, as E was already taken by Expression
treeNode* parseP(const string& input, size_t& pos) {
    treeNode* a = parseF(input, pos);
    while (true) {
        if (::nextToken.type == TokenType::TOKEN_EXPONENT) { //checks and parses ** operators
            if ((::prevToken.type == TokenType::TOKEN_NUMBER) || (::prevToken.type == TokenType::TOKEN_RPAREN)) { //checks for valid operands to the left of operator
                prevToken = nextToken;
                nextToken = scanToken(input, pos);
                if ((::nextToken.type == TokenType::TOKEN_NUMBER) || (::nextToken.type == TokenType::TOKEN_LPAREN) || (::nextToken.type == TokenType::TOKEN_PLUS) || (::nextToken.type == TokenType::TOKEN_MINUS)) { //checks to ensure operator has a valid operand to right
                    treeNode* b = parseF(input, pos);
                    a = new Expo(a, b);
                }
                else {
                    throw runtime_error("Operator with no operand.");
                }
            }
            else {
                throw runtime_error("Operator with no operand.");
            }
        }
        else {
            return a;
        }
    }
}

//function to parse through Factors
treeNode* parseF(const string& input, size_t& pos) {
    while (true) {
        if (::nextToken.type == TokenType::TOKEN_MINUS) { //checks and parses - operators, unary specifically
            prevToken = nextToken;
            nextToken = scanToken(input, pos);
            if (::nextToken.type == TokenType::TOKEN_NUMBER) { //checks for numerical operand
                treeNode* b = parseF(input, pos);
                return new Negate(b);
            }
            else if (::nextToken.type == TokenType::TOKEN_LPAREN) { //checks for parentheses operand
                prevToken = nextToken;
                nextToken = scanToken(input, pos);
                if (::nextToken.type == TokenType::TOKEN_RPAREN) { //if statement = true, this means there is no expression in the parentheses, meaning no argument
                    throw runtime_error("No argument.");
                }
                treeNode* b = parseE(input, pos);
                if (::nextToken.type == TokenType::TOKEN_RPAREN) {
                    prevToken = nextToken;
                    nextToken = scanToken(input, pos);
                    return new Negate(b);
                }
                else {
                    throw runtime_error("Parentheses are mismatched or missing.");
                }
            }
            else {
                throw runtime_error("Operator with no operand.");
            }
        }
        else if (::nextToken.type == TokenType::TOKEN_PLUS) { //checks and parses + operators, unary specifically
            prevToken = nextToken;
            nextToken = scanToken(input, pos);
            if (::nextToken.type == TokenType::TOKEN_NUMBER) {
                treeNode* b = parseF(input, pos);
                return new Plus(b);
            }
            else if (::nextToken.type == TokenType::TOKEN_LPAREN) { //checks and parses parentheses operators
                prevToken = nextToken;
                nextToken = scanToken(input, pos);
                if (::nextToken.type == TokenType::TOKEN_RPAREN) { //if statement = true, this means there is no expression in the parentheses, meaning no argument
                    throw runtime_error("No argument.");
                }
                treeNode* b = parseE(input, pos);
                if (::nextToken.type == TokenType::TOKEN_RPAREN) { //checks to make sure there is a closing parentheses
                    prevToken = nextToken;
                    nextToken = scanToken(input, pos);
                    return new Plus(b);
                }
                else {
                    throw runtime_error("Parentheses are mismatched or missing.");
                }
            }
        }
        else if (::nextToken.type == TokenType::TOKEN_NUMBER) { //parses through numerical operands
            if ((::prevToken.type == TokenType::TOKEN_PLUS) || (::prevToken.type == TokenType::TOKEN_MINUS) || (::prevToken.type == TokenType::TOKEN_STAR) || (::prevToken.type == TokenType::TOKEN_SLASH) || (::prevToken.type == TokenType::TOKEN_MODULO) || (::prevToken.type == TokenType::TOKEN_EXPONENT) || (::prevToken.type == TokenType::TOKEN_LPAREN) || (::prevToken.type == TokenType::TOKEN_START)) { //checks for valid operands to the left of operator
                float num = stof(::nextToken.value);
                treeNode* a = new Integer(num);
                prevToken = nextToken;
                nextToken = scanToken(input, pos);
                if ((::nextToken.type == TokenType::TOKEN_PLUS) || (::nextToken.type == TokenType::TOKEN_MINUS) || (::nextToken.type == TokenType::TOKEN_STAR) || (::nextToken.type == TokenType::TOKEN_SLASH) || (::nextToken.type == TokenType::TOKEN_MODULO) || (::nextToken.type == TokenType::TOKEN_EXPONENT) || (::nextToken.type == TokenType::TOKEN_RPAREN) || (::nextToken.type == TokenType::TOKEN_END)) { //checks for valid operands to the right of operator
                    return a;
                }
                else {
                    throw runtime_error("Operand missing operator.");
                }
            }
            else {
                throw runtime_error("Operand missing operator.");
            }

        }
        else if (::nextToken.type == TokenType::TOKEN_LPAREN) { //checks and parses parentheses operators
            if ((::prevToken.type == TokenType::TOKEN_PLUS) || (::prevToken.type == TokenType::TOKEN_MINUS) || (::prevToken.type == TokenType::TOKEN_STAR) || (::prevToken.type == TokenType::TOKEN_SLASH) || (::prevToken.type == TokenType::TOKEN_MODULO) || (::prevToken.type == TokenType::TOKEN_EXPONENT) || (::prevToken.type == TokenType::TOKEN_LPAREN) || (::prevToken.type == TokenType::TOKEN_START)) { //checks for valid operands to the left of operator
                prevToken = nextToken;
                nextToken = scanToken(input, pos);
                if (::nextToken.type == TokenType::TOKEN_RPAREN) { //if statement = true, this means there is no expression in the parentheses, meaning no argument
                    throw runtime_error("No argument.");
                }
                treeNode* a = parseE(input, pos);
                if (a == NULL) { return NULL; } //checks to ensure non-empty input in the parentheses
                if (::nextToken.type == TokenType::TOKEN_RPAREN) { //ensures parentheses are closed
                    prevToken = nextToken;
                    nextToken = scanToken(input, pos);
                    return a;
                }
                else {
                    throw runtime_error("Parentheses are mismatched or missing.");
                }
            }
            else {
                throw runtime_error("Operand missing operator (parentheses)");
            }
        }
        else if (::nextToken.type == TokenType::TOKEN_END) { //validates and returns a flag for the end of the expression given
            return NULL;
        }
        else if (::nextToken.type == TokenType::TOKEN_RPAREN) { //a parenthese was hit without an accompanything left paren
            throw runtime_error("Parentheses are mismatched or missing. line 251");
        }
        else {
            return NULL;
        }
    }
}


int main() {
    //initializes trackers for input
    size_t pos = 0;
    string input;
    do { //activates primary loop the program runs in
        try {
            pos = 0; //reset of trackers every loop
            input = "";
            cout << "Enter an arithmetic expression (Input 'E' to exit): "; //asks for arithmetic expression to evaluate
            getline(cin, input);

            if (input.empty()) { //checks for empty input
                throw runtime_error("No argument provided. Please enter a valid expression.");
            }

            if (input == "E") { //checks if the user wishes to exit the program
                break;
            }

            nextToken = scanToken(input, pos); //initializes tokenization of input
            prevToken.type = TokenType::TOKEN_START; //sets previous token as start, to avoid recursive issues

            treeNode* resultTree = parseE(input, pos); //begins creation of expression tree

            //output the result
            if (resultTree != nullptr) {
                cout << "Result: " << resultTree->getValue() << endl;
            }
            else {
                throw runtime_error("Failed to parse the input expression.");
            }
        }
        catch (const exception& e) { //handles any errors caught during program run.
            cout << "Error: " << e.what() << endl;
        }
    } while (input != "E");

    cout << "Program terminating.";

    return 0;
}