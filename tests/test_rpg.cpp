// Test the writing capabilities
#include "../parser.h"
#include <iostream>

using namespace json;

struct Player {
	std::string name;
	std::vector<std::string> items;
	std::vector<double> levels;
	bool has_key;
	operator Value::Ptr() const;
};

Player::operator json::Value::Ptr() const {
	ValueObject::data_type values{
		{"name", std::make_shared<ValueString>(name)},
		{"items", std::make_shared<ValueArray>(items)}};
}

int main() {
	Player reference{"player", {"sword", "potion"}, {1, 2, 3}, false};
	/* Best-looking:

	json j{
		{"name", name},
		{"items", items},
		{"levels", levels},
		{"has_key", has_key}
	};

	*/
}