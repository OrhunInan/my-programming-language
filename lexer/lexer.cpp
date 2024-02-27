#include "lexer.h"
#include "token.h"
#include <fstream>
#include <sstream>
#include <iostream>

void lexer::parse_file(string& file_name) {

    ifstream file(file_name);
    string line;

    while (getline(file, line)) {

        vector<token> new_tokens = token::tokenize(line);
        new_tokens.insert(new_tokens.begin(), tokens.begin(), tokens.end());
        tokens = new_tokens;
    }

    file.close();
}

void lexer::print_tokens() {

    for (token t : tokens) {

        cout << t.to_string() << " ";

        if (t.type == token::end_of_statement_token) cout << endl;
    }
}