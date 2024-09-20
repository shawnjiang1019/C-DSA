/**
 * Exercise 3 - Arrays
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * Any clarifications and corrections will be posted to Piazza so please keep an
 * eye on the forum!
 *
 * Unauthorized distribution or posting is strictly prohibited. You must seek
 * approval from course staff before uploading and sharing with others.
 */

// No additional imports are allowed. You can make helper functions if you wish.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// ===========================================================================
// DO NOT CHANGE ANY 'ifndef' AND 'endif' MACROS.
// ===========================================================================
#ifndef ERROR
#define ERROR 0.000001
#endif

/**
 * Function: marcelonacci
 * ----------------------
 * Fill an array with values in a Marcelonacci sequence.
 *  A_n = A_n-1 + alpha * (A_n-2 + A_n-3)
 *
 * The first 3 numbers in the array is the starting sequence.
 *
 * Constraints:
 *  - vals in arr[0:3] >= 0 (starting sequence values)
 *  - len >= 3
 *  - alpha != 0
 *
 * arr: the array to be filled based on the Marcelonacci sequence
 * len: the length of the array
 * alpha: the scaling factor of the Marcelonacci sequence
 */
void marcelonacci(double arr[], int len, double alpha) {
    // TODO: Implement this function.

    for (int i = 3; i < len; ++i){
        arr[i] = arr[i - 1] + alpha * (arr[i - 2] + arr[i - 3]);
    }

    return;
}

/**
 * Function: is_close_enough
 * -------------------------
 * Two doubles are considered close enough if the difference between them is
 * within ERROR margin.
 *
 * a: the first double to compare
 * b: the second double to compare
 * returns: a boolean of whether or not both doubles are within margin
 */
bool is_close_enough(double a, double b) {
    // NOTE: This function is already implemented for you.
    double c = a - b;
    return c <= ERROR && c >= -ERROR;
}

/**
 * Function: last_close_index_of
 * -----------------------------
 * Search an array of numbers and return the index of the last occurrence of
 * another given sub-array.
 *
 * NOTE: Two subarrays are considered close to each other if they have values
 * "close enough" to the other's. This comparison MUST be done with the given
 * is_close_enough(a, b) function.
 *
 * If the array to find cannot be matched, return -1 instead.
 *
 * arr_to_search: the array to search
 * search_len: the length of the array to search
 * arr_to_find: the array to find
 * find_len: the length of the array to find
 * returns: the last index of arr_to_find in arr_to_search
 */
int last_close_index_of(double arr_to_search[], int search_len,
                        double arr_to_find[], int find_len) {
    // TODO: Implement this function.
    int index = 0;
    int count;

    if (find_len > search_len){
        return -1;
    }

    for (int i = search_len - 1; i > find_len - 1; i--){
        count = 0;
        for (int j = 0; j < find_len - 1; ++j){
            if (!is_close_enough(arr_to_search[i - j], arr_to_find[find_len - 1 - j])){
                break;
            } else {
                count++;
            }

            if (count == find_len - 1){
                return i - j - 1;
            }
        }
    }

    return -1;
}

// ===========================================================================
// DO NOT CHANGE ANY 'ifndef' AND 'endif' MACROS.
// These macros help ensure your parts of your code does not conflict with the
// automarker. Changing them will result in your code not compiling and you
// receiving a 0 for the entire assignment.
// ===========================================================================
#ifndef __testing__

#define MARCELO_ARR_LEN 6

int main() {
    // Create array and initialize first 3 values.
    double marcelo_arr[MARCELO_ARR_LEN];
    marcelo_arr[0] = 0.3;
    marcelo_arr[1] = 0.5;
    marcelo_arr[2] = 0.4;

    // Compute Marcelonacci sequence in the array.
    marcelonacci(marcelo_arr, MARCELO_ARR_LEN, 0.314);

    // Compare array with expected results.
    double expected_marcelo_arr[MARCELO_ARR_LEN] = {0.3,    0.5,    0.4,
                                                    0.6512, 0.9338, 1.2638768};
    for (int i = 0; i < MARCELO_ARR_LEN; i++) {
        if (!is_close_enough(marcelo_arr[i], expected_marcelo_arr[i])) {
            printf("Expected %f at marcelo_arr[%d],  but got %f\n",
                   expected_marcelo_arr[i], i, marcelo_arr[i]);
            exit(1);
        }
    }

    printf("marcelonacci() test case passed.\n");

    // Create arrays to search and find.
    double arr_to_search[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double arr_to_find[3] = {6, 7.000000001, 8};

    // Search. Then compare results.
    int idx = last_close_index_of(arr_to_search, 10, arr_to_find, 3);
    int expected_idx = 5;
    if (idx != expected_idx) {
        printf("Expected to find array at %d, got %d\n", expected_idx, idx);
        exit(1);
    }

    printf("last_close_index_of() test case passed.\n");
    return 0;
}

#endif
