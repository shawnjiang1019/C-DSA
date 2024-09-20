/**
 * Exercise 4 - Strings & POinters
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * Any clarifications and corrections will be posted to Piazza so please keep an
 * eye on the forum!
 *
 * Unauthorized distribution or posting is strictly prohibited. You must seek
 * approval from course staff before uploading and sharing with others.
 */

// #############################################################################
// # READ THIS! READ THIS! READ THIS!
// #############################################################################
// No additional imports are allowed. You can make helper functions if you wish.
// Importing other header files will result in an automatic fail.
// Using any array notations "[]" outside of main() will result in an automatic fail.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int find_len(char *string) {
    int len = 0;
    while (*(string + len) != '\0') len++; 
    return len;
}

/**
 * Function: reverse
 * -----------------
 * Reverse a given string in-place. This means that the reversed string should
 * replace the original.
 *
 * string: the string to reverse
 */
void reverse(char* string) {
    // TODO: Complete this function.    
    int len = find_len(string);
    for (int i = 0; i < len / 2; i++) {
        char tmp = *(string + i);
        *(string + i) = *(string + len - i - 1);
        *(string + len - i - 1) = tmp;
    }
    return;
}

/**
 * Function: replace_all
 * -----------------
 * Given a source string, replace all occurrences of a specified substring with
 * another string and write the resulting string to the destination.
 *
 * source: the input string to be replaced
 * dest: the location to write the replaced string to
 * find: the substring to be replaced
 * replace: the string to replace occurrences of "find" with
 */
void replace_all(char* source, char* dest, char* find, char* replace) {
    // TODO: Complete this function.
    int len_source = find_len(source);
    int len_find = find_len(find);
    int len_replace = find_len(replace);
    int len_dest = 0;
    for (int i = 0; i < len_source; i++) {
        bool match = (len_find > 0);
        for (int j = i; j < i + len_find; j++) {
            if (*(source + j) != *(find + j - i)) {
                match = false;
                break;
            }
        }
        if (match) {
            for (int j = 0; j < len_replace; j++, len_dest++) {
                *(dest + len_dest) = *(replace + j);
            }
            i += len_find - 1;
        }
        else {
            *(dest + len_dest++) = *(source + i);
        }
    }
    *(dest + len_dest++) = '\0';
    return;
}

// ===========================================================================
// DO NOT CHANGE ANY 'ifndef' AND 'endif' MACROS.
// These macros help ensure your parts of your code does not conflict with the
// automarker. Changing them will result in your code not compiling and you
// receiving a 0 for the entire assignment.
// ===========================================================================
#ifndef __testing__

void test_reverse() {
    char string[1024] = "Card";
        /*"!dekrow evah yam noitcnuf ruoy ekil skooL ?ylraelc siht daer uoy naC";*/
    
    printf("String: %s\n", string);

    reverse(string);

    // "Can you read this clearly? Looks like your function may have worked!"
    printf("Reversed String: %s\n", string);
}

void test_replace_all() {
    char source[1024] = "the";
    printf("Source: %s\n", source);

    char dest[1024];
    replace_all(source, dest, "the", "dragon");

    // "a quick brown fox jumps over a lazy dog"
    printf("Dest: %s\n", dest);
}

int main() {
    // Testing reverse() function.
    printf("Calling test_reverse() ...\n");
    test_reverse();

    // Testing test_replace_all() function.
    printf("Calling test_replace_all() ...\n");
    test_replace_all();
    return 0;
}

#endif