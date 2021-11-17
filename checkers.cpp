#include "checkers.h"

#include <iostream>

#define printac 
//#define printac cout << ac << endl;

using namespace std;

static bool accept(char c, char** stream_pointer) {
    char* stream = *stream_pointer;
    if (*stream == c){
        *stream_pointer = ++stream;
        return true;
    }
    return false;
}

static bool inVariableAlphabet(char** stream_pointer){
    char* stream = *stream_pointer;
    bool res = (*stream >= '0' && *stream <= '9') ||
               (*stream >= 'A' && *stream <= 'Z') ||
               (*stream == '\'');
    if (res) {
        *stream_pointer = ++stream;
    }
    return res;
}

bool variable(char** stream_pointer) {
    char* stream = *stream_pointer;
    bool res = *stream >= 'A' && *stream <= 'Z';
    if (!res) return false;
    while (inVariableAlphabet(stream_pointer)) {
        stream = *stream_pointer;
        res = true;
    }
    return res;
}

bool inversion(char** stream_pointer) {
    return accept('(', stream_pointer) && expression(stream_pointer) && accept(')', stream_pointer) ||
            accept('!', stream_pointer) && inversion(stream_pointer) || variable(stream_pointer);
}

bool conunction(char** stream_pointer) {
    char* ac = *stream_pointer;
    printac
    bool r1 = (inversion(stream_pointer) && accept('&', stream_pointer) && conunction(stream_pointer));
    if (!r1) *stream_pointer = ac;
    bool r2 = inversion(stream_pointer);
    return r1 || r2;
}

bool disunction(char** stream_pointer) {
    char* ac = *stream_pointer;
    printac
    bool r1 = conunction(stream_pointer)
            && accept('|', stream_pointer) 
            && disunction(stream_pointer) ;
    if (!r1) *stream_pointer = ac;
    bool r2 = conunction(stream_pointer);
    return r1 + r2;
}

bool expression(char** stream_pointer) {
    char* ac = *stream_pointer;
    printac
    bool r1 = disunction(stream_pointer) &&
        accept('-', stream_pointer) &&
        accept('>', stream_pointer) &&
        expression(stream_pointer);
    if (!r1) *stream_pointer = ac;
    bool r2 = disunction(stream_pointer);
    return r1 || r2;
}