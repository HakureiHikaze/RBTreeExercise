#pragma once
#include "RBTNode.h"
#include "Vector.h"
typedef struct RBTree_{
    RBTNode * root;
}RBTree;
extern RBTree* CreateRBTree();
extern void RBTMidTraversal(RBTree*);
extern void RBTPreTraversal(RBTree*);
extern void RBTPostTraversal(RBTree*);
extern void Release(RBTree*);
extern void Insert(RBTree*, size_t);
extern unsigned GetDepth(RBTree*);
extern RBTNode* FindData(RBTree*, size_t, size_t*);
extern Vector** ToLayer(RBTree*);
extern void DrawTree(RBTree* tree);