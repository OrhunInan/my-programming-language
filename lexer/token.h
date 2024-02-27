#ifndef MY_PROGRAMMING_LANGUAGE_TOKEN_H
#define MY_PROGRAMMING_LANGUAGE_TOKEN_H
#include <string>

using namespace std;

class token {

public:

    string value;
    int type;

    token(string& value, int type) : value(value), type(type) {};

    string get_value() const { return value; };
    int get_type() const {return type;}

    enum token_types{
        int_token,
        char_token,
        boolean_token,
        float_token,
        string_token,
        operator_token,
        parentheses_token,
        keyword_token,
        identifier_token,
        punctuation_token,
        end_of_statement_token,
    };
};


#endif //MY_PROGRAMMING_LANGUAGE_TOKEN_H
