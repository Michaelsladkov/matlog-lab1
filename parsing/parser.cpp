#include "parser.h"

#include "Operations.cpp"

#include <vector>
#include <string>

#include <iostream>

using namespace std;
static size_t find_lowest_priority(vector<string> lexemes);

Expression* parse_expression(vector<string> lexemes){
    size_t lowest_index = find_lowest_priority(lexemes);
    cout << lowest_index << "\t" << lexemes[lowest_index] << endl;
    return 0;
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