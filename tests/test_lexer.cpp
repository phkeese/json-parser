#include "../lexer.h"
#include <array>
#include <cassert>
#include <iostream>
#include <sstream>

bool operator==(const json::Token &a, const json::Token &b) {
	return a.type == b.type && a.length == b.length && a.start == b.start;
}

std::ostream &operator<<(std::ostream &os, const json::Token &t) {
	return os << "{t=" << t.type << ", s=" << t.start << ", l=" << t.length
			  << "}";
}

int main() {
	std::stringstream stream;
	stream << "{}[]  ,:  \"Test\\\"\"123.455 5true false null";
	json::Lexer lex{stream};

	const std::array<json::Token, 13> expect{{
		json::T_LBRACE,	  0,  1, // {
		json::T_RBRACE,	  1,  1, // }
		json::T_LBRACKET, 2,  1, // [
		json::T_RBRACKET, 3,  1, // ]
		json::T_COMMA,	  6,  1, // ,
		json::T_COLON,	  7,  1, // :
		json::T_STRING,	  10, 8, // "Test\"""
		json::T_NUMBER,	  18, 7, // 123.455
		json::T_NUMBER,	  26, 1, // 5
		json::T_TRUE,	  27, 4, // true
		json::T_FALSE,	  32, 5, // false,
		json::T_NULL,	  38, 4, // null
		json::T_EOF,	  42, 0	 // EOF
	}};

	for (auto e : expect) {
		json::Token t = lex.get_next();
		if (!(t == e)) {
			std::cerr << "expect " << e << ", got " << t << "\n";
			exit(EXIT_FAILURE);
		}
	}
}