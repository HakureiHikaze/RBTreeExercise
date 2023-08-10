#pragma once
#include "RBTNode.h"
#include "Vector.h"
typedef struct RBTree_{
    RBTNode * root;
}RBTree;
/// Initialize a new red-black tree. All fields equal to 0.
/// \return
extern RBTree* CreateRBTree();
extern void RBTMidTraversal(RBTree*);
extern void RBTPreTraversal(RBTree*);
extern void RBTPostTraversal(RBTree*);
/// Release the target tree, and release every nodes.
/// \param tree Target tree pointer
extern void Release(RBTree* tree);
/// Insert a data into the target tree, then adjust nodes that affect the properties.
/// \param tree Target tree pointer
/// \param data The data being inserted
extern void Insert(RBTree* tree, size_t data);
/// Delete specified data from the target tree, then adjust nodes that affect the properties.
/// \param tree Target tree pointer
/// \param data The data being deleted
/// \return Whether successfully deleted the target data
extern unsigned Delete(RBTree* tree, size_t data);
/// Get maximum depth of the target tree.
/// \param tree Target tree pointer
/// \return The maximum depth of the tree
extern unsigned GetDepth(RBTree* tree);
/// Find specified data node.
/// \param tree Target tree pointer
/// \param data Specified data
/// \param depth Static depth variable that help determining the searching path
/// \return The node pointer that contains the target data
extern RBTNode* FindData(RBTree* tree, size_t data, size_t* depth);
/// Layer traversal of target tree.\n
/// Vector structure: \n
///     [0]     Length of vector array ( =maximum depth + 1)\n
///     [1...]  Vector that contains tree layer sequence
/// \param tree Target tree pointer
/// \return Vector array pointer
extern Vector** ToLayer(RBTree* tree);
/// Draw tree horizontally
/// \param tree Target tree pointer
extern void DrawTree(RBTree* tree);