#include "types_array.h"
#include "types_value.h"

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
