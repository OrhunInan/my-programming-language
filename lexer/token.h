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
        arithmetic_operator_token,
        assignment_operator_token,
        comparison_operator_token,
        logical_operator_token,
        bitwise_operator_token,
        misc_operator_token,
        parentheses_token,
        notation_token,
        comma_token,
        keyword_token,
        identifier_token,
        end_of_statement_token,
        unrecognized_token,
        doc_token,
    };

    const static unordered_map<int, string> reverse_enum;
    const static string keywords[];
    const static string arithmetic_operators[];
    const static string assignment_operators[];
    const static string comparison_operators[];
    const static string logical_operators[];
    const static string bitwise_operators[];
    const static string misc_operators[];


    static bool is_keyword(string& s);
    static token_type operator_type(string& s);

    string value;
    int type;

    token(string& value, token_type type) : value(value), type(type) {};

    string get_value() const { return value; };
    int get_type() const {return type;}
    string to_string() const;


    static vector<token> tokenize(string & statement, bool& is_doc);


};


#endif //MY_PROGRAMMING_LANGUAGE_TOKEN_H
