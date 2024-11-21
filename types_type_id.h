#ifndef TYPES_TYPE_ID
#define TYPES_TYPE_ID

enum {
	ObjectId,
	ArrayId,
	StringId,
	NumberId,
	TrueId,
	FalseId,
	NullId,
} typedef TypeId;

char const* type_id_as_str(TypeId t);

#endif
