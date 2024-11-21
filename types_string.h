#ifndef TYPES_STRING
#define TYPES_STRING

#include <stdlib.h>
#include "types_rustlike.h"

struct {
	char* s;
	size_t length;
	size_t capacity;
} typedef String;

struct {
	char* p;
	size_t len;
} typedef StringView;

String string_new();

void string_push_char(String *self, char c);

void string_push_str(String *self, char const* c);

void string_push_utf8_char(String *self, u32 codepoint);

void string_push_string_view(String *self, StringView view);

StringView string_as_string_view(String *self);

void string_drop(String *self);

char* string_as_c_str(String *self);

int string_equals(String *self, String *b);

#endif
