/**
 * Exercise 7 - Quick Sort
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * Any clarifications and corrections will be posted to Piazza so please keep an
 * eye on the forum!
 *
 * Unauthorized distribution or posting is strictly prohibited. You must seek
 * approval from course staff before uploading and sharing with others.
 */
#include "wackylist.h"

/**
 * Given the head of a linked list and a comparison function, this function
 * sorts the linked list in ascending order and returns the head of the new
 * linked list.
 *
 * @param head Pointer to the head of the linked list to be sorted.
 * @param compare_function Pointer to the comparison function used for sorting.
 * The function should return a negative value if the first argument is less
 * than the second, zero if they are equal, and a positive value if the first
 * argument is greater than the second.
 * @return Pointer to the head of the new sorted linked list.
 */
LinkedListNode* sort_linked_list(LinkedListNode* head, int (*compare_function)(const void*, const void*)) {
    if (head == NULL || head->next == NULL) {
        return head;  // There's nothing to sort.
    }

    // This is the new head we will write to.
    LinkedListNode* new_head = NULL;

    // Perform insertion sort until the old list is empty.
    while (head != NULL) {
        // Remove the head of the list.
        LinkedListNode* current_node = head;
        head = head->next;

        // Find the position in the new list & add the node.
        if (new_head == NULL) {
            current_node->next = NULL;
            new_head = current_node;
        } else if (compare_function(&current_node, &new_head) <= 0) {
            current_node->next = new_head;
            new_head = current_node;
        } else {
            LinkedListNode* prev = new_head;
            while (prev != NULL) {
                if (prev->next == NULL) {
                    prev->next = current_node;
                    current_node->next = NULL;
                    break;
                } else if (compare_function(&current_node, &prev->next) <= 0) {
                    current_node->next = prev->next;
                    prev->next = current_node;
                    break;
                } else {
                    prev = prev->next;
                }
            }
        }
    }

    return new_head;
}
