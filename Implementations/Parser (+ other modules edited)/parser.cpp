#include <iostream>
#include <string>
#include <cctype>
#include "lexer.h"
#include "ast.h"

treeNode* parseE(const std::string& input, size_t& pos);
treeNode* parseT(const std::string& input, size_t& pos);
treeNode* parseP(const std::string& input, size_t& pos);
treeNode* parseF(const std::string& input, size_t& pos);

Token prevToken;  //to keep track of past tokens for context (particularly for unary operators)
Token nextToken;

//Function to parse Expressions
treeNode* parseE(const string& input, size_t& pos) {
    treeNode* a = parseT(input, pos);
    while (true) {
            if (::nextToken.type == TokenType::TOKEN_PLUS) {
                if (prevToken.type == TokenType::TOKEN_NUMBER || prevToken.type == TokenType::TOKEN_RPAREN) {
                    //the token is addition if it matches conditions above
                    prevToken = nextToken;
                    nextToken = scanToken(input, pos);
                    if ((::nextToken.type == TokenType::TOKEN_NUMBER) || (::nextToken.type == TokenType::TOKEN_LPAREN)) {
                        treeNode* b = parseT(input, pos);
                        a = new Add(a, b);
                    }
                    else {
                        throw std::runtime_error("Operator with no operand.");
                    }
                }
                else {
                    //the token is positive unary if it doesn't match the conditions above
                    prevToken = nextToken;
                    nextToken = scanToken(input, pos);
                    if((::nextToken.type == TokenType::TOKEN_NUMBER) || (::nextToken.type == TokenType::TOKEN_LPAREN)) {
                        treeNode* b = parseF(input, pos);
                        a = new Plus(b);
                    }
                    else {
                        throw std::runtime_error("Operator with no operand.");
                    }
                }
            }
            else if (::nextToken.type == TokenType::TOKEN_MINUS) { //might cause problems with negation but we'll get to it later
                if (prevToken.type == TokenType::TOKEN_NUMBER || prevToken.type == TokenType::TOKEN_RPAREN) {
                    //the token is subtraction if it matches conditions above
                    prevToken = nextToken;
                    nextToken = scanToken(input, pos);
                    if ((::nextToken.type == TokenType::TOKEN_NUMBER) || (::nextToken.type == TokenType::TOKEN_LPAREN)) {
                        treeNode* b = parseT(input, pos);
                        a = new Sub(a, b);
                    }
                    else {
                        throw std::runtime_error("Operator with no operand.");
                    }
                }
                else {
                    //the token is negative unary if it doesn't match conditions above
                    prevToken = nextToken;
                    nextToken = scanToken(input, pos);
                    if ((::nextToken.type == TokenType::TOKEN_NUMBER) || (::nextToken.type == TokenType::TOKEN_LPAREN)) {
                        treeNode* b = parseF(input, pos);
                        a = new Negate(b);
                    }
                    else {
                        throw std::runtime_error("Operator with no operand.");
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
        if (::nextToken.type == TokenType::TOKEN_STAR) {
            if ((::prevToken.type == TokenType::TOKEN_NUMBER) || (::prevToken.type == TokenType::TOKEN_RPAREN)) {
                prevToken = nextToken;
                nextToken = scanToken(input, pos);
                if ((::nextToken.type == TokenType::TOKEN_NUMBER) || (::nextToken.type == TokenType::TOKEN_LPAREN) || (::nextToken.type == TokenType::TOKEN_PLUS) || (::nextToken.type == TokenType::TOKEN_MINUS)) {
                    treeNode* b = parseP(input, pos);
                    a = new Multi(a, b);
                }
                else {
                    throw std::runtime_error("Operator with no operand.");
                }

            }
            else {
                throw std::runtime_error("Operator with no operand.");
            }
        }
        else if (::nextToken.type == TokenType::TOKEN_SLASH) {
            if ((::prevToken.type == TokenType::TOKEN_NUMBER) || (::prevToken.type == TokenType::TOKEN_RPAREN)) {
                prevToken = nextToken;
                nextToken = scanToken(input, pos);
                if ((::nextToken.type == TokenType::TOKEN_NUMBER) || (::nextToken.type == TokenType::TOKEN_LPAREN) || (::nextToken.type == TokenType::TOKEN_PLUS) || (::nextToken.type == TokenType::TOKEN_MINUS)) {
                    treeNode* b = parseP(input, pos);
                    a = new Div(a, b);
                }
                else {
                    throw std::runtime_error("Operator with no operand.");
                }
            }
            else {
                throw std::runtime_error("Operator with no operand.");
            }
        }
        else if (::nextToken.type == TokenType::TOKEN_MODULO) {
            if ((::prevToken.type == TokenType::TOKEN_NUMBER) || (::prevToken.type == TokenType::TOKEN_RPAREN)) {
                prevToken = nextToken;
                nextToken = scanToken(input, pos);
                if ((::nextToken.type == TokenType::TOKEN_NUMBER) || (::nextToken.type == TokenType::TOKEN_LPAREN) || (::nextToken.type == TokenType::TOKEN_PLUS) || (::nextToken.type == TokenType::TOKEN_MINUS)) {
                    treeNode* b = parseP(input, pos);
                    a = new Mod(a, b);
                }
                else {
                    throw std::runtime_error("Operator with no operand.");
                }
            }
            else {
                throw std::runtime_error("Operator with no operand.");
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
        if (::nextToken.type == TokenType::TOKEN_EXPONENT) {  
            if ((::prevToken.type == TokenType::TOKEN_NUMBER) || (::prevToken.type == TokenType::TOKEN_RPAREN)) {
                prevToken = nextToken;
                nextToken = scanToken(input, pos);
                if ((::nextToken.type == TokenType::TOKEN_NUMBER) || (::nextToken.type == TokenType::TOKEN_LPAREN) || (::nextToken.type == TokenType::TOKEN_PLUS) || (::nextToken.type == TokenType::TOKEN_MINUS)) {
                    treeNode* b = parseF(input, pos);
                    a = new Expo(a, b);
                }
                else {
                    throw std::runtime_error("Operator with no operand.");
                }
            }
            else {
                throw std::runtime_error("Operator with no operand.");
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
        if (::nextToken.type == TokenType::TOKEN_MINUS) {
            prevToken = nextToken;
            nextToken = scanToken(input, pos);
            if (::nextToken.type == TokenType::TOKEN_NUMBER) {
                treeNode* b = parseF(input, pos);
                return new Negate(b);
            }
            else if (::nextToken.type == TokenType::TOKEN_LPAREN) {
                prevToken = nextToken;
                nextToken = scanToken(input, pos);
                treeNode* b = parseE(input, pos);
                if (::nextToken.type == TokenType::TOKEN_RPAREN) {
                    prevToken = nextToken;
                    nextToken = scanToken(input, pos);
                    return new Negate(b);
                }
                else {
                    throw std::runtime_error("Parentheses are mismatched or missing. Line 185");
                }
            }
            else {
                throw std::runtime_error("Operator with no operand.");
            }
        }
        else if (::nextToken.type == TokenType::TOKEN_PLUS) {
            prevToken = nextToken;
            nextToken = scanToken(input, pos);
            if (::nextToken.type == TokenType::TOKEN_NUMBER) {
                treeNode* b = parseF(input, pos);
                return new Plus(b);
            }
            else if (::nextToken.type == TokenType::TOKEN_LPAREN) {
                prevToken = nextToken;
                nextToken = scanToken(input, pos);
                treeNode* b = parseE(input, pos);
                if (::nextToken.type == TokenType::TOKEN_RPAREN) {
                    prevToken = nextToken;
                    nextToken = scanToken(input, pos);
                    return new Plus(b);
                }
                else {
                    throw std::runtime_error("Parentheses are mismatched or missing. line 206");
                }
            }
        }
        else if (::nextToken.type == TokenType::TOKEN_NUMBER) {
            if ((::prevToken.type == TokenType::TOKEN_PLUS) || (::prevToken.type == TokenType::TOKEN_MINUS) || (::prevToken.type == TokenType::TOKEN_STAR) || (::prevToken.type == TokenType::TOKEN_SLASH) || (::prevToken.type == TokenType::TOKEN_MODULO) || (::prevToken.type == TokenType::TOKEN_EXPONENT) || (::prevToken.type == TokenType::TOKEN_LPAREN) || (::prevToken.type == TokenType::TOKEN_START)) {
                float num = std::stof(::nextToken.value);
                treeNode* a = new Integer(num);
                prevToken = nextToken;
                nextToken = scanToken(input, pos);
                if ((::nextToken.type == TokenType::TOKEN_PLUS) || (::nextToken.type == TokenType::TOKEN_MINUS) || (::nextToken.type == TokenType::TOKEN_STAR) || (::nextToken.type == TokenType::TOKEN_SLASH) || (::nextToken.type == TokenType::TOKEN_MODULO) || (::nextToken.type == TokenType::TOKEN_EXPONENT) || (::nextToken.type == TokenType::TOKEN_RPAREN) || (::nextToken.type == TokenType::TOKEN_END)) {
                    return a;
                }
                else {
                    throw std::runtime_error("Operand missing operator.");
                }
            }
            else {
                throw std::runtime_error("Operand missing operator.");
            }
            
        }
        else if (::nextToken.type == TokenType::TOKEN_LPAREN) {
            if ((::prevToken.type == TokenType::TOKEN_PLUS) || (::prevToken.type == TokenType::TOKEN_MINUS) || (::prevToken.type == TokenType::TOKEN_STAR) || (::prevToken.type == TokenType::TOKEN_SLASH) || (::prevToken.type == TokenType::TOKEN_MODULO) || (::prevToken.type == TokenType::TOKEN_EXPONENT) || (::prevToken.type == TokenType::TOKEN_LPAREN) || (::prevToken.type == TokenType::TOKEN_START)){
                prevToken = nextToken;
                nextToken = scanToken(input, pos);
                treeNode* a = parseE(input, pos);
                if (a == NULL) { return NULL; }
                if (::nextToken.type == TokenType::TOKEN_RPAREN) {
                    prevToken = nextToken;
                    nextToken = scanToken(input, pos);
                    return a;
                }
                else {
                    throw std::runtime_error("Parentheses are mismatched or missing. line 240");
                }
            }
            else {
                throw std::runtime_error("Operand missing operator (parentheses)");
            }
        }
        else if(::nextToken.type == TokenType::TOKEN_END){
            return NULL;
        }
        else if (::nextToken.type == TokenType::TOKEN_RPAREN) { //a parenthese was hit without an accompanything left paren
            throw std::runtime_error("Parentheses are mismatched or missing. line 251");
        }
        else {
            return NULL;
        }
    } 
}


//driver main, for testing while coding
int main() {
    size_t pos = 0;
    string input = "((7 * 3) ^ 2)";
    //-(+2) * (+3) - (-4) / (-5)
    try {
        nextToken = scanToken(input, pos);
        prevToken.type = TokenType::TOKEN_START; //sets previous token as start, to avoid recursive issues
        treeNode* resultTree = parseE(input, pos);

        std::cout << resultTree->getValue() << std::endl;
    }
    catch (const std::exception& e) {
        cout << "Error: " << e.what() << std::endl;
    }
}