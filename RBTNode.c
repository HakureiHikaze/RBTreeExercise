#pragma once
#include "RBTNode.h"
#include <stdio.h>
#include <stdlib.h>
void PrintRBTNode(RBTNode* node){
    printf("\nAddr:\t0x%p\nData:\t%d\nColor:\t%d\nParent:\t0x%p\nLeft:\t0x%p\nRight:\t0x%p\n",
           node,
           node->data,
           node->color,
           node->parent,
           node->lChild,
           node->rChild);
}
RBTNode* CreateRBTNode(){
    RBTNode* node = (RBTNode*)calloc(1,sizeof (RBTNode));
    return node;
}