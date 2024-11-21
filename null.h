#ifndef NULL_H
#define NULL_H

#include "types.h"
#include "panic.h"

void consume_null(FILE *stream) {
	if (getc(stream) != 'n') panic("Expected 'n'");
	if (getc(stream) != 'u') panic("Expected 'u'");
	if (getc(stream) != 'l') panic("Expected 'l'");
	if (getc(stream) != 'l') panic("Expected 'l'");
}

#endif

