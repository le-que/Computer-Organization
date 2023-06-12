/**
 * @file tl04.c
 * @author Que Le
 * @brief Command-line argument & string parsing logic
 * @date 2021-04-21
 */

// DO NOT MODIFY THE INCLUDE(s) LIST
#include <string.h>
#include <stdio.h>
#include "tl04.h"

/*

The following macros and struct are defined in tl04.h. You will need to use these:

#define FAILURE 1
#define SUCCESS 0

struct ascii_image {
    int width;      // The number of columns in the ASCII image. Must be at least 1.
    int height;     // The number of rows in the ASCII image. Must be at least 1.
    char *name;     // The name of the ASCII image. This must be non-null, and must point to a deep copy that was allocated specifically for this struct.
    char *data;     // The image's data, which is a non-null, 1-dimensional char array of size width*height. Note: despite being a char*, this is not a string.
};

*/

/** @brief A debug function that prints an image's data.
 * 
 * This function is already provided for you. You can use this function to help debug your code.
 * @param image The image to display.
 */
void print_image(struct ascii_image *image)
{
    printf("Image name: %s\n", image->name);
    for (int i = 0; i < image->height * image->width; i++)
    {
        printf("%c", image->data[i]);
        if (i % image->width == image->width - 1)
            printf("\n");
    }
}

/**
 * @brief Write a character to an image using row and column coordinates.
 * 
 * If image is NULL or row is not within [0, image->height - 1], or row is not within [0, image->width - 1], then return FAILURE. (You can assume image->data is not NULL, as long as image is not NULL.)
 * Otherwise, write the character c to the requested coordinates in image->data, and return NULL.
 * Since image->data is a 1D array that represents a 2D image, you should use a calculation similar to the OFFSET macro from Homework 8.
 *
 * Examples:
 *
 * Assume that 'img' is a pointer to a struct ascii_image with width=3, height=3, and its data looks like this:
 * 
 *      OOO
 *      OOO
 *      OOO
 * 
 * After calling set_character(img, 2, 1, 'C'), SUCCESS will be returned and the image will look like this:
 * 
 *      OOO
 *      OOO
 *      OCO
 * 
 * Then, after calling set_character(img, 1, 0, 'A'), SUCCESS will again be returned and the image will look like this:
 * 
 *      OOO
 *      AOO
 *      OCO
 * 
 * Calling set_character(img, 0, 3, 'B') or set_character(img, 4, 2, 'D') will return FAILURE and not modify the image at all.
 * set_character(NULL, 0, 0, 'X') will also return FAILURE. set_character(img, 0, 0, 'X') will return FAILURE if img->data is NULL.
 *
 * @param image A struct ascii_image that should be modified. See tl04.h for the definition of this struct.
 * @param row The row where the character will be drawn. Must be in [0, image->height - 1].
 * @param col The column where the character will be drawn. Must be in [0, image->width - 1].
 * @param c The character that will be drawn to the image. 
 * @return returns FAILURE if image is NULL, or if row or col is out-of-bounds; returns SUCCESS otherwise
 */
int set_character(struct ascii_image *image, int row, int col, char c)
{
    if(image == NULL || row < 0 || col < 0 || row > (image -> height - 1) || col > (image->width - 1)) {
        return FAILURE;
    }
    image->data[row * image->width + col] = c;
    return SUCCESS;
}

/**
* @brief Draw a straight line between two specified points to the image inclusive of the given points. 
* If the provided image is NULL return FAILURE. (You may assume that if image is not NULL, then image->data is also not NULL)
* Otherwise, use the two row/column pairs to draw a line between them. If any of the coordinates are less than 0, return FAILURE. 
* If the two points provided do not create a vertical or horizontal straight line, then return FAILURE. It is highly reccomended
* that you use the previously implemented set character method place the characters. If any pixel of the line is out-of-bounds, 
* simply do not draw it. You must not draw anything out-of-bounds. For this reason, it is HIGHLY RECOMMENDED to use set_character, 
* which refuses to draw anything if the provided coordinates is out-of-bounds.* Also, draw_line should still return SUCCESS 
* even if some or all of the line is out-of-bounds or if the two given points are the same. 
* 
* Note: There is no guarantee that the first row or column will be smaller or larger than the sceond. It is recommended you write
* the methods as if you knew one was larger than the other and implement a swap helper method to guarantee this contraint.
*
* Examples:
 * 
 * Assume that 'img' is a pointer to a struct ascii_image with width=7, height=5, and its data looks like this:
 * 
 *      .......
 *      .......
 *      .......
 *      .......
 *      .......
 * 
 * After calling draw_line(img, 1, 1, 1, 4, 'X'), SUCCESS will be returned and the image will look like this:
 * 
 *      .......
 *      .XXXX..
 *      .......
 *      .......
 *      .......
 *      
 * Then, after calling draw_line(img, 4, 1, 1, 1, 'A') and draw_line(img, 0, 0, 0, 0, 'B'), the image looks like this:
 * 
 *      B......
 *      .AXXX..
 *      .A.....
 *      .A.....
 *      .A.....
 * @param image A struct ascii_image that should be modified. See tl04.h for the definition of this struct.
 * @param row1 The starting row of the line
 * @param col1 The starting col of the line
 * @param row2 The row of the endpoint of the line
 * @param col2 The col of the endpoint of the line
 * @param c The character to use when drawing the line.
 * @return Returns FAILURE if the image is NULL, or if any coordinate point is less than 0, or if the points do not make a straight line. Otherwise, returns SUCCESS.
*/
int draw_line(struct ascii_image *image, int row1, int col1, int row2, int col2, char c)
{
    if(image == NULL || row1 < 0 || col1 < 0 || row2 < 0 || col2 < 0) {
        return FAILURE;
    }
    if(row1 == row2 && col2 == col1) {
        set_character(image, row1, col1, c);
    }
    if (row1 != row2) {
        if(col2 == col1) {
            if(row1<row2) {
                for(int i = row1; i<=row2; i++) {
                    set_character(image, i, col1, c);
                }
            } else {
                for(int i = row2; i<=row1; i++) {
                    set_character(image, i, col1, c);
                }
            }
        } else {
            return FAILURE;
        }
    }
    if (col1 != col2) {
        if(row1 != row2) {
            return FAILURE;
        } else {
            if(col1<col2) {
                for(int i = col1; i<=col2; i++) {
                    set_character(image, row1, i, c);
                }
            } else {
                for(int i = col2; i<=col1; i++) {
                    set_character(image, row1, i, c);
                }
            }
        }
    }
    return SUCCESS;
}

