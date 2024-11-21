#include <malloc.h>
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

void array_drop(Array *self) {
	for (int i = 0; i < self->length; ++i) {
		value_drop(&self->v[i]);
	}

	free(self->v);

	self->capacity = 0;
	self->length = 0;
}
