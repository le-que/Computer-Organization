/**
 * @file my_string_suite.c
 * @author Farzam TN a.k.a Unc Zam
 * @brief Testing Suites to HW7 - Spring 2020
 * @date 2020-03-06
 */

// Check Docs
// Tutorial : https://libcheck.github.io/check/doc/check_html/check_3.html
// Check API: https://libcheck.github.io/check/doc/doxygen/html/check_8h.html

// System Headers
#include <stdio.h>
#include <string.h>
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#include "test_utils.h"

// For checking my_string.c array notation
#define NO_ARRAY_NOTATION 2200
#define MY_STRING_C_NOT_FOUND 1
#define MY_STRING_FAILURE 2
#define STRING_H_USED 3
#define STRINGS_H_USED 4

// This is the variable that determines if they used illegal stuff @see whatIsA2110StudentDoingHere()
static int dontReverseEngineerBro = MY_STRING_FAILURE; // TODO: make it const

static void randStringGenerator(char *dest, int length);
static int whatIsA2110StudentDoingHere(void);

/******************************************************************************/
/**************************** my_strlen tests *********************************/
/******************************************************************************/

START_TEST(test_my_strlen_1)
{
    if (dontReverseEngineerBro != NO_ARRAY_NOTATION)
    {
        ck_abort();
    }

    const char *str = "12345";
    const char *backup = str; // pointers should not be changed
    size_t retVal = my_strlen(str);
    ck_assert_ptr_eq(str, backup);
    ck_assert_int_eq(retVal, strlen(str));
}
END_TEST

START_TEST(test_my_strlen_2)
{
    if (dontReverseEngineerBro != NO_ARRAY_NOTATION)
    {
        ck_abort();
    }

    const char *str = "1\0";
    const char *backup = str; // pointers should not be changed

    size_t retVal = my_strlen(str);
    ck_assert_ptr_eq(str, backup);
    ck_assert_int_eq(retVal, strlen(str));
}
END_TEST

START_TEST(test_my_strlen_3)
{
    if (dontReverseEngineerBro != NO_ARRAY_NOTATION)
    {
        ck_abort();
    }

    const char str[] = {'1', '2', '3', '\0', 'Z', 'f'};
    const char *backup = str; // pointers should not be changed
    size_t retVal = my_strlen(str);
    ck_assert_ptr_eq(str, backup);
    ck_assert_int_eq(retVal, strlen(str));
}
END_TEST

START_TEST(test_my_strlen_4)
{
    if (dontReverseEngineerBro != NO_ARRAY_NOTATION)
    {
        ck_abort();
    }

    srand(time(0));
    unsigned long randBoi = rand() % 512;
    if (randBoi < 100)
    {
        // Everybody gotta do at least 155 characters
        randBoi += 155;
    }

    // The only function that doesn't use the random string generator
    char str[randBoi + 1];
    const char *backup = str; // pointers should not be changed

    memset(str, 7, randBoi - 1);
    str[randBoi] = '\0';

    size_t retVal = my_strlen(str);
    ck_assert_ptr_eq(str, backup);
    ck_assert_int_eq(retVal, strlen(str));
}
END_TEST

/******************************************************************************/
/**************************** my_strncmp tests ********************************/
/******************************************************************************/

/**
 * All the strncmp test cases just check for negative, positive, or zero value
 * and the actual value doesn't matter. This is done to adhere to strncmp man page
 * and resources online.
 */

START_TEST(test_my_strncmp_equal)
{
    if (dontReverseEngineerBro != NO_ARRAY_NOTATION)
    {
        ck_abort();
    }

    const char *str1 = "1234/#?\\21tenMo";
    const char *str2 = "1234/#?\\21tenMo";

    const char *backup1 = str1; // pointers should not be changed
    const char *backup2 = str2; // pointers should not be changed

    size_t n = strlen(str1);

    int retVal = my_strncmp(str1, str2, n);
    int correctValSign = strncmp(str1, str2, n);

    if (correctValSign < 0)
    {
        ck_assert_int_lt(retVal, 0);
    }
    else if (correctValSign > 0)
    {
        ck_assert_int_gt(retVal, 0);
    }
    else
    {
        ck_assert_int_eq(retVal, correctValSign);
    }

    ck_assert_ptr_eq(str1, backup1);
    ck_assert_ptr_eq(str2, backup2);
}
END_TEST

