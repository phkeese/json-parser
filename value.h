#pragma once

#include <memory>
#include <string>
#include <unordered_map>
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
	virtual ~Value(){};
	const value_type type;
};

using ValuePtr = std::shared_ptr<Value>;

struct ValueBool : public Value {
	ValueBool(bool data) : Value{V_BOOL}, data{data} {};
	bool data;
};

struct ValueString : public Value {
	ValueString(std::string data) : Value{V_STRING}, data{data} {};
	std::string data;
};

struct ValueNumber : public Value {
	ValueNumber(double data) : Value{V_NUMBER}, data{data} {};
	double data;
};

struct ValueArray : public Value {
	ValueArray(std::vector<ValuePtr> data) : Value{V_ARRAY}, data{data} {}
	std::vector<ValuePtr> data;
};

struct ValueObject : public Value {
	ValueObject(std::unordered_map<std::string, ValuePtr> data)
		: Value{V_OBJECT}, data{data} {}
	std::unordered_map<std::string, ValuePtr> data;
};

} // namespace json
