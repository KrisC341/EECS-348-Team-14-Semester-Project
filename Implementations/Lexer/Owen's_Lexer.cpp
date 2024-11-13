#include <iostream>
#include <string.h>

using namespace std;


//Define the different token identifiers
enum TokenID{
    Number,
    OpenPar,
    ClosePar,
    Exp,
    Mult,
    Div,
    Mod,
    Plus,
    Minus,
    Invalid,
    End
};

//Create the token struct with an ID and a value
struct Token {
    TokenID TokenType;
    string value;
};


//Class to handle the lexer
class Lexer{
    public:
    //Constructor takes the input string from the user. cur_pos is initially 0 and size is the length of the string.
        Lexer(string user_string_input) : input(user_string_input), size(input.size()), cur_pos(0) {

        };
    
    //Method which actually gets the token from the current position in the string.
    Token GetToken(){
        //Return an error if the current position is greater than the size
        if (cur_pos >= size){
            return {End, "---Went Past Size Limit---"};
        }


        char cur_token = input[cur_pos]; //Stores the value of the current position as a character

        //Ignore spaces
        while(isspace(cur_token)){
            cur_pos++;
            if (cur_pos < size) {
                cur_token = input[cur_pos];  // Check the next space for the token
            }
        }

        //Returns the token as an exponent only if the current and next position are '*'
        if(cur_token == '*' && input[cur_pos +1] == '*'){
            cur_pos +=2; //Go ahead by 2 positions
            return {Exp, "**"};
        }
        

        //Returns the token as a number
        if (isdigit(cur_token)){ //check if the current position is a digit
            string num; //stores the number. Initially empty
            //Concatinate 'num' with the next position's values so long as they are either digits or a decimal
            while(isdigit(cur_token) || cur_token == '.'){
                num = num + cur_token; 
                cur_token = input[++cur_pos];
                }
            return {Number, num};
        }

        //Switch statement for the rest of the operators
        switch(cur_token){
            case '(':
                cur_pos++;
                return {OpenPar, "("};

            case ')':
                cur_pos++;
                return {ClosePar, ")"};

            case '*':
                cur_pos++;
                return {Mult, "*"};

            case '/':
                cur_pos++;
                return {Div, "/"};

            case '%':
                cur_pos++;
                return {Mod, "%"};

            case '+':
                cur_pos++;
                return {Plus, "+"};

            case '-':
                cur_pos++;
                return {Minus, "-"};
            default:
                return {Invalid, "---Error---"};
        }
        return {Invalid, "---Error---"};
        }
    
    private:
        string input;
        int size;
        int cur_pos;

};

int main() {
    string user_str = "(9+g8/  6)";
    Lexer test(user_str);

    //get the first token
    Token token = test.GetToken();

    //Loop through the string and get tokens
    while (token.TokenType != End || token.TokenType != Invalid) {
        // Exit out if the token is invalid
        if (token.TokenType == Invalid) {
            cout << "Error: Invalid token '" << token.value;
            break;
        }
        cout << "Token Value: " << token.value << endl;  //Print the valid token
        token = test.GetToken();  //Get next token
    }

    return 0;
}
