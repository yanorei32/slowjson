#ifndef VALUE_H
#define VALUE_H

#include <stdio.h>

#include "parser_boolean.h"
#include "parser_null.h"
#include "parser_string.h"
#include "parser_object.h"
#include "parser_number.h"
#include "parser_array.h"
#include "parser_whitespaces.h"

#include "types_type_id.h"
#include "types_value.h"

#include "panic.h"

Value parse_value(FILE *stream) {
	consume_whitespaces(stream);
	int c = getc(stream);

	switch (c) {
		case '"':
			ungetc(c, stream);
			String s = parse_string(stream);
			consume_whitespaces(stream);

			return (Value) {
				.type_id = StringId,
				.string = s,
			};

		case 'n':
			ungetc(c, stream);
			consume_null(stream);
			consume_whitespaces(stream);

			return (Value) {
				.type_id = NullId,
			};

		case 'f':
			ungetc(c, stream);
			consume_false(stream);
			consume_whitespaces(stream);

			return (Value) {
				.type_id = FalseId,
			};

		case 't':
			ungetc(c, stream);
			consume_true(stream);
			consume_whitespaces(stream);

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
			double number = parse_number(stream);
			consume_whitespaces(stream);

			return (Value) {
				.type_id = NumberId,
				.number = number,
			};

		case '[':
			ungetc(c, stream);
			Array array = parse_array(stream);
			consume_whitespaces(stream);

			return (Value) {
				.type_id = ArrayId,
				.array = array,
			};

		case '{':
			ungetc(c, stream);
			Object object = parse_object(stream);
			consume_whitespaces(stream);

			return (Value) {
				.type_id = ObjectId,
				.object = object,
			};

		default:
			panic("有効なJSON文字列ではありません");
	}
}

#endif
