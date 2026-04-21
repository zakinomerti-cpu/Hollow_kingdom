#include "hashArray.h"
#include "pVoidArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stdint.h"

static int simpleHash(const char* str) {
	uint64_t hash = 5381;
	
	int c;
	while ((c = *str++)) {
		hash = hash * 33 + c;
	}

	return hash & (0x7fffffff);
}


static pVoidArray* getInnerArray(hashArray* arr, int index) {
	pVoidArray* tmp = arr->_data.ops->get(&arr->_data, index);
	if (!tmp) {
		tmp = malloc(sizeof(pVoidArray));
		pVoidArray tmpArr = pVoidArrayCreate();
		memcpy(tmp, &tmpArr, sizeof(pVoidArray));
		arr->_data.ops->set(&arr->_data, tmp, index);
	}
	return tmp;
}


static void _add(hashArray* arr, void* data, const char* name) {
	if (!data || !name) return;

	int hashIndex = simpleHash(name) % arr->elementCount;
	pVoidArray* innerArr = getInnerArray(arr, hashIndex);
	

	int strsize = strlen(name)+1;
	char* lname = malloc(strsize); 
	if(!lname) return;
	memcpy(lname, name, strsize);


	hashArrayElement* tmp = NULL;
	for(int i = 0; i < innerArr->ops->size(innerArr); i++) {
		tmp = innerArr->ops->get(innerArr, i);
		if(strcmp(tmp->name, name) == 0) {
			free(tmp->name);
			tmp->name = lname;
			tmp->data = data;
			return;
		}
	}
	
	tmp = malloc(sizeof(hashArrayElement));
	if(!tmp) {
		free(lname);
		return;
	}
	tmp->name = lname;
	tmp->data = data;
	innerArr->ops->add(innerArr, tmp);
}




static void* _get(hashArray* arr, const char* name) {
	int hashIndex = simpleHash(name) % arr->elementCount;
	pVoidArray* innerArr = getInnerArray(arr, hashIndex);
	for (int iter = 0; iter < innerArr->size; iter++) {
		hashArrayElement* tmp = (hashArrayElement*)innerArr->ops->get(innerArr, iter);
		if (strcmp(tmp->name, name) == 0) {
			return tmp->data;
		}
	}

	return NULL;
}

static char _isExist(hashArray* arr, const char* name) {
	if(arr->ops->get(arr, name) == NULL)
		return 0;
	return 1;
}

static void _forEach(struct hashArray* arr, void(*callback)(void* p, void* args), void* args) {
	if(!arr || !callback) return;

	for(int i = 0; i < arr->elementCount; i++) {
		pVoidArray* iarr = arr->_data.ops->get(&arr->_data, i);
		if(!iarr) continue;
		for(int j = 0; j < iarr->ops->size(iarr); j++) {
			hashArrayElement* e = iarr->ops->get(iarr, j);
			if(!e->data) continue;
			callback(e->data, args);
		}
	}
}

static int _size(struct hashArray* arr) {
	if(!arr) return -1;
	return arr->elementCount;
}

static const hashArrayInterface ops = {

	_add,
	_get,
	_isExist,
	_forEach,
	_size,
};

hashArray hashArrayCreate(int size) {
	hashArray arr;
	arr.elementCount = size;
	arr.ops = &ops;
	arr._data = pVoidArrayCreate();
	arr._data.ops->allocate(&arr._data, size);
	return arr;
}