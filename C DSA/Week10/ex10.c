/**
 * Exercise 10 - Floo-Fill
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
 *                (Updated by) Mustafa Quraish, 2020
 *             (Originally by) Francisco Estrada, 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the image size we are using. This will remain constant.
#define SIZEX 50
#define SIZEY 50

// Include the functions to read / write the images
#include "imgUtils.c"

/**
 * Given the input image array representing the elevation maps of a newly
 * discovered planet and the initial position of the rover, this function finds
 * and marks the connected region around the initial position. Each element of
 * the input array has values 0-255 inclusive, where 0 represents black and 255
 * represents white.
 *
 * @note Because of how 2D arrays are stored in memory, we need to be careful
 * when trying to access the correct pixel. PGM images use the math convention
 * where the first index is the ROW, and the second index is the COLUMN. So, to
 * get the color of pixel (x, y), you will need to do: input[y][x]
 *
 * @param input The input image array representing the elevation maps.
 * @param px The initial position of the rover (x-coordinate).
 * @param py The initial position of the rover (y-coordinate).
 * @param output The output image array to store the marked connected region.
 * Output is initially empty (all pixels have colour 0).
 */

int search_above(unsigned char input[SIZEY][SIZEX], int px, int py, unsigned value, unsigned char output[SIZEY][SIZEX]){
    
    if(input[py - 1][px] == value && output[py - 1][px] != 255){
        return 1;
    } else {
        return 0;
    }
}

//Might be accessing unwanted memory.
int search_below(unsigned char input[SIZEY][SIZEX], int px, int py, unsigned char value, unsigned char output[SIZEY][SIZEX]){
    if(input[py + 1][px] == value && output[py + 1][px] != 255){
        return 1;
    } else {
        return 0;
    }
}

int search_right(unsigned char input[SIZEY][SIZEX], int px, int py, unsigned char value, unsigned char output[SIZEY][SIZEX]){
    if(input[py][px + 1] == value && output[py][px + 1] != 255){
        return 1;
    } else {
        return 0;
    }
}

int search_left(unsigned char input[SIZEY][SIZEX], int px, int py, unsigned char value, unsigned char output[SIZEY][SIZEX]){
    if(input[py][px - 1] == value && output[py][px - 1] != 255){
        return 1;
    } else {
        return 0;
    }
}

void find_connected_region(unsigned char input[SIZEY][SIZEX], int px, int py, unsigned char output[SIZEY][SIZEX]) {
    //Check for invalid (outside of the array)
    if (px < 0 || py < 0 || px >= SIZEX || py >= SIZEY) {
        return;
    }
    unsigned char value = input[py][px];

    output[py][px] = 255;
    if (py > 0 && py < SIZEY){
        
        if (search_above(input, px, py, value, output) == 1){
            find_connected_region(input, px, py - 1, output);
        }
    }

    
    if (py < SIZEY - 1 && py >= 0){
        
        if (search_below(input, px, py, value, output) == 1){
            find_connected_region(input, px, py + 1, output);  
        }
    }
    
    if (px < SIZEX - 1 && py >= 0){
        
        if (search_right(input, px, py, value, output) == 1){
            find_connected_region(input, px + 1, py, output);
        }
    }
    
    if (px > 0 && px < SIZEX){
        
        if (search_left(input, px, py, value, output) == 1){
            find_connected_region(input, px - 1, py, output);
        }
    }
    
    /**
     * Your task is to find all *connected* pixels that have the same elevation
     * as the one at (px,py) in `input`, and mark these pixels on `output`.
     *
     * For instance, if the initial coordinates are (px=5, py=10), your program
     * must check the elevation at input[10][5], then set the colour of all
     * connected pixels to white (255) in the levelset_map.
     *
     * Example with a very tiny sample image:
     *
     * input:
     *                       1    1    1    2    3    3
     *                       1    1    2    3    3    4
     *                       1    2    2    2    4    3
     *                       1    1    1    2    4    3
     *                       1    1    2    2    3    3
     *                       4    4    4    4    2    2
     *
     *
     * If we call the function with the `input` above, and initial coordinates
     * (1,1), it should produce
     *
     * output:
     *
     *                      255  255  255   0    0    0
     *                      255  255   0    0    0    0
     *                      255   0    0    0    0    0
     *                      255  255  255   0    0    0
     *                      255  255   0    0    0    0
     *                       0    0    0    0    0    0
     *
     * If we call the function with initial coordinates (4, 0) it will produce
     *
     * output:
     *
     *                       0    0    0    0   255  255
     *                       0    0    0   255  255   0
     *                       0    0    0    0    0    0
     *                       0    0    0    0    0    0
     *                       0    0    0    0    0    0
     *                       0    0    0    0    0    0
     *
     * In effect, this function extracts the connected region in the image
     * array with the same elevation as that of the pixel at (px, py).
     *
     * NOTE: A pixel can be 'connected' to it's it's 4 neighbours above, below,
     *       to the left and right of it, if they have the same colour. In
     *       particular, we will NOT count pixels along the diagonal. Carefully
     *       look at the examples above to make sure you understand this.
     *
     * - You should NOT change the contents of the input array.
     *
     * There are many ways to approach this problem, you're free to choose
     * whatever makes more sense to you. Make reasonable assumptions where
     * needed, and solve the problem!
     */




    return;  // Update the `output` array as needed before returning.
}

// ===========================================================================
// DO NOT CHANGE ANY 'ifndef' AND 'endif' MACROS.
// These macros help ensure your parts of your code does not conflict with the
// automarker. Changing them will result in your code not compiling and you
// receiving a 0 for the entire assignment.
// ===========================================================================
#ifndef __testing__

int main() {
    unsigned char input[SIZEY][SIZEX];
    unsigned char output[SIZEY][SIZEX];

    // Initialize output array to have colour black (0)
    for (int y = 0; y < SIZEY; y++) {
        for (int x = 0; x < SIZEX; x++) {
            output[y][x] = 0;
        }
    }

    // --------------------------------------------------------------------------
    //                      Testing with floo-region-1.pgm
    //                     Output file will be output-1.pgm
    // --------------------------------------------------------------------------

    // Read the selected input image into input[][]
    readPGM("floo-region-1.pgm", &input[0][0]);

    printf("Calling find_connected_region() on image 1...\n");
    find_connected_region(input, 24, 16, output);  // Staring position is (24, 16)

    // Write the connected region to the output image
    writePGM("output-1.pgm", &output[0][0]);

    // --------------------------------------------------------------------------
    //                      Testing with floo-region-2.pgm
    //                     Output file will be output-2.pgm
    // --------------------------------------------------------------------------

    // Read the selected input image into input[][]
    readPGM("floo-region-2.pgm", &input[0][0]);

    // Don't forget to reset the output array!
    for (int y = 0; y < SIZEY; y++) {
        for (int x = 0; x < SIZEX; x++) {
            output[y][x] = 0;
        }
    }

    printf("Calling find_connected_region() on image 2...\n");
    find_connected_region(input, 4, 35, output);  // Staring position is (4, 35)

    // Write the connected region to the output image
    writePGM("output-2.pgm", &output[0][0]);

    printf("Done!\n");
    return 0;
}

#endif
