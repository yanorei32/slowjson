#include "parser_value.h"
#include "types_value.h"
#include "print_util.h"

int main() {
	Value v = parse_value(stdin);
	println_value(&v);
	value_drop(&v);
	println_value(&v);
}
