#pragma once
#include<stdlib.h>
typedef struct RBTNode_{
    size_t data;
    int color;
    struct RBTNode_* parent,* lChild,* rChild;
}RBTNode;
extern void PrintRBTNode(RBTNode*);
extern RBTNode* CreateRBTNode();