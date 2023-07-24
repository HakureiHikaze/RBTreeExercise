#pragma once
#include <stdlib.h>
#include "RBTree.h"
#define MAX(m,n) m>n?m:n
#define RED 1
#define BLACK 0
//the underline after functions indicates internal function

RBTree* CreateRBTree(){
    RBTree* tree = (RBTree*)calloc(1,sizeof(RBTree));
    return tree;
}
void midTraversal_(RBTNode* node){
    if(node->lChild) midTraversal_(node->lChild);
    PrintRBTNode(node);
    if(node->rChild) midTraversal_(node->rChild);
}
void RBTMidTraversal(RBTree* tree){
    midTraversal_(tree->root);
}
void releaseRecursively_(RBTNode* node){
    if(node->lChild) {
        releaseRecursively_(node->lChild);
        free(node->lChild);
    }
    if(node->rChild) {
        releaseRecursively_(node->rChild);
        free(node->rChild);
    }
}

void Release(RBTree* tree){
    if(tree->root) releaseRecursively_(tree->root);
}

RBTNode* getGrandparent_(RBTNode* node){
    return node->parent? node->parent->parent:0;
}

RBTNode* getUncle_(RBTNode* node){
    RBTNode * grand = getGrandparent_(node);
    return grand? (grand->lChild == node->parent? grand->rChild:grand->lChild):0;
}

void adjust_(RBTNode*);
void adjust_redP_redU(RBTNode*);
void adjust_redP_RL_LR_blackU(RBTNode*);
void adjust_redP_RR_LL_blackU(RBTNode*);
void anticlockwise_(RBTNode*);
void clockwise_(RBTNode*);

RBTNode* insert_(RBTNode * node, int data){//todo: implement comparing callback
    if (data >= node->data){
        if(node->rChild) {
            insert_(node->rChild, data);
        }
        else {
            RBTNode * newNode = CreateRBTNode();
            node->rChild = newNode;
            newNode->parent = node;
            newNode->data = data;
            newNode->color = 1;
            adjust_(newNode);
            return newNode;
        }
    }else{
        if(node->lChild){
            insert_(node->lChild, data);
        }else{
            RBTNode * newNode = CreateRBTNode();
            node->lChild = newNode;
            newNode->parent = node;
            newNode->data = data;
            newNode->color = 1;
            adjust_(newNode);
            return newNode;
        }
    }
    return 0;
}

void Insert(RBTree* tree, int data){
    if(tree->root)insert_(tree->root, data);
    else{
        RBTNode * root = CreateRBTNode();
        root->data = data;
        tree->root = root;
    }
}
///
/// \param node
/// \param from path that traversals recursively

void clockwise_(RBTNode* node){
    if(node->lChild){
        //temp: original lChild of current node
        RBTNode * temp = node->lChild;

        node->lChild = temp->rChild;
        if(node->lChild) node->lChild->parent = node;//Re-assign node.lChild

        temp->rChild = node;
        temp->parent = node->parent;//transfer parent ptr
        node->parent = temp;
        if(temp->parent->lChild == node){
            temp->parent->lChild = temp;
        }
        else{
            temp->parent->rChild = temp;
        }
    }
}
void anticlockwise_(RBTNode* node){
    if(node->rChild){
        //temp: original rChild of current node
        RBTNode * temp = node->rChild;
        node->rChild = temp->lChild;
        if(node->rChild) node->rChild->parent = node;
        temp->lChild = node;
        temp->parent = node->parent;
        node->parent = temp;
        if(temp->parent->lChild == node){
            temp->parent->lChild = temp;
        }
        else{
            temp->parent->rChild = temp;
        }
    }
}
void adjust_(RBTNode* node){
    RBTNode* parent = node->parent;
    RBTNode* uncle = getUncle_(node);
    RBTNode* grandparent = getGrandparent_(node);
    if(!parent) {//root
        node->color = BLACK;
        return;
    }
    if(parent->color == BLACK)return;
    if(!grandparent){//1st children
        adjust_(parent);
        return;
    }
    if(uncle){//uncle exists
        if(uncle->color == RED){
            adjust_redP_redU(node);
            return;
        }else{
            if((node == parent->lChild && parent == grandparent->lChild)||
            (node == parent->rChild && parent == grandparent->rChild)){
                adjust_redP_RR_LL_blackU(node);
                return;
            }else{
                adjust_redP_RL_LR_blackU(node);
                return;
            }
        }
    }
    if((node == parent->lChild && parent == grandparent->lChild)||
       (node == parent->rChild && parent == grandparent->rChild)){
        adjust_redP_RR_LL_blackU(node);
        return;
    }else{
        adjust_redP_RL_LR_blackU(node);
        return;
    }
}

void adjust_redP_redU(RBTNode* node){//rNrPrU, G exists
    node->parent->color = BLACK;
    getUncle_(node)->color = BLACK;
    getGrandparent_(node)->color = RED;
    adjust_(getGrandparent_(node));
}
void adjust_redP_RL_LR_blackU(RBTNode* node){//0: lrPrrNbU; 1: rrPlrNbU
    RBTNode* originParent = node->parent;
    RBTNode* originGrand = getGrandparent_(node);
    if(originGrand->rChild == originParent && originParent->lChild == node){
        clockwise_(originParent);
        adjust_redP_RR_LL_blackU(originParent);
    }else{
        anticlockwise_(originParent);
        adjust_redP_RR_LL_blackU(originParent);
    }
}
void adjust_redP_RR_LL_blackU(RBTNode* node){
    RBTNode* originParent = node->parent;
    RBTNode* originGrand = getGrandparent_(node);
    RBTNode* originUncle = getUncle_(node);
    if(originGrand->rChild == originParent && originParent->rChild == node){
        anticlockwise_(originGrand);
        originGrand->color = RED;
        originParent->color = BLACK;
    }else{
        clockwise_(originGrand);
        originGrand->color = RED;
        originParent->color = BLACK;
    }
}
int getDepth_(RBTNode* node){
    if(!node)return 0;
    return MAX(getDepth_(node->lChild)+1, getDepth_(node->rChild)+1);
}
int GetDepth(RBTree* tree){
    return tree?getDepth_(tree->root):0;
}