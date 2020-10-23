#include "../value.h"
#include <cassert>
#include <iostream>

using namespace json;

int main() {
	/*
		Construct an object with the followign structure:
		{
			"my key" : [10, true]
		}
	*/

	Value null{};
	ValueBool b{true};
	ValueString s{"my key"};
	ValueNumber n{10};

	ValuePtr n_ptr = std::make_shared<ValueNumber>(n);
	ValueArray a{{}};
	a.data.push_back(n_ptr);

	ValuePtr b_ptr = std::make_shared<ValueBool>(b);
	a.data.push_back(b_ptr);

	ValuePtr a_ptr = std::make_shared<ValueArray>(a);
	ValueObject o{{}};
	o.data[s.data] = a_ptr;

	assert(null.type == V_NULL);

	assert(o.type == V_OBJECT);
	assert(o.data[s.data]->type == V_ARRAY);

	ValuePtr array_ptr = o.data[s.data];
	ValueArray &array = dynamic_cast<ValueArray &>(*array_ptr);

	assert(array.data[0]->type == V_NUMBER);
	assert(array.data[1]->type == V_BOOL);

	ValueNumber &number = dynamic_cast<ValueNumber &>(*array.data[0]);
	assert(number.data == 10);

	ValueBool &my_bool = dynamic_cast<ValueBool &>(*array.data[1]);
}