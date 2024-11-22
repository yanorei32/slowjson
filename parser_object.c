#include <stdio.h>

#include "types_object.h"
#include "types_value.h"
#include "parser_value.h"
#include "parser_whitespaces.h"
#include "panic.h"

void consume_colon(FILE *stream) {
	if (getc(stream) == ':') return;
	panic("Object内に謎の文字");
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

		// parse_valueは自動的に終了するから ',' は読み飛ばせばよい
		if (c == ',') {
			continue;
		}

		ungetc(c, stream);

		Value k = parse_value(stream);

		if (k.type_id != StringId) {
			panic("KeyがStringじゃないよー");
		}

		consume_colon(stream);

		Value v = parse_value(stream);
		object_push(&o, &k.string, &v);
	}

	return o;
}
