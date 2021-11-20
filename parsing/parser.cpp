#include "parser.h"

#include "Operations.h"

#include <vector>
#include <string>
#include <set>

static size_t find_lowest_priority(std::vector<std::string> lexemes);

std::set<Variable*> variables_set;
std::set<std::string> variables_names_set;

static bool check_brackets (std::vector<std::string> line) {
    int level = 0;
    for (size_t i = 0; i < line.size(); i++) {
        if(line[i] == "(") level ++;
        if (line[i] == ")") level --;
        if (level < 0) return false;
    }
    return level == 0;
}

Expression* parse_expression(std::vector<std::string> lexemes){
    if (lexemes.size() == 1) {
        Variable* ret = NULL;
        if (variables_names_set.insert(lexemes[0]).second) {
            ret = new Variable(false, lexemes[0]);
            variables_set.insert(ret);
        }
        else {
            for (Variable* v : variables_set) {
                if (v -> get_name() == lexemes[0]) {
                    ret = v;
                }
            }
        }
        return ret;
    }
    size_t lowest_index = find_lowest_priority(lexemes);
    std::vector<std::string> left;
    for (size_t i = 0; i < lowest_index; i++) {
        left.push_back(lexemes[i]);
    }
    std::vector<std::string> right;
    for (size_t i = lowest_index + 1; i < lexemes.size(); i++) {
        right.push_back(lexemes[i]);
    }
    if (!check_brackets(left)) {
        left.erase(left.begin());
    }
    if (!check_brackets(right)) {
        right.erase(right.end());
    }
    if (lexemes[lowest_index] == "!") {
        Inversion* ret = new Inversion;
        ret -> operand = parse_expression(right);
        return ret;
    }
    std::string op_type = lexemes[lowest_index];
    Binary_operation* ret = new Binary_operation;
    ret -> left = parse_expression(left);
    ret -> right = parse_expression(right);
    ret -> type = op_type;
    return ret;
}

static size_t find_lowest_priority(std::vector<std::string> lexemes) {
    int lowest_priority = 1000000;
    int priority;
    char brackets_level = 0;
    size_t i = 0;
    size_t res = 0;
    for (std::string lex: lexemes) {
        if (lex == "("){
            brackets_level+=10;
            i++;
            continue;
        }
        if (lex == ")") {
            brackets_level-=10;
            i++;
            continue;
        }
        if (lex == "!") {
            priority = 4 + brackets_level;
        }
        else if (lex == "&") {
            priority = 3 + brackets_level;
        }
        else if (lex == "|") {
            priority = 2 + brackets_level;
        }
        else if (lex == "->") {
            priority = 1 + brackets_level;
        }
        else {
            i++;
            continue;
        }
        if (priority <= lowest_priority) {
                lowest_priority = priority;
                res = i;
        }
        i++;
    }
    return res;
}

std::set<Variable *>* get_variables_set() {
    return &variables_set;
}