//
// Created by guoyao.wan on 2023/8/2.
//

#include "StringProducer.h"
size_t getWStrLength_(const wchar_t* wStr){
    size_t i = 0;
    for(;wStr[i] != L'\0';i++);
    return i;
}

size_t getStrLength_(const char* str){
    size_t i = 0;
    for(;str[i] != '\0';i++);
    return i;
}

wchar_t* wStrClone_(wchar_t* target, const wchar_t* src){
    for(size_t i =0; src[i] != L'\0'; i++){
        target[i] = src[i];
    }
    return target;
}

wchar_t* strCloneIntoWStr_(wchar_t* target, const char* src){
    for(size_t i =0; src[i] != '\0'; i++){
        target[i] = (wchar_t)src[i];
    }
    return target;
}

StringProducer* spExtend_(StringProducer* sp){
    wchar_t* strTemp = sp->buffer;
    size_t newCapacity = sp->capacity*2;
    sp->buffer = (wchar_t*) calloc(newCapacity, sizeof(wchar_t));
    if(!sp->buffer) exit(-201);
    wStrClone_(sp->buffer, strTemp);
    free(strTemp);
    sp->capacity = newCapacity;
    return sp;
}

StringProducer* spPartialMove_(StringProducer* sp, size_t start, size_t offset){
    if(start >= sp->length) exit(-501);
    size_t length = sp->length - start;
    while(sp->length + offset >= sp->capacity -1){
        spExtend_(sp);
    }
    wchar_t* temp = (wchar_t*) calloc(length, sizeof(wchar_t));
    for(size_t i = 0; i < length; i++){
        temp[i] = sp->buffer[start + i];
        sp->buffer[start + i] = 0;
    }
    for(size_t i = 0; i < length; i++){
        sp->buffer[i + start + offset] = temp[i];
    }
    free(temp);
    return sp;
}
StringProducer* spPushLeft_(StringProducer* sp, size_t start, size_t offset){
    size_t length = sp->length - start;
    for(size_t i = 0; i< length; i++){
        sp->buffer[start-offset+i] = sp->buffer[start + i];
    }
    return sp;
}

StringProducer* SPNewEmpty(){
    StringProducer* sp = (StringProducer*) calloc(1, sizeof(StringProducer));
    sp->buffer = (wchar_t*) calloc(SP_INIT_SIZE, sizeof(wchar_t));
    sp->capacity = SP_INIT_SIZE;
    return sp;
}

StringProducer* SPNewWStr(wchar_t* wStr){
    StringProducer* sp = (StringProducer*) calloc(1, sizeof(StringProducer));
    sp->buffer = (wchar_t*) calloc(SP_INIT_SIZE, sizeof(wchar_t));
    sp->capacity = SP_INIT_SIZE;
    size_t length = getWStrLength_(wStr);
    while(length >= sp->capacity-1){
        spExtend_(sp);
    }
    sp->length = length;
    wStrClone_(sp->buffer, wStr);
    return sp;
}

StringProducer* SPNewStr(char* str){
    StringProducer* sp = (StringProducer*) calloc(1, sizeof(StringProducer));
    sp->buffer = (wchar_t*) calloc(SP_INIT_SIZE, sizeof(wchar_t));
    sp->capacity = SP_INIT_SIZE;
    size_t length = getStrLength_(str);
    while(length >= sp->capacity-1){
        spExtend_(sp);
    }
    sp->length = length;
    strCloneIntoWStr_(sp->buffer, str);
    return sp;
}

StringProducer* SPCloneSP(StringProducer* sp){
    StringProducer* temp = (StringProducer*) calloc(1, sizeof(StringProducer));
    temp->buffer = (wchar_t*) calloc(sp->capacity, sizeof(wchar_t));
    wStrClone_(temp->buffer, sp->buffer);
    temp->capacity = sp->capacity;
    temp->length = sp->length;
    return temp;
}

