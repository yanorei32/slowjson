#ifndef VALUE_H
#define VALUE_H

#include <stdio.h>
#include <string.h>

#include "string.h"
#include "number.h"
#include "boolean.h"
#include "null.h"
#include "array_parse.h"
#include "object.h"

#include "types.h"
#include "panic.h"

Value parse_value(FILE *stream) {
	int c;

IGNORE_WHITESPACE:
	c = getc(stream);

	switch (c) {
		case '"':
			ungetc(c, stream);

			return (Value) {
				.type_id = StringId,
				.string = parse_string(stream),
			};

		case 'n':
			ungetc(c, stream);
			consume_null(stream);

			return (Value) {
				.type_id = NullId,
			};

		case 'f':
			ungetc(c, stream);
			consume_false(stream);

			return (Value) {
				.type_id = FalseId,
			};

		case 't':
			ungetc(c, stream);
			consume_true(stream);

			return (Value) {
				.type_id = TrueId,
			};

		case '-':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			ungetc(c, stream);
			return (Value) {
				.type_id = NumberId,
				.number = parse_number(stream),
			};

		case ' ':
		case '\n':
		case '\r':
		case '\t':
			goto IGNORE_WHITESPACE;

		case '[':
			ungetc(c, stream);

			return (Value) {
				.type_id = ArrayId,
				.array = parse_array(stream),
			};

		case '{':
			ungetc(c, stream);

			return (Value) {
				.type_id = ObjectId,
				.object = parse_object(stream),
			};

		default:
			panic("有効なJSON文字列ではありません");
	}
}

#endif
