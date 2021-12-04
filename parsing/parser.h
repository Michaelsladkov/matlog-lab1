#ifndef _PARSER
#define _PARSER

#include "Operations.h"

#include <vector>
#include <string>
#include <map>

Expression* parse_expression(std::vector<std::string>);
void print_tree (Expression *);
std::map<std::string, Variable*>* get_variables();

#endif