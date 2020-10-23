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

	ValueNumber::Ptr n_ptr = std::make_shared<ValueNumber>(n);
	ValueArray a{{}};
	a.data.push_back(n_ptr);

	ValueBool::Ptr b_ptr = std::make_shared<ValueBool>(b);
	a.data.push_back(b_ptr);

	ValueArray::Ptr a_ptr = std::make_shared<ValueArray>(a);
	ValueObject o{{}};
	o.data[s] = a_ptr;

	assert(null.type == V_NULL);

	assert(o.type == V_OBJECT);
	assert(o.data[s]->type == V_ARRAY);

	ValueArray &array = dynamic_cast<ValueArray &>(*o.data[s]);

	assert(array.data[0]->type == V_NUMBER);
	assert(array.data[1]->type == V_BOOL);

	ValueNumber &number = dynamic_cast<ValueNumber &>(*array.data[0]);
	assert(number.data == 10);

	ValueBool &my_bool = dynamic_cast<ValueBool &>(*array.data[1]);
	assert(my_bool.data == true);
}