#include <stdlib.h>
#include "Vector.h"
Vector* VectorCreate(){
    Vector* vector = (Vector*) calloc(1, sizeof(Vector ));
    vector->data = (void**)calloc(INIT_MAX_CAPACITY, sizeof (void*));
    vector->capacity =  INIT_MAX_CAPACITY;
    vector->size = 0;
    return vector;
}
void VectorRelease(Vector* vector){
    if(vector){
        if(vector->data) free(vector->data);
        free(vector);
    }
}
size_t GetLength(Vector* vector){
    if(!vector)exit(-901);
    return vector->size;
}
size_t GetCapacity(Vector* vector){
    if(!vector)exit(-901);
    return vector->capacity;
}

void vec_extend_(Vector * vector){
    void** newArray;
    if(vector->size >= 0xffffffff>>1){
        vector->capacity = 0xffffffff;
        newArray = (void**)calloc(0xffffffff, sizeof (void*));
        if(!newArray) exit(-999);
    }else{
        newArray = (void**)calloc(vector->capacity*2, sizeof(void*));
        if(!newArray) exit(-999);
    }
    vector->capacity*=2;
    for(size_t i = 0; i< vector->size; i++){
        newArray[i] = vector->data[i];
    }
    vector->data = newArray;
}

void VectorAppend(Vector* vector, void* data){
    if(!vector)exit(-901);
    if(vector->size >= vector->capacity-1){
        vec_extend_(vector);
    }
    vector->data[vector->size] = data;
    vector->size+=1;
}

void VectorInsertAt(Vector* vector, void* data, size_t index){
    if(!vector)exit(-901);
    if(index> vector->size) exit(-501);
    if(vector->size >= vector->capacity-1){
        vec_extend_(vector);
    }
    for(size_t i = index; i<vector->size; i++){
        vector->data[i+1] = vector->data[i];
    }
    vector->data[index] = data;
}

void* VectorDelete(Vector* vector,size_t index){
    if(!vector)exit(-901);
    if(index>= vector->size) exit(-501);
    void* temp = vector->data[index];
    for(size_t i = index; i<vector->size-1;i++){
        vector->data[i] = vector->data[i+1];
    }
    vector->data[vector->size-1] = 0;
    vector->size-=1;
    return temp;
}
void* VectorAtIndex(Vector* vector,size_t index){
    if(!vector)exit(-901);
    if(index>= vector->size) exit(-501);
    return vector->data[index];
}
size_t VectorFindFirst(Vector* vector,void* data){
    if(!vector)exit(-901);
    for(size_t i = 0; i< vector->size;i++){
        if(vector->data[i] == data)return i;
    }
    exit(-502);
}