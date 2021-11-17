#include "parser.h"

#include "Operations.h"

#include <vector>
#include <string>

#include <iostream>

using namespace std;
static size_t find_lowest_priority(vector<string> lexemes);

static bool check_brackets (vector<string> line) {
    int level;
    for (size_t i = 0; i < line.size(); i++) {
        if(line[i] == "(") level ++;
        if (line[i] == ")") level --;
        if (level < 0) return false;
    }
    return level == 0;
}

Expression* parse_expression(vector<string> lexemes){
    cout << lexemes.size() << endl;
    size_t lowest_index = find_lowest_priority(lexemes);
    cout << lowest_index << "\t" << lexemes[lowest_index] << endl;
    vector<string> left;
    for (size_t i = 0; i < lowest_index; i++) {
        left.push_back(lexemes[i]);
    }
    vector<string> right;
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
    string op_type = lexemes[lowest_index];
    Binary_operation* ret = new Binary_operation;
    ret -> left = parse_expression(left);
    ret -> right = parse_expression(right);
    ret -> type = op_type;
    return ret;
}

static size_t find_lowest_priority(vector<string> lexemes) {
    int lowest_priority = 1000000;
    int priority;
    char brackets_level = 0;
    size_t i = 0;
    size_t res = 0;
    for (string lex: lexemes) {
        if (lex == "(") brackets_level+=10;
        if (lex == ")") brackets_level-=10;
        if (lex == "*") {
            priority = 3 + brackets_level;
        }
        if (lex == "+") {
            priority = 2 + brackets_level;
        }
        if (lex == "->") {
            priority = 1 + brackets_level;
        }
        if (priority < lowest_priority) {
                lowest_priority = priority;
                res = i;
        }
        i++;
    }
    return res;
}