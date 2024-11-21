#include <stdlib.h>

#include "types_string.h"

String string_new() {
	return (String) {
		.s = (char*) 0,
		.length = 0,
		.capacity = 0,
	};
}

void string_push_char(String *self, char c) {
	self->length ++;
	if (self->length > self->capacity) {
		self->capacity = self->capacity ? self->capacity * 2 : 16;
		self->s = (char*) realloc(self->s, self->capacity * sizeof(char));
	}

	self->s[self->length - 1] = c;
}

void string_push_str(String *self, char const* c) {
	while (*c) {
		string_push_char(self, *c++);
	}
}

void string_push_utf8_char(String *self, u32 codepoint) {
	const char length_signature_2 = 0xc0;
	const char length_signature_3 = 0xe0;
	const char length_signature_4 = 0xf0;
	const char non_ascii_signature = 0x80;
	const char mask_6bit = 0x3f;
	char buffer[5] = {};

	if (codepoint <= 0x7f) {
		string_push_char(self, codepoint);

	} else if (codepoint <= 0x7FF) {
		buffer[2] = 0;
		buffer[1] = non_ascii_signature | (codepoint & mask_6bit);
		codepoint >>= 6;
		buffer[0] = length_signature_2 | codepoint;
		
		string_push_str(self, buffer);
	} else if (codepoint <= 0xFFFF) {
		buffer[3] = 0;
		buffer[2] = non_ascii_signature | (codepoint & mask_6bit);
		codepoint >>= 6;
		buffer[1] = non_ascii_signature | (codepoint & mask_6bit);
		codepoint >>= 6;
		buffer[0] = length_signature_3 | codepoint;
		
		string_push_str(self, buffer);
	} else {
		buffer[4] = 0;
		buffer[3] = non_ascii_signature | (codepoint & mask_6bit);
		codepoint >>= 6;
		buffer[2] = non_ascii_signature | (codepoint & mask_6bit);
		codepoint >>= 6;
		buffer[1] = non_ascii_signature | (codepoint & mask_6bit);
		codepoint >>= 6;
		buffer[0] = length_signature_4 | codepoint;
		
		string_push_str(self, buffer);
	}
}

void string_push_string_view(String *self, StringView view) {
	for (size_t i = 0; i < view.len; ++i) {
		string_push_char(self, *view.p++);
	}
}

StringView string_as_string_view(String *self) {
	return (StringView) {
		.p = self->s,
		.len = self->length,
	};
}

void string_drop(String *self) {
	free(self->s);
	self->capacity = 0;
}

char* string_as_c_str(String *self) {
	string_push_char(self, '\0');
	self->length --;
	return self->s;
}

void string_format(String *self, String *output, int indent) {
	for (int i = 0; i < indent; ++i)
		string_push_str(output, "  ");

	string_push_char(output, '"');
	string_push_string_view(output, string_as_string_view(self));
	string_push_char(output, '"');
}

int string_equals(String *self, String *b) {
	if (self->length != b->length) return 0;

	for (int i = 0; i < self->length; ++i)
		if (self->s[i] != b->s[i]) return 0;

	return 1;
}

String format_string(String *str) {
	String s = string_new();
	string_format(str, &s, 0);
	return s;
}
