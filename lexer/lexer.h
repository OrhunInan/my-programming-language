#ifndef MY_PROGRAMMING_LANGUAGE_LEXER_H
#define MY_PROGRAMMING_LANGUAGE_LEXER_H

#include <vector>
#include <hash_map>
#include "token.h"

using namespace std;

class lexer {

public:

    lexer() = default;

    vector<token> tokens;

    void parse_file(string& file_name);
    void print_tokens();
};


#endif //MY_PROGRAMMING_LANGUAGE_LEXER_H
