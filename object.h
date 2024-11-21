#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>

#include "string.h"
#include "types.h"
#include "panic.h"

Value parse_value(FILE *stream);

void consume_whitespaces(FILE *stream) {
	int c;

OBJECT_IGNORE_WHITESPACE:
	c = getc(stream);

	switch (c) {
		case ' ':
		case '\n':
		case '\r':
		case '\t':
			goto OBJECT_IGNORE_WHITESPACE;

		default:
			ungetc(c, stream);
			return;
	}
}

void consume_colon(FILE *stream) {
	int c;

OBJECT_IGNORE_WHITESPACE:
	c = getc(stream);

	switch (c) {
		case ':':
			return;
		default:
			panic("Object内に謎の文字");
	}
}

// おやくそく: 最初に '[' がある状態できてね
Object parse_object(FILE *stream) {
	int c;

	Object o = object_new();

	// drop '{'
	getc(stream);

	while (1) {
		consume_whitespaces(stream);

		c = getc(stream);

		if (c == '}') {
			break;
		}

		// 無視する
		if (c == ',') {
			continue;
		}

		ungetc(c, stream);

		Value k = parse_value(stream);

		if (k.type_id != StringId) {
			panic("KeyがStringじゃないよー");
		}

		consume_whitespaces(stream);
		consume_colon(stream);

		Value v = parse_value(stream);
		object_push(&o, &k.string, &v);

		consume_whitespaces(stream);
	}

	return o;
}

#endif
