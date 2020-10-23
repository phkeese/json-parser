#include "lexer.h"

namespace json {

Lexer::Lexer(std::istream &stream) : stream{stream}, offset{0}, length{0} {}

Lexer::~Lexer() {}

Token Lexer::get_next() {
	skip_whitespace();
	int c = advance();
	switch (c)
	{
	case EOF:
		return make_token(T_EOF);
		break;
	case '{':
		return make_token(T_LBRACE);
		break;
	case '}':
		return make_token(T_RBRACE);
		break;
	case '[':
		return make_token(T_LBRACKET);
		break;
	case ']':
		return make_token(T_RBRACKET);
		break;
	case ',':
		return make_token(T_COMMA);
		break;
	case ':':
		return make_token(T_COLON);
		break;
	default:
		return make_token(T_ERROR);
		break;
	}
}

Token Lexer::make_token(token_type type) {
	Token token{type, offset, length};
	offset += length;
	length = 0;
	return token;
}

int Lexer::advance() {
	if (!stream.good()) {
		return EOF;
	}
	int next = stream.get();
	length++;
	return next;
}

int Lexer::peek() {
	if (!stream.good()) {
		return EOF;
	}
	return stream.peek();
}

// No prev yet

void Lexer::skip_whitespace() {
	while (isspace(peek())) {
		advance();
	}
	offset += length;
	length = 0;
}

} // namespace json