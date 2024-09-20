/**
 * Assignment 1 - Wackman Compression
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * There are also additional notes and clarifications on Quercus.
 *
 * Any clarifications and corrections will be posted to Piazza so please keep an
 * eye on the forum!
 *
 * Unauthorized distribution or posting is strictly prohibited. You must seek
 * approval from course staff before uploading and sharing with others.
 */

// No additional imports are allowed. You can make helper functions if you wish.
#include "wackman.h"

/**
 * Given an array of integers and its length, this function calculates
 * the sum of all the elements in the array.
 *
 * @pre The array size (array_size) must be greater than or equal to 0.
 *
 * @param int_array Pointer to the array of integers.
 * @param array_size The number of elements in the array.
 * @return The sum of all integers in the array.
 */
int sum_array_elements(int int_array[], int array_size) {
    int sum = 0;

    if (int_array == NULL){
        return 0;
    }
    for (int i = 0; i < array_size; ++i){
        sum = sum + int_array[i];
    }   
    return sum;
}

/**
 * Given an integer array of size ASCII_CHARACTER_SET_SIZE, this function
 * computes the number of occurrences of each ASCII character in the given
 * string. The results are stored in the corresponding indices of the
 * occurrence_array. The computation stops at and does not include the DELIMITER
 * character.
 *
 * @note The occurrence_array[0] should always be 0, representing the DELIMITER.
 * @note The ASCII decimal value of each character corresponds to its index in
 * the array. For example, 'F' with ASCII decimal value 70 will increment
 * occurrence_array[70].
 *
 * @param occurrence_array An array to store the occurrences of each ASCII
 * characters. The array size should be ASCII_CHARACTER_SET_SIZE.
 * @param string The input string to analyze for ASCII character occurrences.
 */
void compute_occurrence_array(int occurrence_array[ASCII_CHARACTER_SET_SIZE], char* string) {
    // TODO: Complete this function.

    if (occurrence_array == NULL || string == NULL){
        return;

    }

    
    for (int i = 0; i < ASCII_CHARACTER_SET_SIZE; ++i){
        occurrence_array[i] = 0;
    }
    if (string != NULL){
        for (int i = 0; i < strlen(string); ++i){
        
            occurrence_array[(int)(string[i])]++;
        }
    }
    

}

/**
 * Given an integer array of size ASCII_CHARACTER_SET_SIZE, this function
 * computes and returns the number of characters that occur one or more times.
 *
 * @param occurrence_array An array representing the occurrences of ASCII
 * characters. The array size should be ASCII_CHARACTER_SET_SIZE.
 * @return The number of characters occurring one or more times in the ASCII
 * character set.
 */
int count_positive_occurrences(int occurrence_array[ASCII_CHARACTER_SET_SIZE]) {
    // TODO: Complete this function.
    if (occurrence_array == NULL){
        return 0;
    }
    int occurances = 0;
    for (int i = 0; i < ASCII_CHARACTER_SET_SIZE; ++i){
        if (occurrence_array[i] != 0){
            occurances++;
        }
    }
    return occurances;
}

/**
 * Given an integer array of size ASCII_CHARACTER_SET_SIZE, representing the
 * number of occurrences of ASCII characters, this function creates and returns
 * a sorted linked list of WackyLinkedNodes.
 *
 * Each node in the list stores a tree with a single leaf node. The node will
 * contain information about the probability of occurrence 'weight' and the
 * ASCII character itself 'val'.
 *
 * @note Exclude elements with a probability of 0 from the linked list.
 * @note Ensure that the linked list is sorted in ascending order from head to
 * tail, first by the probability of occurrence ('weight'), and in case of ties,
 * by the ASCII character ('val') in ascending order.
 * @note Compute the probability of occurrence for each ASCII character α as
 * occurrence_array[α] / SUM(occurrence_array).
 * @note The memory of any required data types must be allocated manually.
 *
 * @param occurrence_array An array representing the occurrences of ASCII
 * characters. The array size should be ASCII_CHARACTER_SET_SIZE.
 * @return A pointer to the head of the created linked list of WackyLinkedNodes.
 */

void printList(WackyLinkedNode* head){
    WackyLinkedNode* cur = head;
    while (cur != NULL){
        printf("(%c) : %f\n", cur->val->val, cur->val->weight);
        cur = cur->next;
    }
}