/**
 * Given two addresses of integers, swaps the values at the addresses. Helper method used in draw_line()
 * @param num1 address of first int
 * @param num2 address of second int
 * @return SUCCESS after completion
 * 
 **/
int swap(int *num1, int *num2)
{
    int tem = *num1;
    *num1 = *num2;
    *num2 = tem;
    return SUCCESS;
}


/**
* @brief Draw a diagonal line between two specified points to the image inclusive of the given points. 
* If the provided image is NULL return FAILURE. (You may assume that if image is not NULL, then image->data is also not NULL.)
* Otherwise, use the two row/column pairs to draw a line between them. If any of the coordinates are less than 0, return FAILURE. 
* If the distance between the two points do not have equal height or width, then return FAILURE. If any pixel of the line is out-of-bounds, 
* simply do not draw it. You must not draw anything out-of-bounds. For this reason, it is HIGHLY RECOMMENDED to use set_character, 
* which refuses to draw anything if the provided coordinates are out-of-bounds. Also, draw_line should still return SUCCESS 
* even if some or all of the line is out-of-bounds or if the two given points are the same. 
* 
* Note: Your code should be able to work for any 2 valid points.
* (Meaning it can draw in any direction as long as the change in row and change in col are equal.) 
*
* Examples:
 * 
 * Assume that 'img' is a pointer to a struct ascii_image with width=7, height=5, and its data looks like this:
 * 
 *      .......
 *      .......
 *      .......
 *      .......
 *      .......
 * 
 * After calling draw_diagonal_line(img, 0, 0, 2, 2, 'X'), SUCCESS will be returned and the image will look like this:
 * 
 *      X......
 *      .X.....
 *      ..X....
 *      .......
 *      .......
 *      
 * Then, after calling draw_diagonal_line(img, 0, 0, 0, 0, 'B') and draw_diagonal_line(img, 3, 2, 1, 0, 'A'), the image looks like this:
 * 
 *      B......
 *      AX.....
 *      .AX....
 *      ..A....
 *      .......
 * @param image A struct ascii_image that should be modified. See tl04.h for the definition of this struct.
 * @param row1 The starting row of the line
 * @param col1 The starting col of the line
 * @param row2 The row of the endpoint of the line
 * @param col2 The col of the endpoint of the line
 * @param c The character to use when drawing the line.
 * @return Returns FAILURE if the image is NULL, or if any coordinate point is less than 0, or if the points do not make a straight line. Otherwise, returns SUCCESS.
*/
int draw_diagonal_line(struct ascii_image *image, int row1, int col1, int row2, int col2, char c)
{
    // TODO: IMPLEMENT THIS FUNCTION! SEE .pdf FOR DETAILS

    // These are just to turn off compiler errors initially
    // Please delete once you have implemented the function
    if(image == NULL || row1 < 0 || col1 < 0 || row2 < 0 || col2 < 0) {
        return FAILURE;
    }
    if(abs(row2-row1) != abs(col2-col1)) {
        if (abs(row1-row2) != abs(col1-col2)) {
            return FAILURE;
        }
    }
    if(row1 < row2) {
        if (col1<col2) {
            int i = row1;
            int j = col1;
            while (i <= row2) {
                while (j<=col2) {
                    set_character(image, i, j, c);
                    i++;
                    j++;
                }
            }
        } else {
            int i = row1;
            int j = col1;
            while (i <= row2) {
                while (j>=col2) {
                    set_character(image, i, j, c);
                    i++;
                    j--;
                }
            }
        }
    } else {
        if (col1<col2) {
            int i = row1;
            int j = col1;
            while (i >= row2) {
                while (j<=col2) {
                    set_character(image, i, j, c);
                    i--;
                    j++;
                }
            }
        } else {
            int i = row1;
            int j = col1;
            while (i >= row2) {
                while (j>=col2) {
                    set_character(image, i, j, c);
                    i--;
                    j--;
                }
            }
        }
    }
    return SUCCESS;

}


