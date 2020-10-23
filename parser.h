#pragma once

#include "lexer.h"
#include "value.h"

namespace json {

class Parser {
  public:
	Parser(std::istream &stream);
	virtual ~Parser();

	Value::Ptr parse();
	inline Token get_token() const { return prev; };

  private:
	ValueObject::Ptr parse_object();
	bool parse_key_value(ValueObject::data_type &data);
	ValueArray::Ptr parse_array();
	Value::Ptr parse_literal();
	Token advance();
	bool consume(token_type type);
	std::string get_literal(Token &token);

	std::istream &stream;
	Lexer lexer;
	Token prev, peek;
};

} // namespace json