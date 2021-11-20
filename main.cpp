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
    std::cout << without_spaces << std::endl;
    std::vector<std::string> lexemes;
    get_lexemes(without_spaces, &lexemes);
    // for (size_t i = 0; i < lexemes.size(); i++) {
    //     cout << lexemes[i];
    // }
    std::cout << std::endl;
    Expression* tree = parse_expression(lexemes);
    print_tree(tree);
    std::cout << tree -> evaluate() << std::endl;
    std::set<Variable*>* vars = get_variables_set();
    std::cout << vars -> size() << std::endl;
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