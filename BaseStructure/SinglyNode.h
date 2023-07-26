//
// Created by guoyao.wan on 2023/7/26.
//
#pragma once
typedef struct singlyNode_{
    long data;
    struct singlyNode_* next;
}SNode;

extern void SNodeRelease(SNode* node);