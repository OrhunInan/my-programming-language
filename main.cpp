#include <iostream>
#include <fstream>
#include "lexer/lexer.h"

int main() {

    std::ofstream out_file("../recorded_output.txt");
    std::streambuf* old_stdout_buf = std::cout.rdbuf(out_file.rdbuf());

    string file_path("D:\\test\\fake_account.js");

    lexer test_lexer{};
    test_lexer.parse_file(file_path);
    test_lexer.print_tokens();

    std::cout.rdbuf(old_stdout_buf);
    out_file.close();

    return 0;
}
