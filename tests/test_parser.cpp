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
		stream << "{\"key\" : [1,true,null,false]}";
		Parser parser{stream};
		Value::Ptr value = parser.parse();
		assert(value);
		assert(value->type == V_OBJECT);
	}
}