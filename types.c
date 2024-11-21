#include <stdlib.h>
#include <stdint.h>

#include <stdlib.h>
#include <stdio.h>

#include "types.h"

char const* type_as_str(TypeId t) {
	switch (t) {
		case NumberId:
			return "Number";
		case StringId:
			return "String";
		case NullId:
			return "Null";
		case FalseId:
			return "False";
		case TrueId:
			return "True";
		case ArrayId:
			return "Array";
		case ObjectId:
			return "Object";
	}
}


void number_format(double v, String *output, int indent) {
	for (int i = 0; i < indent; ++i)
		string_push_str(output, "  ");

	char buf[32];
	sprintf(buf, "%lf", v);
	string_push_str(output, buf);
}


void println_string(String *str) {
	puts(string_as_c_str(str));
}

void format_const_s_with_indent(const char *s, String *output, int indent) {
	for (int i = 0; i < indent; ++i)
		string_push_str(output, "  ");

	string_push_str(output, s);
}

Array array_new() {
	return (Array) {
		.v = (Value*) 0,
		.length = 0,
		.capacity = 0,
	};
}

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

void array_push(Array *self, Value *v) {
	self->length ++;
	if (self->length > self->capacity) {
		self->capacity = self->capacity ? self->capacity * 2 : 16;
		self->v = (Value*) realloc(self->v, self->capacity * sizeof(Value));
	}

	self->v[self->length - 1] = *v;
}

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

void value_format(Value*, String*, int);

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

void array_format(Array *self, String *output, int indent) {
	for (int i = 0; i < indent; ++i)
		string_push_str(output, "  ");
	string_push_str(output, "[\n");

	for (int n = 0; n < self->length; n++) {
		value_format(&self->v[n], output, indent + 1);
		if (n == self->length - 1) {
			string_push_char(output, '\n');
		} else {
			string_push_str(output, ",\n");
		}
	}

	for (int i = 0; i < indent; ++i)
		string_push_str(output, "  ");
	string_push_char(output, ']');
}

void value_format(Value *value, String *output, int indent) {
	switch (value->type_id) {
		case NumberId: number_format(value->number, output, indent + 0); return;
		case StringId: string_format(&value->string, output, indent + 0); return;
		case NullId: format_const_s_with_indent("Null", output, indent + 0); return;
		case FalseId: format_const_s_with_indent("False", output, indent + 0); return;
		case TrueId: format_const_s_with_indent("True", output, indent + 0); return;
		case ArrayId: array_format(&value->array, output, indent + 0); return;
		case ObjectId: object_format(&value->object, output, indent + 0); return;
	}
}

String format_value(Value *value) {
	String s = string_new();
	value_format(value, &s, 0);
	return s;
}
