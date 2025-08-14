#include "RBTree.h"
#include <stdio.h>
#include <stdlib.h>

// Helper function to check red-black tree properties
int check_rb_properties(RBTNode* node, int black_count, int* path_black_count) {
    if (!node) {
        if (*path_black_count == -1) {
            *path_black_count = black_count;
            printf("First path black count: %d\n", black_count);
        } else if (*path_black_count != black_count) {
            printf("Black count mismatch: expected %d, got %d\n", *path_black_count, black_count);
            return 0;
        }
        return 1;
    }
    
    // Red node cannot have red children
    if (node->color == 1) { // RED
        if ((node->lChild && node->lChild->color == 1) || 
            (node->rChild && node->rChild->color == 1)) {
            printf("Red-Red violation found at node %zu\n", node->data);
            return 0;
        }
    }
    
    // Count black nodes
    if (node->color == 0) { // BLACK
        black_count++;
    }
    
    // Check BST property
    if (node->lChild && node->lChild->data >= node->data) {
        printf("BST violation: left child %zu >= parent %zu\n", node->lChild->data, node->data);
        return 0;
    }
    if (node->rChild && node->rChild->data <= node->data) {
        printf("BST violation: right child %zu <= parent %zu\n", node->rChild->data, node->data);
        return 0;
    }
    
    // Check parent pointers
    if (node->lChild && node->lChild->parent != node) {
        printf("Parent pointer error in left child of %zu (expected %p, got %p)\n", 
               node->data, (void*)node, (void*)node->lChild->parent);
        return 0;
    }
    if (node->rChild && node->rChild->parent != node) {
        printf("Parent pointer error in right child of %zu (expected %p, got %p)\n", 
               node->data, (void*)node, (void*)node->rChild->parent);
        return 0;
    }
    
    return check_rb_properties(node->lChild, black_count, path_black_count) &&
           check_rb_properties(node->rChild, black_count, path_black_count);
}

int validate_rb_tree(RBTree* tree) {
    if (!tree->root) return 1; // Empty tree is valid
    
    // Root must be black
    if (tree->root->color != 0) {
        printf("Root is not black (color: %d)\n", tree->root->color);
        return 0;
    }
    
    // Root should have no parent
    if (tree->root->parent != NULL) {
        printf("Root has a parent: %p\n", (void*)tree->root->parent);
        return 0;
    }
    
    int path_black_count = -1;
    int result = check_rb_properties(tree->root, 0, &path_black_count);
    if (!result) {
        printf("Failed RB properties check\n");
    }
    return result;
}

void print_tree_inorder(RBTNode* node) {
    if (!node) return;
    print_tree_inorder(node->lChild);
    printf("%zu(%c) ", node->data, node->color ? 'R' : 'B');
    print_tree_inorder(node->rChild);
}

int main() {
    printf("Debugging deletion issue\n");
    RBTree* tree = CreateRBTree();
    
    // Insert first few numbers
    for (int i = 1; i <= 5; i++) {
        printf("Inserting %d...\n", i);
        Insert(tree, i);
        printf("Tree: ");
        print_tree_inorder(tree->root);
        printf("\n");
        if (!validate_rb_tree(tree)) {
            printf("Tree invalid after inserting %d\n", i);
            Release(tree);
            return 1;
        }
    }
    
    printf("\n=== Starting deletions ===\n");
    
    // Delete even numbers
    for (int i = 2; i <= 4; i += 2) {
        printf("Deleting %d...\n", i);
        unsigned result = Delete(tree, i);
        printf("Result: %u\n", result);
        printf("Tree: ");
        print_tree_inorder(tree->root);
        printf("\n");
        if (!validate_rb_tree(tree)) {
            printf("Tree invalid after deleting %d\n", i);
            Release(tree);
            return 1;
        }
        printf("Tree is valid after deleting %d\n", i);
    }
    
    Release(tree);
    printf("Test completed successfully!\n");
    return 0;
}