cmake_minimum_required(VERSION 3.17)

project(json-parser)

set(CMAKE_CXX_STANDARD 11)

add_library(json_parser lexer.cpp)