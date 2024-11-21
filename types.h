#ifndef TYPES_H
#define TYPES_H
#include <stdlib.h>
#include <stdint.h>

typedef uint32_t u32;
typedef uint32_t u16;

#include <stdlib.h>
#include <stdio.h>

enum {
	ObjectId,
	ArrayId,
	StringId,
	NumberId,
	TrueId,
	FalseId,
	NullId,
} typedef Type;

char const* type_as_str(Type t);

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

void string_format(String *self, String *output, int indent);

int string_equals(String *self, String *b);

void number_format(double v, String *output, int indent);

String format_string(String *str);

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
	Type type_id;
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
