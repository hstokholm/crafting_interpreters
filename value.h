#ifndef VALUE_H
#define VALUE_H

#include <cstdint>

#include "array.h"
#include "common.h"

using Value = double;
using ValueArray = Array<Value>;

void print_value(const Value& value);

#endif /* VALUE_H */