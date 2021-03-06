#include "preprocessor.h"

#include <cstring>
#include <stdint.h>
#include <string>


bool inVariableAlphabet(char c) {
    return (c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c == '\'');
}

char* remove_spaces(const char* line) {
    const char* ptr = line;
    size_t new_size = 0;
    while (*ptr != 0) {
        if(*ptr != ' ' && *ptr != '\t' && *ptr != '\r') {
            new_size ++;
        }
        ptr++;
    }
    char* new_line = new char[new_size + 1];
    ptr = line;
    char* new_ptr = new_line;
    while (*ptr != 0) {
        if(*ptr != ' ' && *ptr != '\t' && *ptr != '\r') {
            *new_ptr = *ptr;
            new_ptr++;
        }
        ptr++;
    }
    *new_ptr = 0;
    return new_line;
}

void get_lexemes(const char * line, std::vector<std::string>* lexemes){
    const char* ptr = line;
    while (*ptr != 0){
        if (*ptr == '(' || *ptr == ')' || *ptr == '!' || *ptr == '|' || *ptr == '&') {
            std::string a = std::string(1, *ptr);
            lexemes->push_back(a);
        }
        if (*ptr == '-') {
            ptr++;
            if (*ptr == '>') {
                lexemes->push_back("->");
            }
        }
        if (inVariableAlphabet(*ptr)) {
            std::string a = "";
            std::string b;
            while (inVariableAlphabet(*ptr)) {
                b = std::string(1, *ptr);
                a.append(b);
                ptr++;
            }
            lexemes->push_back(a);
            if (*ptr == 0) break;
            ptr--;
        }
        ptr++;
    }
}
