#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

// Abstract base class for tree nodes
class treeNode {
public:
    // Destructor method, erases objects
    virtual ~treeNode() {}

    // Virtual function to allow program to get the value of any treeNode without accessing info directly, all subclasses will override this method
    virtual float getValue() = 0;
};

// Integer node with an integer value
class Integer : public treeNode {
private:
    float value;

public:
    // Constructor
    Integer(float val);

    // Override getValue()
    float getValue() override;
};

// Add node that performs addition on two subtrees
class Add : public treeNode {
private:
    treeNode* left;   
    treeNode* right;  

public:
    // Constructor
    Add(treeNode* l, treeNode* r);

    // Destructor
    ~Add();

    // Override getValue()
    float getValue() override;
};

// Expo node that performs exponentiation on two subtrees
class Expo : public treeNode {
private:
    treeNode* left;
    treeNode* right;

public:
    // Constructor 
    Expo(treeNode* l, treeNode* r);

    // Destructor
    ~Expo();

    // Override getValue()
    float getValue() override;
};

// Sub node that performs subtraction on two subtrees
class Sub : public treeNode {
private:
    treeNode* left;
    treeNode* right;

public:
    // Constructor
    Sub(treeNode* l, treeNode* r);

    // Destructor
    ~Sub();

    // Override getValue()
    float getValue() override;
};

// Multi node that performs multiplication on two subtrees
class Multi : public treeNode {
private:
    treeNode* left;
    treeNode* right;

public:
    // Constructor
    Multi(treeNode* l, treeNode* r);

    // Destructor
    ~Multi();

    // Override getValue()
    float getValue() override;
};

// Div node that performs division on two subtrees
class Div : public treeNode {
private:
    treeNode* left;
    treeNode* right;

public:
    // Constructor
    Div(treeNode* l, treeNode* r);

    // Destructor
    ~Div();

    // Override getValue()
    float getValue() override;
};

// Mod node that performs modulus on two subtrees
class Mod : public treeNode {
private:
    treeNode* left;
    treeNode* right;

public:
    // Constructor
    Mod(treeNode* l, treeNode* r);

    // Destructor
    ~Mod();

    // Override getValue()
    float getValue() override;
};

// Negate, a unary node that negates the value of its operand
class Negate : public treeNode {
private:
    treeNode* operand;

public:
    // Constructor
    Negate(treeNode* op);

    // Destructor
    ~Negate();

    // Override getValue()
    float getValue() override;
};

// Plus, a unary node that simply keeps the value of its operand positive
class Plus : public treeNode {
private:
    treeNode* operand;

public:
    // Constructor
    Plus(treeNode* op);

    // Destructoe
    ~Plus();

    // Override getValue()
    float getValue() override;
};