START_TEST(test_my_strncmp_null_terminator_in_middle_almost_same)
{
    if (dontReverseEngineerBro != NO_ARRAY_NOTATION)
    {
        ck_abort();
    }

    const char str1[] = {'y', '0', 'h', 'a', '\0', 'Z', 'f'};
    const char *str2 = "yOha";

    const char *backup1 = str1; // pointers should not be changed
    const char *backup2 = str2;

    size_t n = strlen(str1) + 2;

    int retVal = my_strncmp(str1, str2, n);
    int correctValSign = strncmp(str1, str2, n);

    if (correctValSign < 0)
    {
        ck_assert_int_lt(retVal, 0);
    }
    else if (correctValSign > 0)
    {
        ck_assert_int_gt(retVal, 0);
    }
    else
    {
        ck_assert_int_eq(retVal, correctValSign);
    }

    ck_assert_ptr_eq(str1, backup1);
    ck_assert_ptr_eq(str2, backup2);
}
END_TEST

START_TEST(test_my_strncmp_null_terminator_in_middle_different)
{
    if (dontReverseEngineerBro != NO_ARRAY_NOTATION)
    {
        ck_abort();
    }

    // Should return negative
    const char str1[] = {'y', 'e', 'e', 'h', 'a', '\0', 'Z', 'f'};
    const char *str2 = "yeehaBro";

    const char *backup1 = str1; // pointers should not be changed
    const char *backup2 = str2;
    size_t n = strlen(str1) + 1;

    int retVal = my_strncmp(str1, str2, n);
    int correctValSign = strncmp(str1, str2, n);

    if (correctValSign < 0)
    {
        ck_assert_int_lt(retVal, 0);
    }
    else if (correctValSign > 0)
    {
        ck_assert_int_gt(retVal, 0);
    }
    else
    {
        ck_assert_int_eq(retVal, correctValSign);
    }

    ck_assert_ptr_eq(str1, backup1);
    ck_assert_ptr_eq(str2, backup2);
}
END_TEST

START_TEST(test_my_strncmp_random)
{
    if (dontReverseEngineerBro != NO_ARRAY_NOTATION)
    {
        ck_abort();
    }

    // Let's see if student's can hack this test case (without zerodays tho..)

    srand(time(0));
    unsigned int randBoi = rand() % 128;
    if (randBoi < 69) // "nice" - the person shall remain nameless
    {
        randBoi += 100; // Everybody gonna do 100 minimum
    }
    char str1[randBoi + 1];

    randStringGenerator(str1, sizeof(str1));

    char str2[randBoi + 1];
    strncpy(str2, str1, strlen(str1)); // Creating a copy
    str2[randBoi] = '\0';

    str2[5] = 'F'; // Yeah boiii

    const char *backup1 = str1; // pointers should not be changed
    const char *backup2 = str2;

    size_t n = (strlen(str1) / 2) + 1;

    int retVal = my_strncmp(str1, str2, n);
    int correctValSign = strncmp(str1, str2, n);

    if (correctValSign < 0)
    {
        ck_assert_int_lt(retVal, 0);
    }
    else if (correctValSign > 0)
    {
        ck_assert_int_gt(retVal, 0);
    }
    else
    {
        ck_assert_int_eq(retVal, correctValSign);
    }

    ck_assert_ptr_eq(str1, backup1);
    ck_assert_ptr_eq(str2, backup2);
}
END_TEST

