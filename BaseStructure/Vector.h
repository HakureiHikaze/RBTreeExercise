#pragma once
typedef struct Vector_{
    size_t capacity;
    size_t size;
    void** data;
}Vector;
extern void VectorAppend(Vector*, void*);
extern void* VectorDelete(Vector*,size_t);
extern void* VectorAtIndex(Vector*,size_t);
extern size_t VectorFindFirst(Vector*,void*);