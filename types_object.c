#include <stdint.h>

#include "types_object.h"
#include "types.h"

Object object_new() {
	return (Object) {
		.k = keys_new(),
		.v = array_new(),
	};
}

void object_push(Object *self, String *k, Value *v) {
	keys_push(&self->k, k);
	array_push(&self->v, v);
}

void object_format(Object *self, String *output, int indent) {
	for (int i = 0; i < indent; ++i)
		string_push_str(output, "  ");
	string_push_str(output, "{\n");

	for (int n = 0; n < self->k.length; n++) {
		string_format(&self->k.k[n], output, indent + 1);
		string_push_str(output, ":\n");
		value_format(&self->v.v[n], output, indent + 2);

		if (n == self->k.length - 1) {
			string_push_char(output, '\n');
		} else {
			string_push_str(output, ",\n");
		}
	}

	for (int i = 0; i < indent; ++i)
		string_push_str(output, "  ");
	string_push_char(output, '}');
}
