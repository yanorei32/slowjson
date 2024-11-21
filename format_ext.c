#include <stdint.h>
#include <stdio.h>

#include "types_array.h"
#include "types_object.h"
#include "types_string.h"
#include "types_type_id.h"
#include "types_value.h"

void value_format(Value*, String*, int);

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

void number_format(double v, String *output, int indent) {
	for (int i = 0; i < indent; ++i)
		string_push_str(output, "  ");

	char buf[32];
	sprintf(buf, "%lf", v);
	string_push_str(output, buf);
}

void format_const_s_with_indent(const char *s, String *output, int indent) {
	for (int i = 0; i < indent; ++i)
		string_push_str(output, "  ");

	string_push_str(output, s);
}

void string_format(String *self, String *output, int indent) {
	for (int i = 0; i < indent; ++i)
		string_push_str(output, "  ");

	string_push_char(output, '"');
	string_push_string_view(output, string_as_string_view(self));
	string_push_char(output, '"');
}

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

// pub
String format_value(Value *value) {
	String s = string_new();
	value_format(value, &s, 0);
	return s;
}
