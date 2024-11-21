#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include "types_object.h"

// おやくそく: 最初に '[' がある状態できてね
Object parse_object(FILE *stream);

#endif