/******************************************************************************/
/*************************** my_strncpy tests *********************************/
/******************************************************************************/
START_TEST(test_my_strncpy_basic)
{
    if (dontReverseEngineerBro != NO_ARRAY_NOTATION)
    {
        ck_abort();
    }

    char src[] = {'\0'};
    const char *backup = src; // pointers should not be changed

    char dest[] = {'a', '\0'};
    size_t n = 1;

    char *retVal = my_strncpy(dest, src, n);

    // Checking if dest didn't change
    ck_assert_ptr_eq(retVal, dest);

    ck_assert_ptr_eq(src, backup);

    // Checking if strncmp returns 0
    ck_assert_msg(!strncmp(dest, src, n), "did not overwrite first byte of dest\n");
}
END_TEST

START_TEST(test_my_strncpy_destination_larger)
{
    if (dontReverseEngineerBro != NO_ARRAY_NOTATION)
    {
        ck_abort();
    }

    char *src = "His palms are sweaty, knees weak, arms are heavy ... mom's spaghetti";
    const char *backup = src; // pointers should not be changed

    char dest[100];
    memset(dest, 0, sizeof(dest)); // just to be safe
    size_t n = strlen(src);

    char *retVal = my_strncpy(dest, src, n);

    // Checking if dest didn't change
    ck_assert_ptr_eq(retVal, dest);

    ck_assert_ptr_eq(src, backup);

    // Checking if strncmp returns 0
    ck_assert_msg(!strncmp(dest, src, n), "did not overwrite first byte of dest\n");
    ck_assert_msg(!strncmp(dest + strlen(src), "\0", strlen(dest) - strlen(src)), "Wrote too much in dest\n");
}
END_TEST

START_TEST(test_my_strncpy_random_basic_256)
{
    if (dontReverseEngineerBro != NO_ARRAY_NOTATION)
    {
        ck_abort();
    }

    srand(time(0) - 5000); // 5000 means something Sean

    // Generate random source
    char src[256 + 1];
    const char *backup = src; // pointers should not be changed

    randStringGenerator(src, sizeof(src));

    // No null-termination on dest on purpose
    char dest[256];
    size_t n = strlen(src);
    char *retVal = my_strncpy(dest, src, n);

    // Checking if dest didn't change
    ck_assert_ptr_eq(retVal, dest);

    ck_assert_ptr_eq(src, backup);

    // Checking if strncmp returns 0
    ck_assert_msg(!strncmp(dest, src, n), "did not copy the first 256 characters of src to dest correctly\n");
}
END_TEST

START_TEST(test_my_strncpy_null_terminator_in_middle)
{
    if (dontReverseEngineerBro != NO_ARRAY_NOTATION)
    {
        ck_abort();
    }

    srand(time(0) - 5000); // 5000 means something Sean

    // Generate random source
    char src[256];
    randStringGenerator(src, sizeof(src));
    const char *backup = src; // pointers should not be changed

    // Null terminating in middle to make sure they only copy all the way to null terminator
    150 [src] = 0; // gangsta move

    // No null-termination on dest on purpose
    char dest[256];
    memset(dest, 7, sizeof(256)); // Filling destination with arbitrary val
    size_t n = 256;
    char *retVal = my_strncpy(dest, src, n);

    // Checking if dest didn't change
    ck_assert_ptr_eq(retVal, dest);

    ck_assert_ptr_eq(src, backup);

    // Size should be the same because of n and null terminator position
    ck_assert_int_eq(strlen(dest), strlen(src));

    // Checking if strncmp returns 0
    ck_assert_msg(!strncmp(dest, src, strlen(src) + 1), "did not copy src to dest correctly when null terminator is in middle\n");
}
END_TEST

