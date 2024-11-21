#include "types_array.h"
#include "types.h"

Array array_new() {
	return (Array) {
		.v = (Value*) 0,
		.length = 0,
		.capacity = 0,
	};
}

void array_push(Array *self, Value *v) {
	self->length ++;
	if (self->length > self->capacity) {
		self->capacity = self->capacity ? self->capacity * 2 : 16;
		self->v = (Value*) realloc(self->v, self->capacity * sizeof(Value));
	}

	self->v[self->length - 1] = *v;
}

void array_format(Array *self, String *output, int indent) {
	for (int i = 0; i < indent; ++i)
		string_push_str(output, "  ");
	string_push_str(output, "[\n");

	for (int n = 0; n < self->length; n++) {
		value_format(&self->v[n], output, indent + 1);
		if (n == self->length - 1) {
			string_push_char(output, '\n');
		} else {
			string_push_str(output, ",\n");
		}
	}

	for (int i = 0; i < indent; ++i)
		string_push_str(output, "  ");
	string_push_char(output, ']');
}
