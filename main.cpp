#include "preprocessing/preprocessor.h"
#include "parsing/parser.h"
#include "analysis/analysis.h"

#include <iostream>
#include <vector>
#include <string>
#include <set>

int main() {
    std::string input;
    std::getline(std::cin, input);
    char* without_spaces = remove_spaces(input.data());
    std::vector<std::string> lexemes;
    get_lexemes(without_spaces, &lexemes);
    Expression* tree = parse_expression(lexemes);
    std::set<Variable*>* vars = get_variables_set();
    OPTIONS res = analyse(tree, vars);
    switch (res)
    {
    case UNSATISFIABLE:
        std::cout << "Unsatisfiable" << std::endl;
        break;
    case SATISFIABLE:
        std::cout << "Satisfiable and invalid" << std::endl;
        break;
    case VALID:
        std::cout << "Valid" << std::endl;
        break;
    }
    return 0;
}