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
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedListNode LinkedListNode;
struct LinkedListNode {
    char utorid[32];
    char major[64];
    double gpa;

    LinkedListNode* next;
};

void generate_random_utorid(char* dest, int characters, int numbers) {
    int idx = 0;

    for (int i = 0; i < characters; i++) {
        dest[idx++] = (char)((rand() % 26) + 'a');
    }

    for (int i = 0; i < numbers; i++) {
        dest[idx++] = (char)((rand() % 10) + '0');
    }

    dest[idx] = '\0';
}

void generate_random_major(char* dest) {
    int value = rand() % 3;
    if (value == 0) {
        strcpy(dest, "Computer Science");
    } else if (value == 1) {
        strcpy(dest, "Mathematics");
    } else if (value == 2) {
        strcpy(dest, "Statistics");
    }
}

double generate_random_gpa() {
    return (((double)rand()) / ((double)RAND_MAX)) * 4.0;
}

void print_linked_list(LinkedListNode* head) {
    if (head == NULL) {
        return;
    }

    printf("ID: %s\n", head->utorid);
    printf("\t%s (%.3f)\n\n", head->major, head->gpa);
    print_linked_list(head->next);
}

void free_linked_list(LinkedListNode* head) {
    LinkedListNode* next;
    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    }
}