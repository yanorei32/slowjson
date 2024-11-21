#ifndef NUMBER_H
#define NUMBER_H

#include <stdio.h>
#include "panic.h"

int c2int(char c) {
	return c - '0';
}

int is_digit(char c) {
	return '0' <= c && c <= '9';
}

int fetch_integer_part(FILE *stream) {
	int v = 0;
	int c;

	while (is_digit((c = getc(stream)))) {
		v *= 10;
		v += c2int(c);
	}

	ungetc(c, stream);

	return v;
}

double fetch_fraction_part(FILE *stream) {
	double v = 0;
	double epsilon = 1;
	int c = getc(stream);

	if (c != '.') {
		ungetc(c, stream);
		return 0;
	}
	

	while (is_digit((c = getc(stream)))) {
		epsilon /= 10;
		v += c2int(c) * epsilon;
	}

	ungetc(c, stream);

	return v;
}

int fetch_is_negative(FILE *stream) {
	int c = getc(stream);

	if (c == '-') {
		return 1;
	}

	ungetc(c, stream);
	return 0;
}

int fetch_exponential_part(FILE *stream) {
	int exp = 0;
	int is_neg_exp = 0;
	int c = getc(stream);

	if (c != 'e' && c != 'E') {
		ungetc(c, stream);
		return 0;
	}

	c = getc(stream);
	switch (c) {
		case '-':
			is_neg_exp = 1;
			break;
		case '+':
			break;
		default:
			ungetc(c, stream);
	}

	exp = fetch_integer_part(stream);

	if (is_neg_exp) exp *= -1;

	return exp;
}


int abs(int v) {
	return v <= 0 ? -v : v;
}

double myexp10(int v) {
	double exp = 1.0;

	double multiplier = v < 0 ? 0.1 : 10;

	for (int i = 0; i < abs(v); ++i) {
		exp *= multiplier;
	}

	return exp;
}

double parse_number(FILE *stream) {
	double value = 0;
	int is_negative = fetch_is_negative(stream);

	value += fetch_integer_part(stream);
	value += fetch_fraction_part(stream);
	int exp = fetch_exponential_part(stream);

	if (is_negative) {
		value *= -1;
	}

	value *= myexp10(exp);

	return value;
}

#endif
