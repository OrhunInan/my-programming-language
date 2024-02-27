#include "token.h"

const string token::keywords[] = {
        "int",
        "char",
        "bool",
        "float",
        "string",
        "void",
        "const",
        "async",
        "await",
        "long",
};

const unordered_map<int, string> token::reverse_enum = {
        {0, "int_token"},
        {1, "boolean_token"},
        {2, "float_token"},
        {3, "string_token"},
        {4, "operator_token"},
        {5, "keyword_token"},
        {6, "identifier_token"},
        {7, "end_of_statement_token"},
        {8, "unrecognized_token"}
};

string token::to_string() const {
    return "{ \"" + value + "\", " + reverse_enum.at(type) + "}";
}

bool is_whitespace(char c) { return (c == ' ' || c == '\t'); }
bool is_number(char c) { return (c >= '0' && c <= '9'); }
bool is_operator(char c) {

    return (c == '-' || c == '+' || c == '/' || c == '*' || c == '=' || c == '<' ||
        c == '>' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == '.' || c == ',');
}
bool is_end_of_statement(char c) { return c == ';'; }
bool is_misc(char c) { return !(is_operator(c) || is_whitespace(c) || is_end_of_statement(c));}
bool token::is_keyword(std::string &s) {

    for (const string& keyword: keywords) {

        if (s == keyword) return true;
    }
    return false;
}

vector<token> token::tokenize(string& statement) {

    vector<token> output{};
    string token_val{};

    for (int i = 0; i < statement.length();) {
        token_val = "";
        if (is_whitespace(statement[i])){
            i++;
        }
        else if (is_number(statement[i])) {

            for (; i < statement.length() && is_number(statement[i]); i++) {

                token_val += statement[i];
            }

            if(!is_misc(statement[i])) {

                output.emplace_back(token_val, int_token);
            }
            else {

                for (; i < statement.length() && !(is_misc(statement[i])); i++) {

                    token_val += statement[i];
                    output.emplace_back(token_val, unrecognized_token);
                }
            }
        }
        else if (is_operator(statement[i])) {

            token_val += statement[i];
            output.emplace_back(token_val, operator_token);
            i++;
        }
        else if (is_end_of_statement(statement[i])){

            token_val += statement[i];
            output.emplace_back(token_val, end_of_statement_token);
            i++;
        }
        else {

            if (statement[i] == '\"' || statement[i] == '\''){
                i++;

                for (; i < statement.length() && statement[i] != '\"' && statement[i] != '\''; i++) {

                    token_val += statement[i];
                }

                i++;

                output.emplace_back(token_val, string_token);
            }
            else {

                for (; i < statement.length() && is_misc(statement[i]); i++) {

                    token_val += statement[i];
                }

                if (is_keyword(token_val)) {

                    output.emplace_back(token_val, keyword_token);
                }
                else {

                    output.emplace_back(token_val, identifier_token);
                }
            }
        }
    }


    return output;
}

