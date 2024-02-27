#include <iostream>
#include "lexer/lexer.h"

int main() {

    string file_path("D:/test/fake_account.js");

    lexer test_lexer{};
    test_lexer.parse_file(file_path);

    return 0;
}
