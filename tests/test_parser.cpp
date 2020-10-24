#include "../parser.h"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace json;

int main() {
	// Empty object
	{
		std::stringstream stream;
		stream << "{}";
		Parser parser{stream};
		Value::Ptr value = parser.parse();
		assert(value);
		assert(value->type == V_OBJECT);
	}

	// Simple object
	{
		std::stringstream stream;
		stream << "{\"key\" : null}";
		Parser parser{stream};
		Value::Ptr value = parser.parse();
		assert(value);
		assert(value->type == V_OBJECT);

		ValueObject &object = dynamic_cast<ValueObject &>(*value);
		assert(object.data.find("key") != object.data.end());

		Value::Ptr null_value = object.data["key"];
		assert(null_value);
		assert(null_value->type == V_NULL);
	}

	// Complex object
	{
		std::stringstream stream;
		stream << "{\"key\" : [1.0,true,null,false,\"string\"]}";
		Parser parser{stream};
		Value::Ptr value = parser.parse();

		assert(value);
		assert(value->type == V_OBJECT);

		ValueObject &object = dynamic_cast<ValueObject &>(*value);
		ValueObject::data_type &data = object.data;

		assert(data["key"]->type == V_ARRAY);
		ValueArray &array = dynamic_cast<ValueArray &>(*data["key"]);

		assert(array.data.size() == 5);
		assert(array.data[0]->type == V_NUMBER);
		assert(array.data[1]->type == V_BOOL);
		assert(array.data[2]->type == V_NULL);
		assert(array.data[3]->type == V_BOOL);
		assert(array.data[4]->type == V_STRING);

		ValueNumber &number = dynamic_cast<ValueNumber &>(*array.data[0]);
		ValueBool &bool_true = dynamic_cast<ValueBool &>(*array.data[1]);
		ValueBool &bool_false = dynamic_cast<ValueBool &>(*array.data[3]);
		ValueString &string = dynamic_cast<ValueString &>(*array.data[4]);

		assert(number.data == 1.0);
		assert(bool_true.data == true);
		assert(bool_false.data == false);
		assert(string.data == "string");
	}

	// String
	{
		std::stringstream stream{};
		stream << "\"This is a string\"";
		Parser parser{stream};
		Value::Ptr value = parser.parse();

		assert(value);
		assert(value->type == V_STRING);

		ValueString &string = dynamic_cast<ValueString &>(*value);
		assert(string.data == "This is a string");
	}

	// Number
	{
		std::stringstream stream{};
		stream << "100.0";
		Parser parser{stream};
		Value::Ptr value = parser.parse();

		assert(value);
		assert(value->type == V_NUMBER);

		ValueNumber &number = dynamic_cast<ValueNumber &>(*value);
		assert(number.data == 100.0);
	}

	// Bool
	{
		std::stringstream stream{};
		stream << "true";
		Parser parser{stream};
		Value::Ptr value = parser.parse();

		assert(value);
		assert(value->type == V_BOOL);

		ValueBool &boolean = dynamic_cast<ValueBool &>(*value);
		assert(boolean.data == true);
	}

	// Null
	{
		std::stringstream stream{};
		stream << "null";
		Parser parser{stream};
		Value::Ptr value = parser.parse();

		assert(value);
		assert(value->type == V_NULL);
	}

	// Multiple values after each other
	{
		std::stringstream stream{};
		stream << "1 \"\" true";
		Parser parser{stream};

		Value::Ptr first = parser.parse();
		assert(first);
		assert(first->type == V_NUMBER);
		assert(dynamic_cast<ValueNumber &>(*first).data == 1);

		Value::Ptr second = parser.parse();
		assert(second);
		assert(second->type == V_STRING);
		assert(dynamic_cast<ValueString &>(*second).data == "");

		Value::Ptr third = parser.parse();
		assert(third);
		assert(third->type == V_BOOL);
		assert(dynamic_cast<ValueBool &>(*third).data == true);
	}
}