#pragma once

#include "value.h"
#include <ostream>

namespace json {

std::ostream &operator<<(std::ostream &os, const Value &value);
std::ostream &operator<<(std::ostream &os, const ValueNumber &value);
std::ostream &operator<<(std::ostream &os, const ValueBool &value);
std::ostream &operator<<(std::ostream &os, const ValueString &value);
std::ostream &operator<<(std::ostream &os, const ValueArray &value);
std::ostream &operator<<(std::ostream &os, const ValueObject &value);

} // namespace json