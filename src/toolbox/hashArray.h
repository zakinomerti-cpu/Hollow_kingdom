#ifndef hashArray_header
#define hashArray_header

#include "pVoidArray.h"

struct hashArray;

typedef struct hashArrayElement {
	char* name;
	void* data;
} hashArrayElement;

typedef struct {
	void (*add)(struct hashArray*, void*, const char*);
	void* (*get)(struct hashArray*, const char*);
	char (*isExist)(struct hashArray*, const char*);
	void (*forEach)(struct hashArray* arr, void(*callback)(void* p, void* args), void* args);
	int (*size)(struct hashArray*);
} hashArrayInterface;

typedef struct hashArray {
	//public
	int elementCount;
	const hashArrayInterface* ops;

	//private
	pVoidArray _data;
} hashArray;

hashArray hashArrayCreate(int);

#endif