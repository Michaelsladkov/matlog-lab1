#ifndef _PARSER
#define _PARSER

#include "Operations.h"

#include <vector>
#include <string>

Expression* parse_expression(std::vector<std::string>);
void print_tree (Expression *);

#endif