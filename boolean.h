#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "types.h"
#include "panic.h"

void consume_false(FILE *stream) {
	if (getc(stream) != 'f') panic("Expected 'f'");
	if (getc(stream) != 'a') panic("Expected 'a'");
	if (getc(stream) != 'l') panic("Expected 'l'");
	if (getc(stream) != 's') panic("Expected 's'");
	if (getc(stream) != 'e') panic("Expected 'e'");
}

void consume_true(FILE *stream) {
	if (getc(stream) != 't') panic("Expected 't'");
	if (getc(stream) != 'r') panic("Expected 'r'");
	if (getc(stream) != 'u') panic("Expected 'u'");
	if (getc(stream) != 'e') panic("Expected 'e'");
}

#endif
