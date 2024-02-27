#include "lexer.h"
#include <fstream>
#include <sstream>
#include <iostream>

const string lexer::keywords[] = {
"int",
"char",
"bool",
"float",
"string",
"void",
"const",
"async",
"await",
};

void lexer::parse_file(string& file_name) {

    ifstream file(file_name);
    string line;

    while (getline(file, line)) parse_line(line);

    file.close();
}

void lexer::parse_line(std::string &line) {

    stringstream split_string(line);
    string statement;

    while(split_string >> statement) tokenize(statement);
}

void lexer::tokenize(std::string &statement) {


}