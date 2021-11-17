#ifndef _OPERATIONS
#define _OPERATIONS

#include <string>
#include <iostream>

struct Expression {
    virtual bool evaluate() = 0;
    virtual void print() = 0;
    virtual ~Expression(){}
};
typedef struct Expression Expression;

struct Variable : Expression {
    Variable(bool value, std::string name)
        : value(value), name(name)
    {}
    virtual bool evaluate() override {
        return value;
    }

    void set_value(bool new_value) {
        value = new_value;
    }

    virtual void print() override {
        std::cout << name;
    }

    virtual ~Variable() override {
        delete &name;
    }

    private:
        bool value;
        std::string name;
};
typedef struct Variable Variable;

struct Binary_operation : Expression {
    Expression* left;
    Expression* right;
    std::string type;
    virtual bool evaluate() override {
        if (type == "|") {
            return left -> evaluate() || right -> evaluate();
        }
        if (type == "&") {
            return left -> evaluate() && right -> evaluate();
        }
        if (type == "->") {
            bool l = left -> evaluate();
            bool r = right -> evaluate();
            return !l || r;
        }
        return false;
    }
    
    virtual void print() override {
        std::cout << "(" << type << ",";
        left -> print();
        std::cout << ",";
        right -> print();
        std::cout << ")";
    }

    virtual ~Binary_operation() override {
        delete left;
        delete right;
    }
};
typedef struct Binary_operation Binary_operation;

struct Unary_operation : Expression {
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
    virtual void print() override {
        std::cout << "(!";
        operand -> print();
        std::cout << ")";
    }
    virtual ~Inversion() override {};
};
typedef struct Inversion Inversion;

#endif