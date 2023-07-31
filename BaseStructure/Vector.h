#pragma once
#define INIT_MAX_CAPACITY 16
typedef struct Vector_{
    size_t capacity;
    size_t size;
    void** data;
}Vector;

extern Vector* VectorCreate();
extern void VectorRelease(Vector*);
extern size_t GetLength(Vector*);
extern size_t GetCapacity(Vector*);
extern void VectorAppend(Vector*, void*);
extern void VectorInsertAt(Vector*, void*, size_t);
extern void* VectorDelete(Vector*,size_t);
extern void* VectorAtIndex(Vector*,size_t);
extern size_t VectorFindFirst(Vector*,void*);