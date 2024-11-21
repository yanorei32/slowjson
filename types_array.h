#ifndef TYPES_ARRAY
#define TYPES_ARRAY

#include <stdlib.h>
#include "types_string.h"

struct Value typedef Value;

struct {
	Value *v;
	size_t length;
	size_t capacity;
} typedef Array;

Array array_new();

void array_push(Array *self, Value *v);
void array_format(Array *self, String *output, int indent);

#endif

