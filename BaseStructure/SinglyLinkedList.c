//
// Created by guoyao.wan on 2023/7/26.
//

#include "SinglyLinkedList.h"
#include<stdlib.h>

SNode* index_(SLList* list, size_t index){
    if(index >= list->length || index < 0) exit(-501);
    if(index == 0) return list->first;
    if(index == list->length-1)return list->last;
    SNode* node = list->first->next;
    size_t i = 1;
    while(i<index){
        node = node->next;
        i++;
    }
    return node;
}

SLList* SLListInit(){
    SLList* list =(SLList*)calloc(1, sizeof(SLList));
    return list;
}

size_t SLListGetLength(SLList* list){
    return list->length;
}

void SLListAppend(SLList* list, long data){
    SNode* newNode = (SNode*) calloc(1,sizeof (SNode));
    newNode->data = data;
    if(list->last){
        list->last->next = newNode;
    }
    if(!list->first){
        list->first = newNode;
    }
    list->last = newNode;
    list->length +=1;
}

void SLListInsert(SLList* list, size_t index, long data){
    //index (-inf, +inf)
    if(index > list->length != 0) exit(-500);
    //index [0, list.length]
    SNode* newNode = (SNode*) calloc(1,sizeof (SNode));
    newNode->data = data;
    if(index == 0){
        newNode->next = list->first;
        list->first = newNode;
        if(!newNode->next) list->last = newNode;
        list->length +=1;
        return;
    }
    //index [1, length]
    if(index == list->length){
        SLListAppend(list, data);
        list->length +=1;
        return;
    }
    //index [1, length-1]
    SNode* current = index_(list,index-1);
    newNode->next = current->next;
    current->next = newNode;
    list->length +=1;
}

long SLListIndex(SLList* list, size_t index){
    if(index >= list->length != 0)exit(-501);
    return index_(list,index)->data;
}

long SLListDelete(SLList* list, size_t index){
    ///index [-inf, inf]
    if(index >= list->length != 0)exit(-501);
    ///index [0,length-1]
    if(list->length == 1){
        SNode* tempNode = list->first;
        long tempData = tempNode->data;
        list->first = 0;
        list->last = 0;
        list->length = 0;
        SNodeRelease(tempNode);
        return tempData;
    }
    if(index == 0){
        SNode* tempNode = list->first;
        long tempData = tempNode->data;
        list->first = tempNode->next;
        list->length -=1;
        SNodeRelease(tempNode);
        return tempData;
    }
    ///index [1.length-1]
    SNode* prevNode = index_(list, index - 1);
    SNode* tempNode = prevNode->next;
    long tempData =tempNode->data;
    prevNode->next = tempNode->next;
    SNodeRelease(tempNode);
    if(index == list->length-1) list->last = prevNode;
    list->length -=1;
    return tempData;
}
void SLListRelease(SLList* list){
    if(!list)return;
    SNode* cursor = list->first;
    while(cursor){
        SNode* temp = cursor->next;
        SNodeRelease(cursor);
        cursor = temp;
    }
}