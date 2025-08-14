#include "RBTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Helper function to check red-black tree properties
int check_rb_properties(RBTNode* node, int black_count, int* path_black_count) {
    if (!node) {
        if (*path_black_count == -1) {
            *path_black_count = black_count;
        }
        return *path_black_count == black_count;
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
        printf("Parent pointer error in left child of %zu\n", node->data);
        return 0;
    }
    if (node->rChild && node->rChild->parent != node) {
        printf("Parent pointer error in right child of %zu\n", node->data);
        return 0;
    }
    
    return check_rb_properties(node->lChild, black_count, path_black_count) &&
           check_rb_properties(node->rChild, black_count, path_black_count);
}

int validate_rb_tree(RBTree* tree) {
    if (!tree->root) return 1; // Empty tree is valid
    
    // Root must be black
    if (tree->root->color != 0) {
        printf("Root is not black\n");
        return 0;
    }
    
    // Root should have no parent
    if (tree->root->parent != NULL) {
        printf("Root has a parent\n");
        return 0;
    }
    
    int path_black_count = -1;
    return check_rb_properties(tree->root, 0, &path_black_count);
}

void print_tree_inorder(RBTNode* node) {
    if (!node) return;
    print_tree_inorder(node->lChild);
    printf("%zu(%c) ", node->data, node->color ? 'R' : 'B');
    print_tree_inorder(node->rChild);
}

void test_deletion_basic() {
    printf("=== Basic Deletion Test ===\n");
    RBTree* tree = CreateRBTree();
    
    // Insert some values
    int values[] = {10, 5, 15, 3, 7, 12, 18, 1, 4, 6, 8, 11, 13, 16, 20};
    int n = sizeof(values) / sizeof(values[0]);
    
    for (int i = 0; i < n; i++) {
        Insert(tree, values[i]);
        if (!validate_rb_tree(tree)) {
            printf("Tree invalid after inserting %d\n", values[i]);
            Release(tree);
            return;
        }
    }
    
    printf("Tree after insertion: ");
    print_tree_inorder(tree->root);
    printf("\n");
    
    // Test deletion of various nodes
    int delete_values[] = {1, 15, 10, 7, 20};
    int delete_n = sizeof(delete_values) / sizeof(delete_values[0]);
    
    for (int i = 0; i < delete_n; i++) {
        printf("Deleting %d...\n", delete_values[i]);
        unsigned result = Delete(tree, delete_values[i]);
        if (result) {
            printf("Successfully deleted %d\n", delete_values[i]);
        } else {
            printf("Failed to delete %d\n", delete_values[i]);
        }
        
        printf("Tree after deletion: ");
        print_tree_inorder(tree->root);
        printf("\n");
        
        if (!validate_rb_tree(tree)) {
            printf("Tree invalid after deleting %d\n", delete_values[i]);
            Release(tree);
            return;
        }
    }
    
    printf("All deletions successful and tree remains valid!\n");
    Release(tree);
}

void test_deletion_edge_cases() {
    printf("\n=== Edge Cases Test ===\n");
    RBTree* tree = CreateRBTree();
    
    // Test deletion from empty tree
    printf("Testing deletion from empty tree...\n");
    unsigned result = Delete(tree, 42);
    if (!result) {
        printf("✓ Correctly handled deletion from empty tree\n");
    } else {
        printf("✗ Deletion from empty tree should return 0\n");
    }
    
    // Test single node deletion
    printf("Testing single node deletion...\n");
    Insert(tree, 100);
    printf("Inserted 100, tree root: %p\n", (void*)tree->root);
    result = Delete(tree, 100);
    printf("Delete result: %u, tree root after: %p\n", result, (void*)tree->root);
    if (result && tree->root == NULL) {
        printf("✓ Correctly deleted single node\n");
    } else {
        printf("✗ Single node deletion failed\n");
    }
    
    // Test deletion of non-existent node
    printf("Testing deletion of non-existent node...\n");
    Insert(tree, 50);
    printf("Inserted 50, about to delete 999...\n");
    result = Delete(tree, 999);
    printf("Delete non-existent result: %u\n", result);
    if (!result) {
        printf("✓ Correctly handled deletion of non-existent node\n");
    } else {
        printf("✗ Should not delete non-existent node\n");
    }
    
    printf("Releasing tree...\n");
    Release(tree);
    printf("Tree released successfully\n");
}

void test_memory_safety() {
    printf("\n=== Memory Safety Test ===\n");
    RBTree* tree = CreateRBTree();
    
    // Insert and delete many nodes to stress test memory management
    for (int i = 1; i <= 100; i++) {
        Insert(tree, i);
    }
    
    // Delete every other node
    for (int i = 2; i <= 100; i += 2) {
        Delete(tree, i);
        if (!validate_rb_tree(tree)) {
            printf("Tree became invalid during mass deletion at %d\n", i);
            Release(tree);
            return;
        }
    }
    
    // Delete remaining nodes
    for (int i = 1; i <= 100; i += 2) {
        Delete(tree, i);
        if (!validate_rb_tree(tree)) {
            printf("Tree became invalid during final deletion at %d\n", i);
            Release(tree);
            return;
        }
    }
    
    if (tree->root == NULL) {
        printf("✓ All nodes deleted successfully, tree is empty\n");
    } else {
        printf("✗ Tree should be empty after deleting all nodes\n");
    }
    
    Release(tree);
    printf("✓ Memory safety test completed\n");
}

int main() {
    printf("Red-Black Tree Deletion Testing\n");
    printf("================================\n");
    
    test_deletion_basic();
    test_deletion_edge_cases();
    test_memory_safety();
    
    printf("\n=== Testing Complete ===\n");
    return 0;
}