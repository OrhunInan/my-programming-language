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
        "export",
        "import",
        "try",
        "catch",
        "then",
        "from",
        "as",

};

const string token::arithmetic_operators[] = {
        "+",
        "-",
        "*",
        "**",
        "/",
        "%",
        "++",
        "--",
};

const string token::assignment_operators[] = {
        "=",
        "+=",
        "-=",
        "*=",
        "/=",
        "%=",
        "**=",
};

const string token::comparison_operators[] = {
        "==",
        "===",
        "!=",
        "!==",
        ">",
        "<",
        ">=",
        "<=",
        "?",
};

const string token::logical_operators[] = {
        "&&",
        "||",
        "!",
};

const string token::bitwise_operators[] = {
        "&",
        "|",
        "~",
        "^",
        "<<",
        ">>",
        ">>>",

};

const string token::misc_operators[] = {
        "=>",
        ":",
};

const unordered_map<int, string> token::reverse_enum = {
        {0, "int_token"},
        {1, "boolean_token"},
        {2, "float_token"},
        {3, "string_token"},
        {4, "arithmetic_operator_token"},
        {5, "assignment_operator_token"},
        {6, "comparison_operator_token"},
        {7, "logical_operator_token"},
        {8, "bitwise_operator_token"},
        {9, "misc_operator_token"},
        {10, "parentheses_token"},
        {11, "notation_token"},
        {12, "comma_token"},
        {13, "keyword_token"},
        {14, "identifier_token"},
        {15, "end_of_statement_token"},
        {16, "unrecognized_token"},
        {17, "doc_token"}
};

string token::to_string() const {
    return "{ \"" + value + "\", " + reverse_enum.at(type) + "}\n";
}


bool is_whitespace(char c) { return (c == ' ' || c == '\t'); }
bool is_notation(char c) { return  c == '.'; }
bool is_comma(char c) { return  c== ','; }
bool is_number(char c) { return (c >= '0' && c <= '9'); }
bool is_operator(char c) {

    return (c == '-' || c == '+' || c == '/' || c == '*' || c == '=' || c == '<' ||
        c == '>' || c == ':');
}
bool is_end_of_statement(char c) { return c == ';'; }
bool is_parentheses(char c) { return c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}'; }
bool is_misc(char c) { return !(is_operator(c) || is_notation(c) || is_comma(c) || is_parentheses(c) ||
                                is_whitespace(c) || is_end_of_statement(c));}
bool token::is_keyword(std::string &s) {

    for (const string& keyword: keywords) {

        if (s == keyword) return true;
    }
    return false;
}

token::token_type token::operator_type(std::string &s) {

    for (const string& e: arithmetic_operators) {

        if (s == e) return arithmetic_operator_token;
    }
    for (const string& e: assignment_operators) {

        if (s == e) return assignment_operator_token;
    }
    for (const string& e: comparison_operators) {

        if (s == e) return comparison_operator_token;
    }
    for (const string& e: logical_operators) {

        if (s == e) return logical_operator_token;
    }
    for (const string& e: bitwise_operators) {

        if (s == e) return bitwise_operator_token;
    }
    for (const string& e: misc_operators) {

        if (s == e) return misc_operator_token;
    }
    return unrecognized_token;
}

vector<token> token::tokenize(string& statement, bool& is_doc) {

    vector<token> output{};
    string token_val{};

    for (int i = 0; i < statement.length();) {
        token_val = "";

        if (is_doc) {
            for (; i < statement.length(); i++) {
                token_val += statement[i];

                if (statement[i] == '*' &&  i < statement.length() - 1 &&  statement[i+1] == '/') {
                    token_val += statement[++i];
                    i++;
                    is_doc = false;
                    break;
                }

            }

            output.emplace_back(token_val, doc_token);
        }
        else if (is_whitespace(statement[i])){
            i++;
        }
        else if (is_notation(statement[i])) {
            token_val += statement[i++];

            if (is_number(statement[i])) {
                for (; i < statement.length() && is_number(statement[i]); i++) {
                    token_val += statement[i];
                }

                if(!is_misc(statement[i])) {
                    output.emplace_back(token_val, float_token);
                }
                else {
                    for (; i < statement.length() && is_misc(statement[i]); i++) {
                        token_val += statement[i];
                    }

                    output.emplace_back(token_val, unrecognized_token);
                }
            }
            else {
                output.emplace_back(token_val, notation_token);
            }
        }
        else if (is_comma(statement[i])) {

            token_val += statement[i];
            output.emplace_back(token_val, comma_token);
            i++;
        }
        else if (is_number(statement[i])) {
            token_type type = int_token;

            for (; i < statement.length() && is_number(statement[i]); i++) {
                token_val += statement[i];
            }

            if(is_notation(statement[i])){
                type = float_token;

                token_val += statement[i++];

                for (; i < statement.length() && is_number(statement[i]); i++) {

                    token_val += statement[i];
                }
            }

            if(!is_misc(statement[i])) {
                output.emplace_back(token_val, type);
            }
            else {
                for (; i < statement.length() && is_misc(statement[i]); i++) {
                    token_val += statement[i];
                    output.emplace_back(token_val, unrecognized_token);
                }
            }
        }
        else if (is_parentheses(statement[i])) {
            token_val += statement[i];
            output.emplace_back(token_val, parentheses_token);
            i++;
        }
        else if (is_operator(statement[i])) {

            if (statement[i] == '/' && i < statement.length() - 1 && statement[i+1] == '*') {
                for (; i < statement.length(); i++) {
                    token_val += statement[i];

                    if (statement[i] == '*' &&  i < statement.length() - 1 &&  statement[i+1] == '/') {
                        token_val += statement[++i];
                        i++;
                        break;
                    }
                }

                output.emplace_back(token_val, doc_token);
            }
            else {
                for (; i < statement.length() && is_operator(statement[i]); i++) {
                    token_val += statement[i];
                }

                output.emplace_back(token_val, operator_type(token_val));
            }
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

                    if (statement[i] == '\\') token_val += statement[i++];
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

