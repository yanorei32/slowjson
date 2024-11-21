#ifndef TYPES_VALUE_H
#define TYPES_VALUE_H

#include "types_type_id.h"
#include "types_string.h"
#include "types_array.h"
#include "types_object.h"

struct Value {
	TypeId type_id;
	union {
		double number;
		String string;
		Array array;
		Object object;
	};
} typedef Value;

void value_drop(Value *self);

#endif
