#include "lexer.h"

namespace json {

Lexer::Lexer(std::istream &stream) : stream{stream}, offset{0}, length{0} {}

Lexer::~Lexer() {}

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
}

} // namespace json