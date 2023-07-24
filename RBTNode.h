#pragma once
typedef struct RBTNode_{
    int data;
    int color;
    struct RBTNode_* parent,* lChild,* rChild;
}RBTNode;
extern void PrintRBTNode(RBTNode*);
extern RBTNode* CreateRBTNode();