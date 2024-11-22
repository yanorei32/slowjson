#include <stdio.h>

void consume_whitespaces(FILE *stream) {
	int c;

WHITESPACE_LOOP:
	c = getc(stream);

	switch (c) {
		case ' ':
		case '\n':
		case '\r':
		case '\t':
			goto WHITESPACE_LOOP;

		default:
			ungetc(c, stream);
			return;
	}
}
