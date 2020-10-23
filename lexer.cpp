#include "lexer.h"

namespace json {

Lexer::Lexer(std::istream &stream) : stream{stream}, offset{0}, length{0} {}

Lexer::~Lexer() {}

Token Lexer::get_next() {
	skip_whitespace();
	int c = advance();
	switch (c) {
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
	case '"':
		return make_string();
		break;
	default:
		if (isnumber(c)) {
			return make_number();
		} else if (isalpha(c)) {
			return make_ident(c);
		}
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

// Finish rest of string until (including) "
Token Lexer::make_string() {
	int c;
	// Until we reach the end, only escape "
	while ((c = advance()) != '"') {
		if (c == '\\') {
			advance();
		}
		// EOF in string is error
		if (c == EOF) {
			return make_token(T_ERROR);
		}
	}
	return make_token(T_STRING);
}

// Finish rest of number until non-number
Token Lexer::make_number() {
	// First part of number
	while (isnumber(peek())) {
		advance();
	}

	// If not a decimal point, return just the first part
	if (peek() != '.') {
		return make_token(T_NUMBER);
	}

	// Consume decimal
	advance();

	// Next one has to be number
	if (!isnumber(peek())) {
		return make_token(T_ERROR);
	}

	// Second part of number
	while (isnumber(peek())) {
		advance();
	}

	return make_token(T_NUMBER);
}

// Match an identifier with true, false, null
Token Lexer::make_ident(char start) {
	switch (start) {
	case 't':
		if (match("rue")) {
			return make_token(T_TRUE);
		}
		return make_token(T_ERROR);
		break;
	case 'n':
		if (match("ull")) {
			return make_token(T_NULL);
		}
		return make_token(T_ERROR);
		break;
	case 'f':
		if (match("alse")) {
			return make_token(T_FALSE);
		}
		return make_token(T_ERROR);
		break;
	default:
		return make_token(T_ERROR);
		break;
	}
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

// Match the rest of a literal with a string
bool Lexer::match(std::string rest) {
	for (int i = 0; i < rest.length(); i++) {
		if (advance() != rest.at(i)) {
			return false;
		}
	}
	return true;
}

void Lexer::skip_whitespace() {
	while (isspace(peek())) {
		advance();
	}
	offset += length;
	length = 0;
}

} // namespace json