#include <stdio.h>
#include "types_string.h"
#include "format_ext.h"

void println_string(String *str) {
	puts(string_as_c_str(str));
}

void println_value(Value *v) {
	String s = format_value(v);
	println_string(&s);
	string_drop(&s);
}
