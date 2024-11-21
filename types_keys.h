#ifndef TYPES_KEYS
#define TYPES_KEYS

#include <stdint.h>
#include "types_string.h"

struct {
	String *k;
	size_t length;
	size_t capacity;
} typedef Keys;

Keys keys_new();
void keys_push(Keys *self, String *k);
void keys_drop(Keys *self);

#endif
