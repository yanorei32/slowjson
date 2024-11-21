#include "types_object.h"
#include "types_string.h"
#include "types_value.h"

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
