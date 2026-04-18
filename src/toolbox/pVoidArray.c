#include "pVoidArray.h"
#include <stdlib.h>

static void _add(pVoidArray* arr, void* element) {
	void** tmp;
	if(arr->size >= arr->capacity) {
		arr->capacity = (arr->capacity == 0) ? 2 :
			arr->capacity * 2;
		tmp = realloc(arr->data, arr->capacity * sizeof(void*));
		if(!tmp) return;
		arr->data = tmp;
	}
	
	arr->data[arr->size] = element;
	arr->size += 1;
}

static void* _get(pVoidArray* arr, int index) {
	if(index < 0 || index >= arr->size)
		return NULL;
	return arr->data[index];
}

static void* _last(pVoidArray* arr) {
	return arr->data[arr->size-1];
}

static int _size(pVoidArray* arr) {
	return arr->size;
}

static const pVoidArrayInterface ops = {
	_get,
	_last,
	_add,
	_size
};

pVoidArray pVoidArrayCreate() {
	pVoidArray arr = {0};
	arr.size = 0;
	arr.capacity = 0;
	arr.data = NULL;
	arr.ops = &ops;
	return arr;
}

void pVoidArrayDelete(pVoidArray** arr) {
	free((*arr)->data);
	(*arr) = NULL;
}