WackyLinkedNode* create_wacky_list(int occurrence_array[ASCII_CHARACTER_SET_SIZE]) {
    /*
    
    
    STILL HAVE TO SORT THE LINKED LIST
    
    
    */
    int num_elements = count_positive_occurrences(occurrence_array);
    if (num_elements == 0){
        return NULL;
    }
    int total = sum_array_elements(occurrence_array, ASCII_CHARACTER_SET_SIZE );
    WackyTreeNode* holder[num_elements];
    //Create an array of leaf nodes;
    //Dont need to use j just use "i"
    int j = 0;
    for (int i = 0; i < ASCII_CHARACTER_SET_SIZE; ++i){
        if (occurrence_array[i] != 0){
            double weight = (double) occurrence_array[i] / (double) total; 
            holder[j] = new_leaf_node(weight, (char)(i));
            j++;
        }
    }
    WackyTreeNode* temp;
    //Sort the array based on weight
    for (int i = 0; i < num_elements - 1; ++i){
        for (int j = 0; j < num_elements - 1 - i; ++j){
            if (holder[j]->weight > holder[j + 1]->weight){
                temp = holder[j];
                holder[j] = holder[j + 1];
                holder[j + 1] = temp;
            }
            if (holder[j]->weight == holder[j + 1]->weight){
                if (holder[j]->val > holder[j + 1]->val){
                    temp = holder[j];
                    holder[j] = holder[j + 1];
                    holder[j + 1] = temp;
                }
            }
        }
    }
    

    WackyLinkedNode* LLarray[num_elements];

    for (int i = 0; i < num_elements; ++i){
        LLarray[i] = new_linked_node(holder[i]);
    }

    for (int i = 0; i < num_elements - 1; ++i){
        LLarray[i]->next = LLarray[i + 1];
        
    }

    WackyLinkedNode* root = LLarray[0];

    
    return root;
}

//function to get the length of a wacky linked list
int getLength(WackyLinkedNode* linked_list){
    int count = 0; 
    WackyLinkedNode* cur = linked_list;
    while (cur != NULL){
        count++;
        cur = cur->next;
    }
    return count;
}



WackyLinkedNode* insertInAscendingOrder(WackyLinkedNode* head, WackyLinkedNode* newNode) {
    
    WackyLinkedNode* current = head;
    WackyLinkedNode* prev = NULL;

    if (head == NULL){
        return newNode;
    }

    
    while (current != NULL && current->val->weight < newNode->val->weight) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        newNode->next = head;
        return newNode;
    } else {
        prev->next = newNode;
        newNode->next = current;
        return head;
    }
}

/**
 * Given a sorted linked list of WackyTreeNodes, where each node (initially)
 * contains a tree with a single leaf node, this function generates a tree based
 * on the following algorithm:
 * - If the size of the linked list is 2 or more:
 *    - Remove 2 WackyLinkedNodes from the head.
 *    - Create a new WackyTreeNode that joins the tree nodes inside the removed
 *      linked nodes. The first node ('head') goes to the LEFT, and the
 *      following node ('head->next') goes to the RIGHT.
 *    - Create a new WackyLinkedNode and add the newly created WackyTreeNode
 *      back into the linked list. The linked list must remain in sorted order
 *      by the probability of occurrence 'weight'. If the newly created node has
 *      the same weight as another node already in the list, add it in front of
 *      all existing similarily weighted nodes.
 *    - Repeat this algorithm until the size of the linked list is 1.
 * - If the size of the linked list is 1:
 *    - Return the address of the tree held at the head of the linked list.
 * - Otherwise:
 *    - Return NULL.
 *
 * @note The memory of any WackyLinkedNodes must be freed by the end of this
 * function.
 *
 * @param linked_list The sorted linked list of WackyTreeNodes.
 * @return A pointer to the root of the generated tree or NULL if the list is
 * empty.
 */
WackyTreeNode* merge_wacky_list(WackyLinkedNode* linked_list){
    if (getLength(linked_list) == 1){
        printf("reached basecase");
        return linked_list->val;
    }

    if (linked_list == NULL){
        free(linked_list);
        return NULL;
    }

    WackyTreeNode* left;
    WackyTreeNode* right;
    WackyTreeNode* branch;
    WackyLinkedNode* node;
    WackyLinkedNode* head;

    if (getLength(linked_list) == 2){
        left = linked_list->val; //get the left
        right = linked_list->next->val; //get the right
        branch = new_branch_node(left, right); //create the new branch node

        
        free(linked_list->next); //free the old node
        free(linked_list); //free the old node   
        
        return branch;

    }

    if (getLength(linked_list) >= 2){
        
        left = linked_list->val; //get the left
        right = linked_list->next->val; //get the right
        head = linked_list->next->next; //set to the new head
        branch = new_branch_node(left, right); //create the new branch node

        node = new_linked_node(branch); //create the new node
        free(linked_list->next); //free the old node
        free(linked_list); //free the old node   
        

        //add the new node back to the list.
        head = insertInAscendingOrder(head, node);
        //Add at the head
        return merge_wacky_list(head);
        
          
    }
    printf("not good\n");
    return NULL;
}



