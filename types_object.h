#ifndef TYPES_OBJECT
#define TYPES_OBJECT

#include "types_keys.h"
#include "types_array.h"

struct {
	Keys k;
	Array v;
} typedef Object;

Object object_new();

void object_push(Object *self, String *k, Value *v);

#endif
