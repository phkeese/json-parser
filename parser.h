#pragma once

#include "lexer.h"
#include "value.h"

namespace json {

class Parser {
  public:
	Parser(std::istream &stream);
	virtual ~Parser();

	Value::Ptr parse();
	Token get_token() const;

  private:
	ValueObject::Ptr parse_object();
	ValueArray::Ptr parse_array();
	Value::Ptr parse_literal();
	inline Token advance() { return prev; };
	bool consume(token_type type);
	std::string get_literal(Token &token);

	Lexer lexer;
	Token prev, peek;
};

} // namespace json