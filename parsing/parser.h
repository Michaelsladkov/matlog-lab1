#ifndef _PARSER
#define _PARSER

#include "Operations.h"

#include <vector>
#include <string>
#include <set>

Expression* parse_expression(std::vector<std::string>);
void print_tree (Expression *);
std::set<Variable*>* get_variables_set();

#endif