/**
 * @brief Using the provided height, width, and name, make a new image with these parameters and fill the already allocated ascii_image's data with "." characters.
 *
 * The provided height and width must be at least 1, and the provided name must be non-NULL. If any of these conditions are not met, return NULL without allocating anything.
 * Otherwise, you should create and return a new struct ascii_image.
 *
 * @param height The height of the image. This must be stored in the created ascii_image struct, and should be used when allocating the image data array.
 * @param width The width of the image. This must be stored in the created ascii_image struct, and should be used when allocating the image data array.
 * @param name The name of the image. This must NOT be assigned directly to the image; you MUST create a deep-copy of this name, so use the *copy pointer we have malloc'd to do this.
 * @return Returns NULL if the height or width is less than 1, if the name is NULL, or if there was a malloc failure. Returns a valid ascii_image pointer otherwise.
 */
struct ascii_image *create_image(int height, int width, char *name) {
    // TODO: IMPLEMENT THIS FUNCTION! SEE .pdf FOR DETAILS
    // Write a conditional here that checks if all of the parameters are valid.

    // YOUR CODE HERE
    if (height < 1 || width <1 || name == NULL) {
        return NULL;
    }
    // Malloc code given to you
    struct ascii_image *image = malloc(sizeof(struct ascii_image));
    if (!image)
        return NULL;
    char *copy = malloc(strlen(name) + 1);
    if (!copy)
    {
        free(image);
        return NULL;
    }
    char *data = malloc(height * width);
    if (!data)
    {
        free(image);
        free(copy);
        return NULL;
    }
    // Set all of the image struct's values here.
    // Also fill image->data with "." characters.
    // YOUR CODE HERE
    char *c = ".";
    image->height = height;
    image->width = width;
    image->data = data;
    for(int i = 0; i < height; i++) {
         for(int j= 0; j < width; j++) {
             image->data[j * width + i] = *c;
        }
    }
    
    strncpy(copy, name, strlen(name)+1);
    image->name = copy;

    return image;    // Don't forget to replace this!
}

/**
 * @brief Append the extension string to the end of the name of the provided ascii_image.
 *
 * If image or extension is NULL, or if there is a malloc/realloc failure, return FAILURE. image->name MUST remain unmodified. (You can assume that image->name is not NULL, as long as image is not NULL.)
 * Otherwise, modify image->name so that it points to an allocation with the original image name and the extension concatenated together, and return SUCCESS.
 * You must only copy the characters from the extension string; you should not assign the image's name to be the extension. Also, you should not attempt to free the extension string.
 * There must be NO MEMORY LEAKS. If you allocate new space for the name+extension, make sure to deallocate the name's old space once you're done using it. (Given to you).
 *
 * You may use ANY of the functions from string.h in your code. Some of these functions will be extremely useful!
 *
 * Examples:
 *
 * Assume that 'img' is a pointer to a struct ascii_image, and assume that its name is the following string allocated on the heap: {'a', 'r', 't', '\0'}, AKA "art".
 * After calling add_extension(img, ".png"), add_extension should return SUCCESS (assuming no mallocs fail).
 * Additionally, img->name should point to a new or expanded allocation with the following string: {'a', 'r', 't', '.', 'p', 'n', 'g', '\0'}, AKA "art.png".
 * Note that the extension can be any length. Calling add_extension(img, ".tar.gz") should then turn the image's name into "art.png.tar.gz".
 * add_extension(NULL, ".jpg") or add_extension(img, NULL) should both return FAILURE. Also, if a malloc fails, you should return FAILURE as well.
 *
 * @param image The image whose name should be extended. If add_extension is successful, image->name should have the extension appended to it.
 * @param extension The string that should be appended to the image's name.
 * @return Returns FAILURE if image or extension if NULL, or if there was a malloc/realloc failure. Otherwise, the image's name is extended and this function returns SUCCESS.
 */
int add_extension(struct ascii_image *image, char *extension) {
    // TODO: IMPLEMENT THIS FUNCTION! SEE .pdf FOR DETAILS
    // Write a conditional here that checks if all of the parameters are valid.

    // YOUR CODE HERE
    if (image == NULL || extension == NULL) {
        return FAILURE;
    }

    // Allocate space on the heap for our new image name. (Given to you.)
    char *concat = malloc(strlen(image->name) + strlen(extension) + 1);
    if (!concat){
        return FAILURE;
    }


    // Here you will combine the extension and the allocated image name.
    // YOUR CODE HERE
    strcpy(concat, image->name);
    strcat(concat, extension);

    // Free allocated memory. (Given to you.) Then, reassign the name of the image to be the new name.
    free(image->name);

    // YOUR CODE HERE
    image->name = concat;

    return SUCCESS;
}
