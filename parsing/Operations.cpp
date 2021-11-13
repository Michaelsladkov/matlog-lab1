#ifndef _OPERATIONS
#define _OPERATIONS

struct Expression {
    virtual bool evaluate();
    virtual ~Expression();
};
typedef struct Expression Expression;

struct Variable : Expression {
    Variable(bool value)
        : value(value)
    {}
    virtual bool evaluate() override {
        return value;
    }

    void set_value(bool new_value) {
        value = new_value;
    }

    private:
        bool value;
};
typedef struct Variable Variable;

struct Binary_operation : Expression {
    Expression* left;
    Expression* right;
    virtual ~Binary_operation() override {
        delete left;
        delete right;
    }
};
typedef struct Binary_operation Binary_operation;

struct Unary_operation : Expression {
    virtual bool evaluate();
    Expression* operand;
    virtual ~Unary_operation() override {
        delete operand;
    }
};
typedef struct Unary_operation Unary_operation;

struct Inversion : Unary_operation {
    virtual bool evaluate() override {
        return ! (operand -> evaluate());
    }
};
typedef struct Inversion Inversion;

struct And_operation : Binary_operation {
    virtual bool evaluate() override {
        return left -> evaluate() && right -> evaluate();
    }
};
typedef struct And_operation And;

struct Or_operation : Binary_operation {
    virtual bool evaluate() override {
        return left -> evaluate() || right -> evaluate();
    }
};
typedef struct Or_operation Or;

struct Implication : Binary_operation {
    virtual bool evaluate() override {
        bool a = left -> evaluate();
        bool b = right -> evaluate();
        return !a || b;
    }
};
typedef struct Implication Implication;
#endif