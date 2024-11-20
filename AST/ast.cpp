#include <cmath>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;


class treeNode {
public:

    //'treeNode' destructor
    //Made virtual to ensure thorough deconstruction
    virtual ~treeNode() {}

    //Define a generic 'getValue' function for all dervied class to use
    virtual int getValue() = 0;

};


class Integer : public treeNode {
private:
    int value;

public:

    //'Integer' constructor 
    Integer(int val) {
        value = val;
    }

    //Return integer value (leaf node)
    int getValue() override {
        return value;
    }

};



class Add : public treeNode {
private:

    // Define left and right tree nodes as pointers
    treeNode* left;
    treeNode* right;

public:

    //'Add' constructor with parameters for left and right subtrees
    Add(treeNode* l, treeNode* r) {
        left = l;
        right  = r;
    }

    //'Add' deconstructor to free allocated memory of left and right nodes
    ~Add() {
        delete left;
        delete right;
    }

    //Recursively getValue left and right subtrees
    //Add the results and return it
    int getValue() override {
        return left -> getValue() + right -> getValue();
    }

};

 

class Sub : public treeNode {
private:
    treeNode* left;
    treeNode* right;

public:
    Sub(treeNode* l, treeNode* r) : left(l), right(r) {}

    ~Sub() {
        delete left;
        delete right;
    }

    int getValue() override {
        return left->getValue() - right->getValue();
    }
};

// Multi Node
class Multi : public treeNode {
private:
    treeNode* left;
    treeNode* right;

public:
    Multi(treeNode* l, treeNode* r) : left(l), right(r) {}

    ~Multi() {
        delete left;
        delete right;
    }

    int getValue() override {
        return left->getValue() * right->getValue();
    }
};

// Div Node
class Div : public treeNode {
private:
    treeNode* left;
    treeNode* right;

public:
    Div(treeNode* l, treeNode* r) : left(l), right(r) {}

    ~Div() {
        delete left;
        delete right;
    }

    int getValue() override {
        int divisor = right->getValue();
        if (divisor == 0) {
            cout << "Error: Division by zero." << endl;
            return 0;
        }
        return left->getValue() / divisor;
    }
};

// Negate Node -Unary Operation
class Negate : public treeNode {
private:
    treeNode* operand;

public:
    Negate(treeNode* op) : operand(op) {}

    ~Negate() {
        delete operand;
    }

    int getValue() override {
        return -operand->getValue();
    }
};

class Exponent : public treeNode {
private:
    treeNode* base;
    treeNode* exponent;

public:

    //'Add' constructor with parameters for left and right subtrees
    Exponent(treeNode* b, treeNode* e) {
        base = b;
        exponent  = e;
    }
    
    ~Exponent() {
        delete base;
        delete exponent;
    }

    int getValue() override {
        int baseValue = base->getValue();
        int exponentValue = exponent->getValue();

        // Handling negative exponents, if unsupported
        if (exponentValue < 0) {
            cout << "Error: Negative exponents not supported for integers." << endl;
            return 0; 
        }

        int result = 1;

        // Loop through and multiply the base value 'exponentValue' number of time
        for (int i = 0; i < exponentValue; ++i) {
            result *= baseValue;
        }

        return result;

        }

};

class Modulo : public treeNode {
private:
    treeNode* left;
    treeNode* right;

public:
    Modulo(treeNode* l, treeNode* r) {
        left = l;
        right = r;
    }

    ~Modulo() {
        delete left;
        delete right;
    }

    int getValue() override {
        int divisor = right->getValue();

        // Handle invalid mod zero
        if (divisor == 0) {
            cout << "Error: Modulo by zero." << endl;
            return 0;
        }
        return left->getValue() % divisor;

    }


};
