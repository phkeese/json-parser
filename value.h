#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace json {

enum value_type {
	V_NULL,
	V_OBJECT,
	V_ARRAY,
	V_NUMBER,
	V_STRING,
	V_BOOL,
};

struct Value {
	Value(value_type type = V_NULL) : type{type} {}
	virtual ~Value();
	const value_type type;
};

using ValuePtr = std::shared_ptr<Value>;

namespace {
template <typename T, value_type type> struct ValueType : public Value {
	ValueType(T data) : Value{type}, data{data} {};
	T data;
};
} // namespace

using ValueNumber = ValueType<double, V_NUMBER>;
using ValueString = ValueType<std::string, V_STRING>;
using ValueBool = ValueType<bool, V_BOOL>;
using ValueArray = ValueType<std::vector<ValuePtr>, V_ARRAY>;
using ValueObject = ValueType<std::map<ValueString, ValuePtr>, V_OBJECT>;

} // namespace json
