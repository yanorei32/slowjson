#ifndef PANIC_H
#define PANIC_H

#include <stdio.h>
#include <stdlib.h>

[[noreturn]] void panic(const char* s) {
	fprintf(stderr, "%s\n", s);
	exit(1);
}

#endif
