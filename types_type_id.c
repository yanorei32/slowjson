#include "types_type_id.h"

char const* type_as_str(TypeId t) {
	switch (t) {
		case NumberId:
			return "Number";
		case StringId:
			return "String";
		case NullId:
			return "Null";
		case FalseId:
			return "False";
		case TrueId:
			return "True";
		case ArrayId:
			return "Array";
		case ObjectId:
			return "Object";
	}
}
