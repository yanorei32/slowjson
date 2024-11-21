#include <stdio.h>
#include <string.h>

#include "types.h"
#include "panic.h"

u32 c2u32(char c) {
	switch (c) {
		case '0'...'9': return c - '0';
		case 'a'...'z': return c - 'a' + 10;
		case 'A'...'Z': return c - 'A' + 10;
		default: panic("\\uのエスケープシーケンス内に謎の文字が来た");
	}
}

// おやくそく: 最初の "\u" がない状態で来てね。
u16 fetch_u16(FILE *stream) {
	u16 n = 0;
	n |= c2u32(getc(stream)) << 12;
	n |= c2u32(getc(stream)) << 8;
	n |= c2u32(getc(stream)) << 4;
	n |= c2u32(getc(stream)) << 0;
	return n;
}

int is_surrogate_first_byte(u16 v) {
	return v >> 10 == 0b110110;
}

int is_surrogate_last_byte(u16 v) {
	return v >> 10 == 0b110111;
}

u32 combine_surrogate(u16 first, u16 last) {
	u32 ret = first & 0b1111111111;
	ret <<= 10;
	ret |= last & 0b1111111111;
	ret += 0x10000;

	return ret;
}

// おやくそく: 最初の '\' がない状態で来てね。
void fetch_escaped(String *self, FILE *stream) {
	const char *from = "\"\\/bfnrt";
	const char *to = "\"\\/\b\f\n\r\t";

	int c = getc(stream);
	const char *pos = strchr(from, c);

	if (pos) {
		string_push_char(self, to[pos - from]);
		return;
	}

	if (c == 'u') {
		u32 codepoint = 0;
		u16 first_utf16 = fetch_u16(stream);

		if (is_surrogate_first_byte(first_utf16)) {
			if (!(getc(stream) == '\\' && getc(stream) == 'u')) {
				panic("完了しないサロゲートペアが来た");
			}

			u16 last_utf16 = fetch_u16(stream);

			if (!is_surrogate_last_byte(last_utf16)) {
				panic("完了しないサロゲートペアが来た");
			}

			codepoint = combine_surrogate(first_utf16, last_utf16);

		} else if (is_surrogate_last_byte(first_utf16)) {
			panic("始まってないサロゲートペアが来た");

		} else {
			codepoint = first_utf16;
		}

		string_push_utf8_char(self, codepoint);
	}
}

String parse_string(FILE *stream) {
	int c;
	String s = string_new();

	// Drop first '"'
	getc(stream);
	
	while ((c = getc(stream)) != EOF) {
		if (c == '"') {
			return s;
		}

		if (c == '\\') {
			fetch_escaped(&s, stream);
			continue;
		}

		string_push_char(&s, c);
	}

	panic("\"が来ませんでした。");
}
