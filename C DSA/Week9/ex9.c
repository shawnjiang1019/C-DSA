/**
 * Exercise 8 - More BST Operations
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * Any clarifications and corrections will be posted to Piazza so please keep an
 * eye on the forum!
 *
 * Unauthorized distribution or posting is strictly prohibited. You must seek
 * approval from course staff before uploading and sharing with others.
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BSTNode BSTNode;
struct BSTNode {
    int value;
    BSTNode* left;
    BSTNode* right;
};

/**
 * This function allocates a new node for a Binary Search Tree (BST) with the
 * specified value. If the allocation fails, it returns NULL.
 *
 * @param value The value to be assigned to the new node.
 * @return Pointer to the newly allocated BST node or NULL if allocation fails.
 */
BSTNode* allocate_new_node(int value) {
    // NOTE: This function is already completed for you.
    BSTNode* node = malloc(sizeof(BSTNode));
    if (node == NULL) {
        return NULL;
    }

    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * Given the root of a BST, this function recursively frees the memory
 * associated with the entire tree, including all nodes and their values.
 *
 * @param root Pointer to the root of the BST to be freed.
 */
void free_tree(BSTNode* root) {
    // NOTE: This function is already completed for you.
    if (root == NULL) {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

/**
 * Given the root of a BST and a value, this function inserts a new node with
 * the specified value into the BST. Returns the root of the modified BST.
 *
 * @param root Pointer to the root of the BST.
 * @param value The value to be inserted into the BST.
 * @return Pointer to the root of the modified BST.
 */
BSTNode* insert_value(BSTNode* root, int value) {
    // NOTE: This function is already completed for you.
    if (root == NULL) {
        return allocate_new_node(value);
    } else if (root->value == value) {
        return root;
    } else if (root->value > value) {
        root->left = insert_value(root->left, value);
        return root;
    } else {
        root->right = insert_value(root->right, value);
        return root;
    }
}

/**
 * Given the root of a BST and a value, this function searches for the value
 * in the BST. Returns true if the value was found, false otherwise.
 *
 * @param root Pointer to the root of the BST.
 * @param value The value to be searched for in the BST.
 * @return true if the value was found, false otherwise.
 */
bool contains_value(BSTNode* root, int value) {
    // NOTE: This function is already completed for you.
    if (root == NULL) {
        return false;
    } else if (root->value == value) {
        return true;
    } else if (value > root->value) {
        return contains_value(root->right, value);
    } else {
        return contains_value(root->left, value);
    }
}

/**
 * Given the root of a BST and a value, this function deletes the node with
 * the specified value from the BST and deallocates any unused nodes. Returns
 * the root of the modified BST.
 *
 * @param root Pointer to the root of the BST.
 * @param value The value to be deleted from the BST.
 * @return Pointer to the root of the modified BST.
 */


// BSTNode* delete_value(BSTNode* root, int value) {
//     if (contains_value(root, value) == false){
//         return root;
//     }

//     BSTNode* tmp = root;

//     if (root == NULL){
//         return NULL;
//     }
//     if (root->value > value){
//         delete_value(root->left, value);
//         return root;
//     } 
//     if (root->value < value){
//         delete_value(root->right, value);
//         return root;
//     }

//     if (root->value == value){
//         //if there are no children then simply delete withour worry.
//         if (root->left == NULL && root->right == NULL){
//             free(root);
//             return tmp;
//         } 
//         //One child on the left
//         else if (root->right == NULL){
//             tmp = root->left;
//             free(root);
//             return tmp;
//         }
//         //One child on the right
//         else if (root->left == NULL){
//             tmp = root->right;
//             free(root);
//             return tmp;
//         }
//         // two children
//         else {
//             BSTNode* successorParent = root;
//             BSTNode* successor = root->right;
//             while (successor->left != NULL){
//                 successorParent = successor;
//                 successor = successor->left;
//             }

//             if (successorParent != root){
//                 successorParent->left = successor->right;
//             } else {
//                 successorParent->right = successor->right;
//             }
//             root->value = successor->value;
//             free(successor);
//             return root;

//         }

//     }



//     return root;
// }

BSTNode* get_BST_min(BSTNode* node){
    while (node->left != NULL){
        node = node->left;
    }
    return node;
}

BSTNode* delete_BST_min(BSTNode* node){
    if (node == NULL){
        return NULL;
    }
    if (node->left == NULL){
        BSTNode* tmp = node->right;
        free(node);
        return tmp;
    }
    node->left = delete_BST_min(node->left);
    return node;
}


BSTNode* delete_value(BSTNode* root, int value){
    if (root == NULL){
        return NULL;
    }

    if (value < root->value){
        root->left = delete_value(root->left, value);
    }

    if (value > root->value){
        root->right = delete_value(root->right, value);
    }

    else {
        //if no children nodes
        if (root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        }

        else if (root->left == NULL){
            BSTNode* tmp = root->right;
            free(root);
            return tmp;
        }

        else if (root->right == NULL){
            BSTNode* tmp = root->left;
            free(root);
            return tmp;
        }

        BSTNode* tmp = get_BST_min(root->right);
        root->value = tmp->value;
        root->right = delete_BST_min(root->right);
    }
    
    return root;
}

// ===========================================================================
// DO NOT CHANGE ANY 'ifndef' AND 'endif' MACROS.
// These macros help ensure your parts of your code does not conflict with the
// automarker. Changing them will result in your code not compiling and you
// receiving a 0 for the entire assignment.
// ===========================================================================
#ifndef __testing__

int main() {
    // This is our initial BST.
    BSTNode* root = NULL;
    root = insert_value(root, 60);
    
    root = insert_value(root, 41);
    root = insert_value(root, 74);
    root = insert_value(root, 16);
    root = insert_value(root, 53);
    root = insert_value(root, 65);
    root = insert_value(root, 25);
    root = insert_value(root, 46);
    root = insert_value(root, 55);
    root = insert_value(root, 63);
    root = insert_value(root, 70);
    root = insert_value(root, 42);
    root = insert_value(root, 62);
    root = insert_value(root, 64);

    // Try to delete a node that doesn't exist. Nothing should happen.
    root = delete_value(root, 10000);
    
    
    
    // Delete a node that exists.
    
    
    
    assert(contains_value(root, 53) == true);
    
    root = delete_value(root, 55);
    
    
    assert(contains_value(root, 55) == false);
    

    // Don't forget to release any memory!
    free_tree(root);

    printf("All test cases passed. Have you written any of your own?\n");
    return 0;
}

#endif
