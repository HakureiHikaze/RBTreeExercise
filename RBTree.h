#pragma once
#include "RBTNode.h"
typedef struct RBTree_{
    RBTNode * root;
}RBTree;
extern RBTree* CreateRBTree();
extern void RBTMidTraversal(RBTree*);
extern void RBTPreTraversal(RBTree*);
extern void RBTPostTraversal(RBTree*);
extern void Release(RBTree*);
extern void Insert(RBTree*, size_t);
extern int GetDepth(RBTree*);
extern RBTNode* FindData(RBTree*, size_t, size_t*);