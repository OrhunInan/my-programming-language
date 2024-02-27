cmake_minimum_required(VERSION 3.26)
project(my_programming_language)

set(CMAKE_CXX_STANDARD 17)

add_executable(my_programming_language main.cpp
        lexer/lexer.cpp
        lexer/lexer.h
        lexer/token.cpp
        lexer/token.h
)
