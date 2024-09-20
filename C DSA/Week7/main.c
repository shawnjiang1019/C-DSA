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
#include <time.h>

//#include "wackybadsort.c"
#include "wackygoodsort.c"
// When you're ready to test your code, change the import above to "wackygoodsort.c"

#define SAMPLE_SIZE 100000

/**
 * 
 * 
 * 
 * Given the addresses of two LinkedListNode*, this function returns an integer
 * value that sorts the nodes in ascending order by major, GPA, and finally
 * UTORid.
 *
 * @param void_ptr_a Pointer to the first LinkedListNode* address.
 * @param void_ptr_b Pointer to the second LinkedListNode* address.
 * @return A negative value if the first node is less than the second, zero if
 * they are equal, and a positive value if the first node is greater than the
 * second.
 */
int compare_nodes(const void* void_ptr_a, const void* void_ptr_b) {
    LinkedListNode* node_a = *((LinkedListNode**)void_ptr_a);
    LinkedListNode* node_b = *((LinkedListNode**)void_ptr_b);

    // Compare Majors first.
    int majorCompare = strcmp(node_a->major, node_b->major);
    if (majorCompare != 0) {
        return majorCompare;
    }

    // Compare GPAs second.
    if (node_a->gpa > node_b->gpa) {
        return 1;
    } else if (node_a->gpa < node_b->gpa) {
        return -1;
    }

    // Compare IDs last.
    return strcmp(node_a->utorid, node_b->utorid);
}

int main() {
    // This is a random seed. Keeping this constant means that random
    // numbers generated from this seed will also remain constant.
    srand(31415);

    // Allocate SAMPLE_SIZE different LinkedListNodes.
    LinkedListNode* head = NULL;
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        LinkedListNode* new_node = malloc(sizeof(LinkedListNode));
        if (new_node == NULL) {
            printf("Sorry, not enough memory!\n");
            exit(1);
        }

        // Fill the node with random data.
        generate_random_utorid(new_node->utorid, 7, 3);
        generate_random_major(new_node->major);
        new_node->gpa = generate_random_gpa();
        new_node->next = head;
        head = new_node;
    }

    time_t start_time;
    time(&start_time);

    // Sort the list.
    printf("Beginning to sort ...\n");
    head = sort_linked_list(head, compare_nodes);

    time_t end_time;
    time(&end_time);

    time_t elapsed_time = end_time - start_time;
    printf("Sorting the list took %ld seconds ...\n", elapsed_time);

    // You have access to print_linked_list() to check if the sorting worked!
    // print_linked_list(head); // NOTE: Uncomment this line if needed.

    // Free the list.
    free_linked_list(head);
    return 0;
}
