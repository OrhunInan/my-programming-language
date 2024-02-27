#ifndef MY_PROGRAMMING_LANGUAGE_TOKEN_H
#define MY_PROGRAMMING_LANGUAGE_TOKEN_H
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class token {

public:

    enum token_type{
        int_token,
        boolean_token,
        float_token,
        string_token,
        operator_token,
        keyword_token,
        identifier_token,
        end_of_statement_token,
        unrecognized_token,
    };

    const static unordered_map<int, string> reverse_enum;
    const static string keywords[];
    static bool is_keyword(string& s);

    string value;
    int type;

    token(string& value, token_type type) : value(value), type(type) {};

    string get_value() const { return value; };
    int get_type() const {return type;}
    string to_string() const;


    static vector<token> tokenize(string& statement);


};


#endif //MY_PROGRAMMING_LANGUAGE_TOKEN_H
