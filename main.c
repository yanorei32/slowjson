#include <assert.h>

#include "parser_value.h"
#include "types_value.h"
#include "types_string.h"

#include "format_ext.h"
#include "types.h"

int main() {
	Value v = parse_value(stdin);

	String s = format_value(&v);
	println_string(&s);
}
