#pragma once

#include <istream>

namespace json {
enum token_type {
	// Meta
	T_ERROR,
	T_EOF,

	// Non-data
	T_LBRACE,
	T_RBRACE,
	T_LBRACKET,
	T_RBRACKET,
	T_COMMA,
	T_COLON,

	// Data
	T_STRING,
	T_NUMBER,
	T_TRUE,
	T_FALSE,
	T_NULL,
};

struct Token {
	token_type type;
	int start, length;
};

class Lexer {
  public:
	Lexer(std::istream &stream);
	virtual ~Lexer();

	Token get_next();

  private:
	Token make_token(token_type);
	Token make_string();
	Token make_number();
	Token make_ident();
	int advance();
	int peek();
	int prev();
	void skip_whitespace();
	std::istream &stream;
	int offset, length;
};
} // namespace json