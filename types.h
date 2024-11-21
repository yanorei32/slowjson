#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>

#include "types_string.h"
#include "types_value.h"

void number_format(double v, String *output, int indent);

void println_string(String *str);

void format_const_s_with_indent(const char *s, String *output, int indent);

void value_format(Value*, String*, int);
String format_value(Value *value);

#endif
