#include "writer.h"

namespace json {

std::ostream &operator<<(std::ostream &os, const Value &value) {
	switch (value.type) {
	case V_NULL:
		return os << "null";
		break;
	case V_NUMBER:
		return operator<<(os, dynamic_cast<const ValueNumber &>(value));
		break;
	case V_BOOL:
		return operator<<(os, dynamic_cast<const ValueBool &>(value));
		break;
	case V_STRING:
		return operator<<(os, dynamic_cast<const ValueString &>(value));
		break;
	case V_ARRAY:
		return operator<<(os, dynamic_cast<const ValueArray &>(value));
		break;
	case V_OBJECT:
		return operator<<(os, dynamic_cast<const ValueObject &>(value));
		break;
	default:
		return os << "error";
		break;
	}
}

std::ostream &operator<<(std::ostream &os, const ValueNumber &value) {
	return os << value.data;
}

std::ostream &operator<<(std::ostream &os, const ValueBool &value) {
	return os << value.data;
}

std::ostream &operator<<(std::ostream &os, const ValueString &value) {
	return os << '"' << value.data << '"';
}

std::ostream &operator<<(std::ostream &os, const ValueArray &value) {
	os << "[";
	// First value
	if (value.data.begin() != value.data.end()) {
		os << *value.data.begin();
	}
	// All others
	for (auto it = value.data.begin() + 1; it != value.data.end(); it++) {
		os << "," << *it;
	}
	return os << "]";
}

std::ostream &operator<<(std::ostream &os, const ValueObject &value) {
	os << "{";
	// First value
	auto it = value.data.begin();
	if (it != value.data.end()) {
		const auto pair = *it++;
		os << pair.first << ":" << pair.second;
	}
	// All others
	for (; it != value.data.end(); it++) {
		const auto pair = *it;
		os << "," << pair.first << ":" << pair.second;
	}
	return os << "}";
}
} // namespace json
