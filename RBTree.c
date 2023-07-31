#include <stdlib.h>
#include "RBTree.h"
#include "LinkedQueue.h"
#include "Vector.h"
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
    }
    free(node->lChild);
    if(node->rChild) {
        releaseRecursively_(node->rChild);
    }
    free(node->rChild);
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

RBTNode* createRBTNode_(RBTNode* parent, size_t data, int color){
    RBTNode * newNode = CreateRBTNode();
    newNode->parent = parent;
    newNode->data = data;
    newNode->color = color;
    return newNode;
}

RBTNode* insert_(RBTNode * node, size_t data){//todo: implement comparing callback
    if (data >= node->data){
        if(node->rChild) {
            insert_(node->rChild, data);
        }
        else {
            RBTNode * newNode = createRBTNode_(node,data,1);
            node->rChild = newNode;
            adjust_(newNode);
            return newNode;
        }
    }else{
        if(node->lChild){
            insert_(node->lChild, data);
        }else{
            RBTNode * newNode = createRBTNode_(node,data,1);
            node->lChild = newNode;
            adjust_(newNode);
            return newNode;
        }
    }
    return 0;
}

void resetRoot_(RBTree* tree, RBTNode* node){
    if(node){
        if(node->parent){
            resetRoot_(tree, node->parent);
        }
        else {
            tree->root = node;
            return;
        }
    }
    if(tree->root->parent){
        resetRoot_(tree, tree->root);
    }
}

void Insert(RBTree* tree, size_t data){
    if(tree->root) {
        insert_(tree->root, data);
        resetRoot_(tree,0);
    }
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
        if(temp->parent){
            if(temp->parent->lChild == node){
                temp->parent->lChild = temp;
            }
            else{
                temp->parent->rChild = temp;
            }
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
        if(temp->parent){
            if( temp->parent->lChild == node){
                temp->parent->lChild = temp;
            }
            else{
                temp->parent->rChild = temp;
            }
        }
    }
}

void clockwiseNew_(RBTNode* node){

}

void adjust_(RBTNode* node){
    RBTNode* parent = node->parent;
    RBTNode* uncle = getUncle_(node);
    RBTNode* grandparent = getGrandparent_(node);
    //根节点，设置为黑节点后直接添加
    if(!parent) {//root
        node->color = BLACK;
        return;
    }
    //父节点为黑，直接添加
    if(parent->color == BLACK)return;
    //第二层的情形
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
unsigned getDepth_(RBTNode* node){
    if(!node)return 0;
    return MAX(getDepth_(node->lChild)+1, getDepth_(node->rChild)+1);
}
unsigned GetDepth(RBTree* tree){
    return tree?getDepth_(tree->root):0;
}

RBTNode* findData_(RBTNode* node, size_t data, size_t* depth){
    if(data == node->data){
        return node;
    }else if(node->rChild && data > node->data){
        *depth+=1;
        return findData_(node->rChild, data, depth);
    }else if(node->rChild && data < node->data){
        *depth+=1;
        return findData_(node->lChild, data, depth);
    }else{
        depth = 0;
        return 0;
    }
}

RBTNode* FindData(RBTree* tree, size_t data, size_t* depth){
    *depth+=1;
    return findData_(tree->root, data, depth);
}

Vector** toLayer_(RBTree* tree){
    Queue* queues[2];
    queues[0] = CreateQueue();
    queues[1] = CreateQueue();
    unsigned depth = GetDepth(tree);
    Vector** vector = (Vector**) calloc(depth+1, sizeof(Vector*));
    vector[0]= (void*)(0ll^depth);
    for(unsigned i = 1; i<depth+1; i++){
        vector[i] = VectorCreate();
    }
    if(tree){
        unsigned flag = 0;
        size_t i = 1;
        RBTNode* cursor;
        Enqueue(queues[0],tree->root);
        while(queues[0]->size || queues[1]->size){
            cursor = (RBTNode*)Dequeue(queues[flag]);
            VectorAppend(vector[i],cursor);
            if(cursor->lChild){
                Enqueue(queues[!flag], cursor->lChild);
            }
            if(cursor->rChild){
                Enqueue(queues[!flag], cursor->rChild);
            }
            if(GetQueueSize(queues[flag]) == 0){
                flag = !flag;
                i++;
            }
        }
    }
    ReleaseQueue(queues[0]);
    ReleaseQueue(queues[1]);
    return vector;
}

Vector** ToLayer(RBTree* tree){
    return toLayer_(tree);
}

unsigned* GetMaxDigitsOfEachLayer(RBTree* tree){
    unsigned depth = GetDepth(tree);
    unsigned* temp = (unsigned *)calloc(depth, sizeof (unsigned)+1);
    temp[0] = depth;
}