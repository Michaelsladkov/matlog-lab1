#ifndef _ANALYSIS
#define _ANALYSIS

#include "../parsing/Operations.h"

#include <map>
#include <utility>
#include <stdint.h>

enum options {
    UNSATISFIABLE,
    SATISFIABLE,
    VALID
};
typedef enum options OPTIONS;

enum options analyse(Expression* tree, std::map<std::string, Variable*>* variables, std::pair<uint16_t, uint16_t>*);

#endif