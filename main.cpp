#include "preprocessing/preprocessor.h"
#include "parsing/parser.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    string input;
    getline(cin, input);
    char* without_spaces = remove_spaces(input.data());
    cout << without_spaces << endl;
    vector<string> lexemes;
    get_lexemes(without_spaces, &lexemes);
    parse_expression(lexemes);
    return 0;
}