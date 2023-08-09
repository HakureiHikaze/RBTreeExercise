#include <stdlib.h>
#include "RBTree.h"
#include "LinkedQueue.h"
#include "Vector.h"
#include "StringProducer.h"
#include <wchar.h>
#include "Utilities.h"
#define MAX(m,n) m>n?m:n
#define RED 1
#define BLACK 0
#define RIGHT L'0'
#define LEFT L'1'
wchar_t up_right = L'┌';
wchar_t down_right = L'└';
wchar_t up_left = L'┐';
wchar_t down_left = L'┘';
wchar_t T_cross = L'┤';
wchar_t line = L'│';

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
    if(!node) return;
    if(node->lChild) {
        releaseRecursively_(node->lChild);
    }
    if(node->rChild) {
        releaseRecursively_(node->rChild);
    }
    free(node);
}

void Release(RBTree* tree){
    if(tree->root) releaseRecursively_(tree->root);
    free(tree);
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
    vector[0]= (void*)(0ll^depth)+1;
    for(unsigned i = 1; i<depth+1; i++){
        vector[i] = VectorCreate();
    }
    if(tree){
        unsigned flag = 0;
        unsigned queueFlag[]={1,1};
        size_t i = 1;
        RBTNode* cursor;
        Enqueue(queues[0],tree->root);
        while(queueFlag[flag]){
            cursor = (RBTNode*)Dequeue(queues[flag]);
            VectorAppend(vector[i],cursor);
            if(cursor){
                Enqueue(queues[!flag], cursor->lChild);
                Enqueue(queues[!flag], cursor->rChild);
                if(cursor->lChild || cursor->rChild){
                    queueFlag[!flag] = 1;
                }
            }else{
                Enqueue(queues[!flag], 0);
                Enqueue(queues[!flag], 0);
                queueFlag[!flag] = queueFlag[!flag] != 0;
            }
            if(GetQueueSize(queues[flag]) == 0){
                queueFlag[flag] = 0;
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

///
/// \param node node
/// \param width width of whole formatted text
/// \return formatted text
wchar_t* formatNode_(RBTNode* node, unsigned width){
    wchar_t* temp = (wchar_t*) calloc(width+1, sizeof(wchar_t));
    temp[width] = L'\0';
    swprintf_s(temp,width,L"%ld,%u",node->data, node->color);
    StringProducer* sp = SPNewWStr(temp);
    free(temp);
    while(sp->length < width-2){
        SPInsertWChar(sp,0 , L' ');
    }
    SPInsertWChar(sp,0,L'(');
    SPAppendWChar(sp,L')');
    temp = SPBuildString(sp);
    SPRelease(sp);
    return temp;
}
unsigned getMaxDigitsRecur_(RBTNode* node){
    if(node){
        unsigned temp = DigitLen((long)node->data);
        unsigned l = MAX(temp, getMaxDigitsRecur_(node->lChild));
        unsigned r = MAX(temp, getMaxDigitsRecur_(node->rChild));
        unsigned re = MAX(l,r);
        return re;
    }
    return 0;
}
unsigned getMaxDigitsOfTree_(RBTree* tree){
    if(tree && tree->root){
        return getMaxDigitsRecur_(tree->root);
    }
    return 0;
}

//src: https://blog.csdn.net/Hodaka/article/details/128376957
void drawTreeRecur(RBTNode* node, StringProducer* spWay, unsigned width){
    if(!spWay) spWay = SPNewEmpty();
    if(node->rChild){
        StringProducer* right_way = SPAppendWChar(SPCloneSP(spWay), RIGHT);
        drawTreeRecur(node->rChild, right_way, width);
    }
    StringProducer* pre = SPNewEmpty();
    if(spWay->length == 0){
        SPAppendWChar(pre, L' ');
    }else{
        for(int i = 0; i<=width; i++){
            SPAppendWChar(pre, L' ');
        }
        for(int i =1; i< spWay->length; i++){
            if(spWay->buffer[i] != spWay->buffer[i-1]){
                SPAppendWChar(pre, line);
                for(int j = 0; j<=width-1; j++){
                    SPAppendWChar(pre, L' ');
                }
            }else{
                for(int j = 0; j<=width; j++){
                    SPAppendWChar(pre, L' ');
                }
            }
        }
        size_t l = spWay->length;
        if(spWay->buffer[l-1] == L'0'){
            SPAppendWChar(pre,up_right);
        }else{
            SPAppendWChar(pre,down_right);
        }
    }
    wchar_t* preStr = SPBuildString(pre);
    SPRelease(pre);
    wprintf_s(preStr);
    free(preStr);
    wchar_t* nodeStr = formatNode_(node, width);
    wprintf_s(nodeStr);
    free(nodeStr);
    if (node->lChild && node->rChild)
        wprintf_s(L"%c",T_cross);
    else if (node->lChild && !node->rChild)
        wprintf_s(L"%c",up_left);
    else if (!node->lChild && node->rChild)
        wprintf_s(L"%c",down_left);
    wprintf_s(L"\n");
    if(node->lChild){
        StringProducer* left_way = SPAppendWChar(SPCloneSP(spWay), LEFT);
        drawTreeRecur(node->lChild, left_way, width);
    }
    SPRelease(spWay);
}

void DrawTree(RBTree* tree){
    if(tree)drawTreeRecur(tree->root,0, getMaxDigitsOfTree_(tree)+4);
}