#include "analysis.h"

#include <stdint.h>
#include <cmath>
#include <iostream>

static size_t create_array_from_set(Variable*** array, std::set<Variable*>* set) {
    *array = new Variable*[set -> size()];
    Variable** ptr = *array;
    for (Variable* v : *set) {
        **array = v;
        array ++;
    }
    return set -> size();
}

static void next_combination(Variable** array, size_t size) {
    bool value = array[0] -> get_value();
    array[0] -> set_value(!value);
    std::cout << array[0] -> get_value();
    bool carry = value; 
    for (size_t i = 1; i < size; i++) {
        value = array[i] -> get_value();
        array[i] -> set_value(value^carry);
        carry = value && carry;
        std::cout << array[i] -> get_value();
    }
}

enum options analyse(Expression* tree, std::set<Variable*>* variables_set) {
    Variable** variables_array = NULL;
    size_t array_size = create_array_from_set(&variables_array, variables_set);
    bool satisfied = tree -> evaluate();
    bool unsatisfied = !(tree -> evaluate());
    bool value;
    for (size_t c = 0; c < std::pow(2, array_size) - 1; c++)
    {
        next_combination(variables_array, array_size);
        std::cout << "incremented" << std::endl;
        value = tree -> evaluate();
        satisfied &= value;
        unsatisfied &= !value;
    }
    if (unsatisfied) return UNSATISFIABLE;
    else if (satisfied) return VALID;
    else return SATISFIABLE;
}