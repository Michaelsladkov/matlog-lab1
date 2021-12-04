#include "parser.h"

#include "Operations.h"

#include <vector>
#include <string>
#include <map>

static size_t find_lowest_priority(std::vector<std::string> lexemes);

std::map<std::string, Variable*> variables = {};

static bool check_brackets (std::vector<std::string> line) {
    int level = 0;
    for (size_t i = 0; i < line.size(); i++) {
        if(line[i] == "(") level ++;
        if (line[i] == ")") level --;
        if (level < 0) return false;
    }
    return level == 0;
}

static std::vector<std::string> eliminate_extra_brackets(std::vector<std::string> lex) {
    if (lex[0] != "(") return lex;
    std::vector<std::string> new_vector = lex;
    new_vector.erase(new_vector.begin());
    new_vector.erase(new_vector.end());
    if (check_brackets(new_vector)) return eliminate_extra_brackets(new_vector);
    else return lex;
}

Expression* parse_expression(std::vector<std::string> lexemes) {
    lexemes = eliminate_extra_brackets(lexemes);
    if (lexemes.size() == 1) {
        Variable* ret = NULL;
        if (!variables.count(lexemes[0])) {
            ret = new Variable(false, lexemes[0]);
            variables[lexemes[0]] = ret;
        }
        else {
            ret = variables[lexemes[0]];
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
    /* TODO:
    * Учесть разную ассоциативность операторов
    */
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
        if (priority < lowest_priority) {
            lowest_priority = priority;
            res = i;
        }
        if (priority == lowest_priority) {
            if (lex != "->" && lex != "!") {
                lowest_priority = priority;
                res = i;
            }
        }
        i++;
    }
    return res;
}

std::map<std::string, Variable*>* get_variables() {
    return &variables;
}