//
// Created by guoyao.wan on 2023/7/26.
//

#pragma once
#include "SinglyNode.h"
#include<stdlib.h>
typedef struct singlyLinkedList_{
    SNode* first;
    SNode* last;
    size_t length;
}SLList;

/// Initialize a new SLList.
/// \first  NULL
/// \last   NULL
/// \length 0
/// \return ptr of SLList
extern SLList* SLListInit();
/// Get length of SLList
/// \param list ptrList
/// \return length of SLList
extern size_t SLListGetLength(SLList* list);
/// Add a new data after the tail
/// \param list
/// \param data
extern void SLListAppend(SLList* list, long data);
extern void SLListInsert(SLList* list, size_t index, long data);
extern long SLListIndex(SLList* list, size_t index);
extern long SLListDelete(SLList* list, size_t index);
extern void SLListRelease(SLList* list);