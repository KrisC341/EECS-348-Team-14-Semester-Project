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
    int getValue() {
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
    int getValue() {
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

