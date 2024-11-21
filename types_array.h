#ifndef TYPES_ARRAY
#define TYPES_ARRAY

#include <stdlib.h>

struct Value typedef Value;

struct {
	Value *v;
	size_t length;
	size_t capacity;
} typedef Array;

Array array_new();

void array_push(Array *self, Value *v);
void array_drop(Array *self);

#endif