START_TEST(test_my_strncpy_overwrite)
{
    if (dontReverseEngineerBro != NO_ARRAY_NOTATION)
    {
        ck_abort();
    }

    char src[100];
    randStringGenerator(src, sizeof(src));
    const char *backup = src; // pointers should not be changed

    char dest[100];
    randStringGenerator(dest, sizeof(dest));
    size_t n = strlen(dest);

    char *retVal = my_strncpy(dest, src, n);

    // Checking if dest didn't change
    ck_assert_ptr_eq(retVal, dest);

    ck_assert_ptr_eq(src, backup);

    // Checking if strncmp returns 0
    ck_assert_msg(!strncmp(dest, src, n), "did not overwrite destination completely\n");
}
END_TEST

START_TEST(test_my_strncpy_adv)
{
    if (dontReverseEngineerBro != NO_ARRAY_NOTATION)
    {
        ck_abort();
    }

    char src[77];
    randStringGenerator(src, sizeof(src));
    const char *backup = src; // pointers should not be changed

    // Making sure we overwrite null terminator at the end so strncpy doesn't halt early
    src[strlen(src) - 1] = 'F';

    char dest[100];
    randStringGenerator(dest, sizeof(dest));
    size_t n = strlen(dest) - 1;

    // so everything after src length should be nulled out

    char *retVal = my_strncpy(dest, src, n);

    // Checking if dest didn't change
    ck_assert_ptr_eq(retVal, dest);
    ck_assert_ptr_eq(src, backup);

    // Checking if strncmp returns 0
    ck_assert_msg(!strncmp(dest, src, strlen(src)), "did not overwrite destination completely\n");

    // Making sure students actually read the man page
    // "If the length of src is less than n, strncpy() writes additional null bytes
    // to dest to ensure that a total of n bytes are written."
    char zeroedOut[n - strlen(src)];
    memset(zeroedOut, '\0', sizeof(zeroedOut));
    int test = !strncmp(dest + strlen(src), zeroedOut, n - strlen(src));
    ck_assert_msg(test, "Make sure you read the man page carefully\n");
}
END_TEST

/**
 * @brief Helper function for creating random strings. It will null-terminate like a champ.
 */
// Thanks bro --> https://stackoverflow.com/questions/15767691/whats-the-c-library-function-to-generate-random-string/15768317
static void randStringGenerator(char *buffer, int length)
{
    // C weird syntax once again
    char charset[] = "0123456789"
                     "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // So we don't have to keep adding space for the null terminator
    length--;

    while (length-- > 0)
    {
        // The magic of double, this guy is a flexer
        size_t index = ((double)rand() / RAND_MAX) * (sizeof(charset) - 1);
        *buffer++ = charset[index];
    }

    *buffer = '\0';
}

/**
 * @brief Unc Z's method for checking illegal stuff such as <string.h> and array notation. Man we needed this a long time ago
 *
 * @return int a status code (@see #defines at the top)
 */
