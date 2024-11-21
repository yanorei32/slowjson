#include <stdio.h>
#include "types_string.h"

void println_string(String *str) {
	puts(string_as_c_str(str));
}
