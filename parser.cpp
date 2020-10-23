#include "parser.h"
#include <sstream>

namespace json {
Parser::Parser(std::istream &stream)
	: stream{stream}, lexer{stream}, prev{T_EOF, -1, 0}, peek{T_EOF, -1, 0} {
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
	// No data
	if (consume(T_RBRACE)) {
		return std::make_shared<ValueObject>(data);
	}

	// Need at least one key : value pair
	if (!parse_key_value(data)) {
		return nullptr;
	}

	// If at end
	if (consume(T_RBRACE)) {
		return std::make_shared<ValueObject>(data);
	}

	// Require at least one more key : value pair
	do {
		// Require comma after key : value
		if (!consume(T_COMMA)) {
			return nullptr;
		}

		if (!parse_key_value(data)) {
			return nullptr;
		}
	} while (peek.type != T_RBRACE);

	// Closing brace
	consume(T_RBRACE);
	return std::make_shared<ValueObject>(data);
}

// Parse one key : value pair
bool Parser::parse_key_value(ValueObject::data_type &data) {
	// Require string key
	if (!consume(T_STRING)) {
		return false;
	}
	std::string key_literal = get_literal(prev);
	std::string key = key_literal.substr(1, key_literal.length() - 2);
	// Require key : value
	if (!consume(T_COLON)) {
		return false;
	}
	Value::Ptr value = parse();
	data[key] = value;
	return true;
}

// Finish parsing an array
ValueArray::Ptr Parser::parse_array() {
	ValueArray::data_type data{};

	// No data
	if (peek.type == T_RBRACKET) {
		return std::make_shared<ValueArray>(data);
	}

	// At least one data
	{
		Value::Ptr value = parse();
		if (!value) {
			return nullptr;
		}
	}

	// Parse rest of data
	while (peek.type == T_COMMA) {
		consume(T_COMMA);
		Value::Ptr value = parse();
		if (!value) {
			return nullptr;
		}
		data.push_back(value);
	}
	// Closing bracket
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

Token Parser::advance() {
	prev = peek;
	peek = lexer.get_next();
	return prev;
}

bool Parser::consume(token_type type) {
	if (peek.type == type) {
		advance();
		return true;
	}
	return false;
}

std::string Parser::get_literal(Token &token) {
	auto prev_offset = stream.tellg();

	// Extract relevent part of stream
	stream.seekg(token.start);
	std::stringstream ss{};
	for (int i = 0; i < token.length; i++) {
		int c = stream.get();
		if (c == EOF) {
			break;
		}
		ss << char(c);
	}
	// Do not disturb lexer
	stream.seekg(prev_offset);

	return ss.str();
}

} // namespace json