#ifndef _ANALYSIS
#define _ANALYSIS

#include "../parsing/Operations.h"

#include <set>

enum options {
    UNSATISFIABLE,
    SATISFIABLE,
    VALID
};
typedef enum options OPTIONS;

enum options analyse(Expression* tree, std::set<Variable*>* variables);

#endif