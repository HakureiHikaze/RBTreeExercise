//
// Created by guoyao.wan on 2023/8/2.
//

#pragma once
#include <stdlib.h>
#ifndef SP_INIT_SIZE
#define SP_INIT_SIZE 16
#endif
typedef struct strProducer_{
    size_t length;
    size_t capacity;
    wchar_t* buffer;
}StringProducer;
extern StringProducer* SPNewEmpty();
extern StringProducer* SPNewWStr(wchar_t* wStr);
extern StringProducer* SPNewStr(char* str);
extern StringProducer* SPCloneSP(StringProducer* sp);

extern StringProducer* SPAppendWStr(StringProducer* sp, wchar_t* wStr);
extern StringProducer* SPAppendStr(StringProducer* sp, char* str);
extern StringProducer* SPAppendWChar(StringProducer* sp, wchar_t wCh);
extern StringProducer* SPAppendChar(StringProducer* sp, char ch);
extern StringProducer* SPAppendSP(StringProducer* target, StringProducer* src);

extern StringProducer* SPInsertWStr(StringProducer* sp, size_t index, wchar_t* wStr);
extern StringProducer* SPInsertStr(StringProducer* sp, size_t index,char* str);
extern StringProducer* SPInsertWChar(StringProducer* sp, size_t index, wchar_t wCh);
extern StringProducer* SPInsertChar(StringProducer* sp, size_t index, char ch);
extern StringProducer* SPInsertSP(StringProducer* target, size_t index, StringProducer* src);

extern wchar_t* SPBuildString(StringProducer* sp);
extern wchar_t* SPGetWStringPtr(StringProducer* sp);
extern wchar_t* SPSubString(StringProducer* sp, size_t index, size_t length);

extern wchar_t SPGetCharAt(StringProducer* sp, size_t index);

extern wchar_t SPDeleteAt(StringProducer* sp, size_t index);

extern void SPRelease(StringProducer* sp);