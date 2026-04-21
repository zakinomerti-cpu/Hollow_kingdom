#ifndef pVoidArray_header
#define pVoidArray_header

struct pVoidArray;

typedef struct {
	void* (*get)(struct pVoidArray*, int index);
	void* (*last)(struct pVoidArray*);
	void (*add)(struct pVoidArray*, void* data);
	int (*size)(struct pVoidArray*);

	void (*allocate)(struct pVoidArray*, int size); // аллоцирует память с последнего элемента
	void (*set)(struct pVoidArray* arr, void* data, int index);
} pVoidArrayInterface;

typedef struct pVoidArray {
	int size;
	int capacity;
	void** data;
	const pVoidArrayInterface* ops;
} pVoidArray;

pVoidArray pVoidArrayCreate();
void pVoidArrayDelete(pVoidArray** arr);

#endif