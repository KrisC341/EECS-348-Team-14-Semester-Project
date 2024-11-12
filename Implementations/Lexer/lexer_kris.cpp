#include <iostream>
#include <string>
#include <cctype>

using std::string;
using std::isspace;
using std::isdigit;

//creates an enumeration as a easy way to categorize what ASCII character has been tokenized
enum TokenType {
    NUMBER,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    LPAREN,
    RPAREN,
    END,
    ERROR
};

//struct is initalized that stores what type of ASCII character is stored within the token, and what the value of said character (if any) is
struct Token {
    TokenType type;
    string value;
};

//scanToken function takes in the address of a string input and the current position along said input that the lexer is at (this position is tracked through a global variable)
Token scanToken(const string &input, size_t &pos){
    Token result; //Initalizes the token that will be returned at the end of the function
    
    //While loop checks for any whitespace and advances the position of the lexer along the input until it hits a valid ASCII character than can be tokenized
    while(pos < input.size() && isspace(input[pos])){
        pos++;
    }

    //if block checks that the end of the input hasn't been found. If it has been found, it returns an END token, signifying no more characters are left for the lexer to tokenize
    if(pos >= input.size()){
        result.type = END;
        result.value = "";
        return result;
    }

    //Initalizes a character variable to store the current ASCII character the lexer is pointing at
    char currentChar = input[pos];

    //number lexer - if the currentChar is a digit, the if-block will ensure all ASCII characters apart of the overall number are included in a single token
    if(isdigit(currentChar)){
        string num; //initalizes a string variable that will serve as the value of this numerical token
        while(pos < input.size() && isdigit(input[pos])){  //This while loop ensures all ASCII characters apart of the overall number are included in a single token through string concatenation
            num += input[pos];
            pos++;
        }
        result.type = NUMBER;
        result.value = num;
        return result;
    }

    //operator lexer - If the currentChar is not a digit, it must either be an operator, a parenthesis, or some third case indicative of an error. 
    //The following switch block goes through all possible cases and adjusts the result tokens type and value accordingly. 
    switch(currentChar){
        case '+':
            pos++;
            result.type = PLUS;
            result.value = "+";
            return result;
        case '-':
            pos++;
            result.type = MINUS;
            result.value = "-";
            return result;
        case '*':
            pos++;
            result.type = STAR;
            result.value = "*";
            return result;
        case '/':
            pos++;
            result.type = SLASH;
            result.value = "/";
            return result;
        case '(':
            pos++;
            result.type = LPAREN;
            result.value = "(";
            return result;
        case ')':
            pos++;
            result.type = RPAREN;
            result.value = ")";
            return result;
        default: //INSERT LATER ERROR HANDLING
            pos++;
            result.type = ERROR;
            result.value = "ERROR";
            return result;
    }

}

//This main isn't a part of the official package, just simple implementation testing while developing (NOT A PART OF THE OFFICIAL TEST CASES)
int main(){
    size_t pos = 0;
    string input = "-(36+5)*2";
    Token currentToken;
    do{
        currentToken = scanToken(input, pos);
        std::cout << currentToken.value << std::endl;
    } while(currentToken.value != "");


    return 0;
}