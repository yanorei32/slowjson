#include <malloc.h>
#include "types_type_id.h"
#include "types_value.h"
#include "types_array.h"
#include "types_string.h"

void value_drop(Value *self) {
	switch (self->type_id) {
		case ObjectId:
			object_drop(&self->object);
			break;

		case ArrayId:
			array_drop(&self->array);
			break;

		case StringId:
			string_drop(&self->string);
			break;

		case NumberId:
		case TrueId:
		case FalseId:
		case NullId:
			break;
	}

	self->type_id = NullId;
}
