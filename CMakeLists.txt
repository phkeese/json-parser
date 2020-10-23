cmake_minimum_required(VERSION 3.17)

project(json-parser)

set(CMAKE_CXX_STANDARD 11)

add_library(json_parser lexer.cpp)

include(CTest)
enable_testing()

add_executable(test_lexer tests/test_lexer.cpp)
target_link_libraries(test_lexer json_parser)
add_test(lexer test_lexer)