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
	}
}