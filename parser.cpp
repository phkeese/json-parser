#include "parser.h"

namespace json {
Parser::Parser(std::istream &stream)
	: lexer{stream}, prev{T_EOF, -1, 0}, peek{T_EOF, -1, 0} {
	// "Prime the pump"
	peek = lexer.get_next();
}

Parser::~Parser() {}

Value::Ptr Parser::parse() {
	Token token = advance();
	switch (token.type) {
	case T_LBRACE:
		return parse_object();
		break;
	case T_LBRACKET:
		return parse_array();
		break;
	default:
		return parse_literal();
		break;
	}
}

Value::Ptr Parser::parse_literal() {
	switch (prev.type) {
	case T_NULL:
		return std::make_shared<Value>();
		break;
	case T_NUMBER: {
		double value = std::stod(get_literal(prev));
		return std::make_shared<ValueNumber>(value);
	} break;
	case T_TRUE: {
		return std::make_shared<ValueBool>(true);
	} break;
	case T_FALSE:
		return std::make_shared<ValueBool>(false);
		break;
	case T_STRING: {
		std::string literal = get_literal(prev);
		return std::make_shared<ValueString>(
			literal.substr(1, literal.length() - 2));
	} break;
	default:
		return nullptr;
		break;
	}
}
} // namespace json