#include "types.h"
#include "parser_value.h"

// おやくそく: 最初に '[' がある状態できてね
Array parse_array(FILE *stream) {
	int c;

	Array a = array_new();

	// drop '['
	getc(stream);

	while (1) {
		c = getc(stream);

		if (c == ']') {
			break;
		}

		// parse_valueは自動的に終了するから ',' は読み飛ばせばよい
		if (c == ',') {
			continue;
		}

		ungetc(c, stream);

		Value v = parse_value(stream);
		array_push(&a, &v);
	}

	return a;
}
