#include "parser.h"

#include <iostream>

void print_tree (Expression * tree) {
    tree -> print();
    std::cout << std::endl;
}