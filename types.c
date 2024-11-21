#include <stdint.h>
#include <stdio.h>

#include "types.h"


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

void value_format(Value*, String*, int);

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
