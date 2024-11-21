#ifndef TYPES_H
#define TYPES_H
#include <stdlib.h>
#include <stdint.h>

#include <stdlib.h>
#include <stdio.h>

#include "types_string.h"

enum {
	ObjectId,
	ArrayId,
	StringId,
	NumberId,
	TrueId,
	FalseId,
	NullId,
} typedef TypeId;

char const* type_as_str(TypeId t);

void number_format(double v, String *output, int indent);

void println_string(String *str);

struct Value typedef Value;

struct {
	Value *v;
	size_t length;
	size_t capacity;
} typedef Array;

void format_const_s_with_indent(const char *s, String *output, int indent);

Array array_new();
struct {
	String *k;
	size_t length;
	size_t capacity;
} typedef Keys;

Keys keys_new();

void keys_push(Keys *self, String *k);

struct {
	Keys k;
	Array v;
} typedef Object;

struct Value {
	TypeId type_id;
	union {
		double number;
		String string;
		Array array;
		Object object;
	};
} typedef Value;

void array_push(Array *self, Value *v);

Object object_new();

void object_push(Object *self, String *k, Value *v);

void value_format(Value*, String*, int);

void object_format(Object *self, String *output, int indent);

void array_format(Array *self, String *output, int indent);

String format_value(Value *value);


#endif