/**
 * Given a tree, this function calculates and returns the height of the tree.
 *
 * @note An empty tree (NULL) has a height of 0.
 *
 * @param tree Pointer to the root of the tree.
 * @return The height of the tree.
 */
int get_height(WackyTreeNode* tree) {
    if (tree == NULL){
        return 0;
    } else {
        int left_branch_height = get_height(tree->left);
        int right_branch_height = get_height(tree->right);
        if (left_branch_height >= right_branch_height){
            return left_branch_height + 1;
        } else {
            return right_branch_height + 1;
        }
    }
    
}




void set_to_zero(int* num){
    *num = 0;
}

/**
 * Given a WackyTree and a specific character, this function computes the
 * traversal of the character based on its position in the tree. Movement to the
 * LEFT is FALSE, and movement to the RIGHT is TRUE. The steps are written
 * inside boolean_array, and the total number of steps is stored in array_size.
 *
 * @note the size of boolean_array is greater than or equal to get_height(tree)
 *
 * @param tree Pointer to the root of the WackyTree.
 * @param character The specific ASCII character to compute the encoding for.
 * @param boolean_array An array to store the traversal steps.
 * @param array_size Pointer to the variable holding the total number of steps.
 * If the character is not found, -1 is written to array_size instead.
 */


bool get_path(WackyTreeNode* tree, char character, bool boolean_array[], int* index, int depth){
    if (tree == NULL){
        
        return false;
    }
    
    if (tree->val == character){
        return true;
    }

    if (get_path(tree->left, character, boolean_array, index, depth + 1)){
        
        boolean_array[depth] = false;
        (*index)++;
        return true;
    }

    if (get_path(tree->right, character, boolean_array, index, depth + 1)){
        
        boolean_array[depth] = true;
        (*index)++;
        return true;
    }
    
    return false;
}




void get_wacky_code(WackyTreeNode* tree, char character, bool boolean_array[], int* array_size) {
    // TODO: Complete this function.
    set_to_zero(array_size);
    
    if (get_path(tree, character, boolean_array, array_size, 0) == false){
        *array_size = -1;
    }
}

/**
 * Given the root of a WackyTree, a boolean array, and the size of the array,
 * this function traverses the tree. FALSE indicates a movement to the left,
 * and TRUE indicates a movement to the right. The function returns the
 * character at the node reached after all the steps have been taken. If the
 * node is not a leaf node (LEFT and RIGHT are NOT NULL), it returns the
 * DELIMITER ('\0') instead.
 *
 * @param tree Pointer to the root of the WackyTree.
 * @param boolean_array An array representing the traversal steps.
 * @param array_size The size of the boolean array.
 * @return The character at the reached node or the DELIMITER ('\0') if the node
 * is not a leaf node.
 */
char get_character(WackyTreeNode* tree, bool boolean_array[], int array_size) {
    // TODO: Complete this function.

    if (array_size == 0 || tree == NULL){
        return '\0';
    }
   
    WackyTreeNode* cur = tree;
    for (int i = 0; i < array_size; ++i){
        if (cur == NULL){
            return '\0';
        }
        
        if (boolean_array[i] == true){
            if (cur->right == NULL){
                return '\0';
            }
            cur = cur->right; 
        }

        if (boolean_array[i] == false){
            if (cur->left == NULL){
                return '\0';
            }
            cur = cur->left; 
        }

    }
    if (cur->left == NULL && cur->right == NULL){
        return cur->val;
    }

    
    return '\0';
}

/**
 * Given a binary tree, this function frees the memory associated with the
 * entire tree.
 *
 * @param tree Pointer to the root of the binary tree to be freed.
 */



void free_tree(WackyTreeNode* tree) {
    if (tree == NULL){
        free(tree);
        return;
    }


    free_tree(tree->left);
    free_tree(tree->right);

    free(tree);
    
}
