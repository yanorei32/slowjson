#include <assert.h>

#include "types.h"
#include "value.h"

int main() {
	/* String s = string_new(); */
	/* string_push_str(&s, "Hello, "); */
	/* string_push_str(&s, "World!"); */
    /*  */
	/* println_string(&s); */

	/* String s = parse_string(stdin); */
	/* println_string(&s); */


	/* string_as_c_str() */

	// string_push_utf8_char(&s, 0x1f4a9);

	/* String formatted = format_string(&s); */

	Value v = parse_value(stdin);

	String s = format_value(&v);
	println_string(&s);
}
