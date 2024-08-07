#include "lexer.h"
#include "token.h"
#include <fstream>
#include <iostream>

void lexer::parse_file(string& file_name) {

    ifstream file(file_name);
    string line;
    bool is_doc = false;

    while (getline(file, line)) {

        if (!tokens.empty() && tokens[tokens.size() -1].type == token::doc_token) is_doc = true;

        vector<token> new_tokens = token::tokenize(line, is_doc);

        new_tokens.insert(new_tokens.begin(), tokens.begin(), tokens.end());
        tokens = new_tokens;
    }

    file.close();
}

void lexer::print_tokens() {

    for (token& t : tokens) {

        cout << t.to_string();

        if (t.type == token::end_of_statement_token) cout << endl;
    }
}