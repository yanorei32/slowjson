#include <stdlib.h>
#include "types_keys.h"
#include "types_string.h"

Keys keys_new() {
	return (Keys) {
		.k = (String*) 0,
		.length = 0,
		.capacity = 0,
	};
}

void keys_push(Keys *self, String *k) {
	self->length ++;
	if (self->length > self->capacity) {
		self->capacity = self->capacity ? self->capacity * 2 : 16;
		self->k = (String *) realloc(self->k, self->capacity * sizeof(String));
	}

	self->k[self->length - 1] = *k;
}

void keys_drop(Keys *self) {
	for (int i = 0; i < self->length; ++i) {
		string_drop(&self->k[i]);
	}

	free(self->k);

	self->capacity = 0;
	self->length = 0;
}
