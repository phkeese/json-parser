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

// Finish parsing an object
ValueObject::Ptr Parser::parse_object() {
	ValueObject::data_type data{};
	while (peek.type != T_RBRACE) {
		// Require string key
		if (!consume(T_STRING)) {
			return nullptr;
		}
		std::string key_literal = get_literal(prev);
		std::string key = key_literal.substr(1, key_literal.length() - 2);
		// Require key : value
		if (!consume(T_COLON)) {
			return nullptr;
		}
		Value::Ptr value = parse();
		data[key] = value;

		// Require comma after key : value
		if (!consume(T_COMMA)) {
			return nullptr;
		}
	}
	// Closing brace
	consume(T_RBRACE);
	return std::make_shared<ValueObject>(data);
}

// Finish parsing an array
ValueArray::Ptr Parser::parse_array() {
	ValueArray::data_type data{};
	while (peek.type != T_RBRACKET) {
		Value::Ptr value = parse();
		data.push_back(value);
		// Require comma between values
		if (!consume(T_COMMA)) {
			return nullptr;
		}
	}
	// All closing bracket
	if (!consume(T_RBRACKET)) {
		return nullptr;
	}
	return std::make_shared<ValueArray>(data);
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