static int whatIsA2110StudentDoingHere(void)
{
    FILE *myStringDotC = fopen("my_string.c", "r");
    if (!myStringDotC)
    {
        printf("ERROR: Can't open my_string.c\n\n");
        return MY_STRING_C_NOT_FOUND;
    }

    char buffer[512]; // Should not have code lines more than this size --> This could result in a bug if anybody bypasses this length

    // Checking for disallowed stuff
    while (!feof(myStringDotC))
    {
        if (fgets(buffer, sizeof(buffer), myStringDotC))
        {
            // Skipping everything after comment
            char *temp = buffer;

            int commFlag = 0; // Need flag since temp is set to buffer and we don't want to free buffer accidentally

            // Checking for // style comments
            char *commentLocation = strstr(buffer, "//");
            if (commentLocation)
            {
                // Grabbing everything from line to comment
                int beforeCommentSize = (commentLocation - buffer); // Call me the pointer monster
                temp = malloc(beforeCommentSize * sizeof(char) + 1);
                if (!temp)
                {
                    printf("ERROR: MEMORY ALLOCATION FAILED\n");
                    return MY_STRING_FAILURE;
                }
                strncpy(temp, buffer, beforeCommentSize);
                temp[beforeCommentSize - 1] = '\0';

                commFlag = 1;
            }

            // Checking for /* style comments
            // This was a pain back in compilers and it's a pain now too fam
            commentLocation = strstr(buffer, "/*");
            char *endOfCommentLocation = strstr(buffer, "*/");
            if (endOfCommentLocation)
            {
                // Gotta check after comment here and return failure
                char *theRestAfterEnd1 = strstr(endOfCommentLocation, "<string.h>");
                char *theRestAfterEnd2 = strstr(endOfCommentLocation, "<strings.h>");
                char *theRestAfterEnd3 = strstr(endOfCommentLocation, "[");
                char *theRestAfterEnd4 = strstr(endOfCommentLocation, "]");

                if (theRestAfterEnd1 || theRestAfterEnd2 || theRestAfterEnd3 || theRestAfterEnd4)
                {
                    printf("ALL TESTS FAILED: Disallowed header/notation used.\n\n");
                    return MY_STRING_FAILURE;
                }
                else
                {
                    // Necessary as we don't modify temp here
                    continue;
                }
            }

            // At this point we have a comment "beginner" :D
            if (commentLocation)
            {
                // Grabbing everything from line to comment
                int beforeCommentSize = (commentLocation - buffer); // Call me the pointer monster
                temp = malloc(beforeCommentSize * sizeof(char) + 1);
                if (!temp)
                {
                    printf("ERROR: MEMORY ALLOCATION FAILED\n");
                    return MY_STRING_FAILURE;
                }
                strncpy(temp, buffer, beforeCommentSize);
                temp[beforeCommentSize - 1] = '\0';

                commFlag = 1;
            }

            // At this point temp would be either before comment or just start of line (i.e. buffer)
            if (strstr(temp, "<string.h>"))
            {
                printf("ALL TESTS FAILED: Using <string.h> is not allowed\n\n");
                return STRING_H_USED;
            }

            if (strstr(temp, "<strings.h>"))
            {
                printf("ALL TESTS FAILED: (Trying to be sneaky huh?). Using <strings.h> is not allowed\n\n");
                return STRINGS_H_USED;
            }

            if (strstr(temp, "]") || strstr(temp, "["))
            {
                printf("ALL TESTS FAILED: Using array notation is not allowed in file my_string.c\n\n");
                return MY_STRING_FAILURE;
            }

            // Temp was malloced, free that man
            if (commFlag)
            {
                free(temp);
            }
        }
    }

    // Nice one ese
    return NO_ARRAY_NOTATION;
}

Suite *my_string_suite(void)
{
    Suite *s = suite_create("my_string_suite");

    // Even if they bypass this, they still need a valid implementation
    dontReverseEngineerBro = whatIsA2110StudentDoingHere();

    tcase_hack(s, NULL, NULL, test_my_strlen_1);
    tcase_hack(s, NULL, NULL, test_my_strlen_2);
    tcase_hack(s, NULL, NULL, test_my_strlen_3);
    tcase_hack(s, NULL, NULL, test_my_strlen_4);

    tcase_hack(s, NULL, NULL, test_my_strncmp_equal);
    tcase_hack(s, NULL, NULL, test_my_strncmp_null_terminator_in_middle_almost_same);
    tcase_hack(s, NULL, NULL, test_my_strncmp_null_terminator_in_middle_different);
    tcase_hack(s, NULL, NULL, test_my_strncmp_random);

    tcase_hack(s, NULL, NULL, test_my_strncpy_basic);
    tcase_hack(s, NULL, NULL, test_my_strncpy_destination_larger);
    tcase_hack(s, NULL, NULL, test_my_strncpy_random_basic_256);
    tcase_hack(s, NULL, NULL, test_my_strncpy_null_terminator_in_middle);
    tcase_hack(s, NULL, NULL, test_my_strncpy_overwrite);
    tcase_hack(s, NULL, NULL, test_my_strncpy_adv);

    return s;
}
