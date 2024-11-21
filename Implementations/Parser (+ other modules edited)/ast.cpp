#include "ast.h"

// Integer class constructor
Integer::Integer(float val) : value(val) {}

// Integer class getValue method
float Integer::getValue() {
    return value;
}

// Add class constructor
Add::Add(treeNode* l, treeNode* r) : left(l), right(r) {}

// Add class destructor
Add::~Add() {
    delete left;
    delete right;
}

// Add class getValue method
float Add::getValue() {
    return left->getValue() + right->getValue();
}

// Expo class constructor
Expo::Expo(treeNode* l, treeNode* r) : left(l), right(r) {}

// Expo class destructor
Expo::~Expo() {
    delete left;
    delete right;
}

// Expo class getValue method
float Expo::getValue() {
    return std::pow(left->getValue(), right->getValue());
}

// Sub class constructor
Sub::Sub(treeNode* l, treeNode* r) : left(l), right(r) {}

// Sub class destructor
Sub::~Sub() {
    delete left;
    delete right;
}

// Sub class getValue method
float Sub::getValue() {
    return left->getValue() - right->getValue();
}

// Multi class constructor
Multi::Multi(treeNode* l, treeNode* r) : left(l), right(r) {}

// Multi class destructor
Multi::~Multi() {
    delete left;
    delete right;
}

// Multi class getValue method
float Multi::getValue() {
    return left->getValue() * right->getValue();
}

// Div class constructor
Div::Div(treeNode* l, treeNode* r) : left(l), right(r) {}

// Div class destructor
Div::~Div() {
    delete left;
    delete right;
}

// Div class getValue method
float Div::getValue() {
    float divisor = right->getValue();
    if (divisor == 0) {
        cout << "Error: Division by zero." << endl;
        return 0;
    }
    return left->getValue() / divisor;
}

// Mod class constructor
Mod::Mod(treeNode* l, treeNode* r) : left(l), right(r) {}

// Mod class destructor
Mod::~Mod() {
    delete left;
    delete right;
}

// Mod class getValue method
float Mod::getValue() {
    return static_cast<int>(left->getValue()) % static_cast<int>(right->getValue());
}

// Plus class constructor
Plus::Plus(treeNode* op) : operand(op) {}

// Plus class destructor
Plus::~Plus() {
    delete operand;
}

// Plus class getValue method
float Plus::getValue() {
    return operand->getValue();
}

// Negate class constructor
Negate::Negate(treeNode* op) : operand(op) {}

// Negate class destructor
Negate::~Negate() {
    delete operand;
}

// Negate class getValue method
float Negate::getValue() {
    return -(operand->getValue());
}