StringProducer* SPAppendWStr(StringProducer* sp, wchar_t* wStr){
    size_t length = getWStrLength_(wStr);
    while(sp->length + length >= sp->capacity-1){
        spExtend_(sp);
    }
    for(size_t i = sp->length, j = 0; wStr[j] != L'\0';)
    {
        sp->buffer[i] = wStr[j];
        i++;j++;
    }
    sp->length += length;
    sp->buffer[sp->length] = L'\0';
    return sp;
}
StringProducer* SPAppendStr(StringProducer* sp, char* str){
    size_t length = getStrLength_(str);
    while(sp->length + length >= sp->capacity-1){
        spExtend_(sp);
    }
    for(size_t i = sp->length, j = 0; str[j] != '\0';)
    {
        sp->buffer[i] = (wchar_t)str[j];
        i++;j++;
    }
    sp->buffer[sp->length] = L'\0';
    return sp;
}
StringProducer* SPAppendWChar(StringProducer* sp, wchar_t wCh){
    if(sp->length >= sp->capacity -2){
        spExtend_(sp);
    }
    sp->buffer[sp->length] = wCh;
    sp->length++;
    sp->buffer[sp->length] = L'\0';
    return sp;
}
StringProducer* SPAppendChar(StringProducer* sp, char ch){
    if(sp->length >= sp->capacity -2){
        spExtend_(sp);
    }
    sp->buffer[sp->length] = (wchar_t)ch;
    sp->length++;
    sp->buffer[sp->length] = '\0';
    return sp;
}
StringProducer* SPAppendSP(StringProducer* target, StringProducer* src){
    size_t length = src->length;
    while(target->length + length >= target->capacity-1){
        spExtend_(target);
    }
    for(size_t i = target->length, j = 0; src->buffer[j] != L'\0';)
    {
        target->buffer[i] = src->buffer[j];
        i++;j++;
    }
    target->length += length;
    target->buffer[target->length] = L'\0';
    return target;
}
StringProducer* SPInsertWStr(StringProducer* sp, size_t index, wchar_t* wStr){
    size_t length = getWStrLength_(wStr);
    spPartialMove_(sp,index, length);
    for(size_t i = 0; i< length; i++){
        sp->buffer[index + i] = wStr[i];
    }
    sp->length += length;
    return sp;
}
StringProducer* SPInsertStr(StringProducer* sp, size_t index,char* str){
    size_t length = getStrLength_(str);
    spPartialMove_(sp,index, length);
    for(size_t i = 0; i< length; i++){
        sp->buffer[index + i] = (wchar_t)str[i];
    }
    sp->length += length;
    return sp;
}
StringProducer* SPInsertWChar(StringProducer* sp, size_t index, wchar_t wCh){
    spPartialMove_(sp,index, 1);
    sp->buffer[index] = wCh;
    sp->length++;
    return sp;
}
StringProducer* SPInsertChar(StringProducer* sp, size_t index, char ch){
    spPartialMove_(sp,index, 1);
    sp->buffer[index] = (wchar_t)ch;
    sp->length++;
    return sp;
}
StringProducer* SPInsertSP(StringProducer* target, size_t index, StringProducer* src){
    size_t length = src->length;
    spPartialMove_(target,index, length);
    for(size_t i = 0; i< length; i++){
        target->buffer[index + i] = src->buffer[i];
    }
    target->length+= src->length;
    return target;
}
wchar_t* SPBuildString(StringProducer* sp){
    wchar_t* temp = (wchar_t*) calloc(sp->length, sizeof(wchar_t));
    wStrClone_(temp, sp->buffer);
    return temp;
}
wchar_t* SPGetWStringPtr(StringProducer* sp){
    return sp->buffer;
}
wchar_t* SPSubString(StringProducer* sp, size_t index, size_t length){
    wchar_t* temp = (wchar_t*) calloc(length, sizeof(wchar_t));
    for(size_t i = 0; i<length; i++){
        temp[i] = sp->buffer[index + i];
    }
    return temp;
}
wchar_t SPGetCharAt(StringProducer* sp, size_t index){
    return sp->buffer[index];
}
wchar_t SPDeleteAt(StringProducer* sp, size_t index){
    wchar_t temp = sp->buffer[index];
    spPushLeft_(sp,index+1, 1);
    sp->length--;
    sp->buffer[sp->length] = L'\0';
    return temp;
}
void SPRelease(StringProducer* sp){
    if(sp->buffer)free(sp->buffer);
    free(sp);
}