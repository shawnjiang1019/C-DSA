/**
 * Exercise 11 - Sudoku
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * Any clarifications and corrections will be posted to Piazza so please keep an
 * eye on the forum!
 *
 * Unauthorized distribution or posting is strictly prohibited. You must seek
 * approval from course staff before uploading and sharing with others.
 *
 * Starter code:  (Updated by) Charles Xu, 2024
 *             (Originally by) Mustafa Quraish, 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===========================================================================
// DO NOT CHANGE ANY 'ifndef' AND 'endif' MACROS.
// These macros help ensure your parts of your code does not conflict with the
// automarker. Changing them will result in your code not compiling and you
// receiving a 0 for the entire assignment.
// ===========================================================================
#ifndef __testing__

/**
 * Given a 9x9 Sudoku grid, this function prints out the grid in a format
 * that is easy to view, aiding in debugging or visualization.
 *
 * @param sudoku The 9x9 Sudoku grid to be printed.
 */
void print_sudoku(int sudoku[9][9]) {
    printf("The Sudoku contains:\n");
    printf("+-------+-------+-------+\n");
    for (int j = 0; j < 9; j++) {
        printf("| ");
        for (int i = 0; i < 9; i++) {
            printf("%d ", sudoku[j][i]);
            if (i % 3 == 2) printf("| ");
        }
        printf("\n");
        if (j % 3 == 2) printf("+-------+-------+-------+\n");
    }
}

#endif

/**
 * This function checks if the current Sudoku grid (not necessarily complete)
 * is valid. A Sudoku grid is considered valid if, ignoring the 0s, each row,
 * column, and 3x3 subgrid does not repeat any digits from 1 to 9.
 *
 * @note An incomplete Sudoku grid may be valid if the criteria above is met.
 *
 * @param sudoku The 9x9 Sudoku grid to be checked.
 * @return 1 if the Sudoku is valid, 0 if it's not.
 */




int is_valid_row(int sudoku[9][9], int length, int row) {
    // Create a frequency array 
    int result[9] = {0}; 
    
    // Count the frequency of each number in the row
    for (int i = 0; i < length; i++) {
        result[sudoku[row][i] - 1]++;
    }
    
    // Check to see that no value appears more than once
    for (int i = 0; i < 9; i++) { 
        if (result[i] > 1) {
            return 0;
        }
    }
    return 1;
}


int is_valid_column(int sudoku[9][9], int col) {
    // Create a frequency array
    int result[9] = {0};

    // Count the frequency of each number in the column
    for (int i = 0; i < 9; i++) {
        result[sudoku[i][col] - 1]++;
    }

    // Check that each number appears at most once
    for (int i = 0; i < 9; i++) {
        if (result[i] > 1) {
            return 0; // Not a valid column
        }
    }
    return 1; // Valid column
}


int is_valid_grid(int sudoku[9][9], int row, int col) {
    // Frequency array to keep track of uniqueness
    int result[9] = {0};
    for (int i = row; i < row + 3; ++i) {
        for (int j = col; j < col + 3; ++j) {
            if (sudoku[i][j] != 0) {
                result[sudoku[i][j] - 1]++;
                if (result[sudoku[i][j] - 1] > 1) {
                    return 0; 
                }
            }
        }
    }
    return 1;
}





int is_valid_sudoku(int sudoku[9][9]) {
    // Check each row
    for (int i = 0; i < 9; i++) {
        if (is_valid_row(sudoku, 9, i) == 0) {
            return 0; 
        }
    }
    
    for (int j = 0; j < 9; j++) {
        if (is_valid_column(sudoku, j) == 0) {
            return 0; 
        }
    }
    
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            if (is_valid_grid(sudoku, i, j) == 0) {
                return 0; 
            }
        }
    }
    
    return 1;
}


/**
 * Given a (possibly partially) completed Sudoku grid, this function attempts
 * to solve the Sudoku. The `sudoku` array is changed to contain the solution
 * if one exists. None of the digits in the input grid should be changed.
 *
 * @note: Empty spots in the grid are denoted with 0s.
 *
 * @param sudoku The 9x9 Sudoku grid to be solved.
 * @return 1 if the Sudoku was solved successfully and the `sudoku` array is
 * updated, 0 if it's not possible to solve the Sudoku, and the input `sudoku`
 * array remains unchanged in this case.
 */
int solve_sudoku(int sudoku[9][9]) {
    
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (sudoku[row][col] == 0) { 
                // try all numbers
                for (int num = 1; num <= 9; num++) {
                    sudoku[row][col] = num; 
                    // Check if the number placement is valid
                    if (is_valid_sudoku(sudoku) == 1) {
                        if (solve_sudoku(sudoku) == 1) {
                            return 1; 
                        }
                    }
                    //Undo the placement i guess
                    sudoku[row][col] = 0;
                }
                return 0; 
            }
        }
    }
    return 1; // Puzzle is solved
}

// ===========================================================================
// DO NOT CHANGE ANY 'ifndef' AND 'endif' MACROS.
// These macros help ensure your parts of your code does not conflict with the
// automarker. Changing them will result in your code not compiling and you
// receiving a 0 for the entire assignment.
// ===========================================================================
#ifndef __testing__

int main() {
    int sudoku_grid[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    print_sudoku(sudoku_grid);

    int solved = solve_sudoku(sudoku_grid);

    printf("\nsolve_sudoku() return value: %d\n\n", solved);

    /* Look at the handout to see the solution for this! */
    print_sudoku(sudoku_grid);

    return 0;
}

#endif