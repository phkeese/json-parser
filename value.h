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
	using Ptr = std::shared_ptr<Value>;
	Value(value_type type = V_NULL) : type{type} {}
	virtual ~Value(){};
	const value_type type;
};

using ValuePtr = std::shared_ptr<Value>;

template <typename T, value_type V> struct ValueType : public Value {
	using Ptr = std::shared_ptr<ValueType>;
	ValueType(T data) : Value{V}, data{data} {}
	T data;
	operator T() { return data; }
};

using ValueBool = ValueType<bool, V_BOOL>;
using ValueString = ValueType<std::string, V_STRING>;
using ValueNumber = ValueType<double, V_NUMBER>;
using ValueArray = ValueType<std::vector<Value::Ptr>, V_ARRAY>;
using ValueObject =
	ValueType<std::unordered_map<std::string, Value::Ptr>, V_OBJECT>;

} // namespace json
