/**
 * @file hw7_suite.c
 * @author Farzam, Dillon, Nicole
 * @brief Testing Suites to HW7 - Fall 2020
 * @date 2020-10-16
 */

// Check Docs
// Tutorial : https://libcheck.github.io/check/doc/check_html/check_3.html
// Check API: https://libcheck.github.io/check/doc/doxygen/html/check_8h.html

// System Headers
#include <string.h>
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/wait.h> // For grabbing return value of system call

// TA Headers
#include "test_utils.h"

#define NO_STRING_H 2200
#define HW7_C_NOT_FOUND 1
#define HW7_FAILURE 2
#define STRING_H_USED 3
#define STRINGS_H_USED 4

#define INCORRECT_RESULT_MSG "array at index %d not populated correctly. Expected: %s, %d, %d (in order).\nargv[1]='%s'\n"

// Helper function prototypes
static void setup(void);
static void _add_student(const char *name, int age, double housePoints, const char *house);
static int whatIsA2110StudentDoingHere(void);


///////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************* TESTS ***********************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////

/* addStudent() tests */
START_TEST(test_addStudent_single)
{
    const char *name = "Harry Pot";
    int age = 22;
    double housePoints = 43.2;
    const char *house = "Gryffindor";
    int retVal = addStudent(name, age, housePoints, house);

    // We don't need to test that the values at name and house haven't changed, since they are pointers to const chars
    ck_assert_int_eq(retVal, SUCCESS);

    // Make sure the values in the global array have been correctly updated
    ck_assert_int_eq(size, 1);
    ck_assert(strncmp(class[0].name, name, MAX_NAME_SIZE) == 0); // don't use ck_assert_str_eq because it uses strcmp (not strncmp) internally
    ck_assert_int_eq(class[0].age, age);
    ck_assert(class[0].housePoints == housePoints);
    ck_assert(strncmp(class[0].house, house, MAX_HOUSE_SIZE) == 0);
}
END_TEST

START_TEST(test_addStudent_multiple_1) {
    const char *name1 = "Ron";
    int age1 = 19;
    double housePoints1 = 35.83;
    const char *house1 = "Hogwarts";
    int retVal1 = addStudent(name1, age1, housePoints1, house1);

    const char *name2 = "Draco";
    int age2 = 18;
    double housePoints2 = 31.85;
    const char *house2 = "Slytherin";
    int retVal2 = addStudent(name2, age2, housePoints2, house2);

    ck_assert_int_eq(retVal1, SUCCESS);
    ck_assert_int_eq(retVal2, SUCCESS);

    ck_assert_int_eq(size, 2);

    ck_assert(strncmp(class[0].name, name1, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[0].age, age1);
    ck_assert(class[0].housePoints == housePoints1);
    ck_assert(strncmp(class[0].house, house1, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[1].name, name2, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[1].age, age2);
    ck_assert(class[1].housePoints == housePoints2);
    ck_assert(strncmp(class[1].house, house2, MAX_HOUSE_SIZE) == 0);
}
END_TEST

START_TEST(test_addStudent_multiple_2) {
    for (int i = 0; i < 20; i++) {
        // Deterministically generate students
        char name[7];
        sprintf(name, "Mr. %02d", i);
        int age = 18 + i;
        double housePoints = 20.0 - i / 3.0;
        char house[9];
        sprintf(house, "House%02d", i);

        int retVal = addStudent(name, age, housePoints, house);
        ck_assert_int_eq(retVal, SUCCESS);
    }

    ck_assert_int_eq(size, 20);

    // Check the backing array after ALL students have been inserted
    for (int i = 0; i < 20; i++) {
        char name[7];
        sprintf(name, "Mr. %02d", i);
        int age = 18 + i;
        double housePoints = 20.0 - i / 3.0;
        char house[9];
        sprintf(house, "House%02d", i);

        ck_assert(strncmp(class[i].name, name, MAX_NAME_SIZE) == 0);
        ck_assert_int_eq(class[i].age, age);
        ck_assert(class[i].housePoints == housePoints);
        ck_assert(strncmp(class[i].house, house, MAX_HOUSE_SIZE) == 0);
    }
}
END_TEST

START_TEST(test_addStudent_null_terminator) {
    _add_student("LongWizardName", 45, 4.0, "GryffindorHufflepuff");
    size--;

    const char *name = "Bob";
    int age = 20;
    double housePoints = 3.5;
    const char *house = "ShortID";
    int retVal = addStudent(name, age, housePoints, house);

    ck_assert_int_eq(retVal, SUCCESS);

    ck_assert_int_eq(size, 1);
    ck_assert(strncmp(class[0].name, name, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[0].age, age);
    ck_assert(class[0].housePoints == housePoints);
    ck_assert(strncmp(class[0].house, house, MAX_HOUSE_SIZE) == 0);
}
END_TEST

START_TEST(test_addStudent_long_name)
{
    const char *name = "Ms. Elizabeth S. Longname III"; // This name should get truncated appropriately, do not expect failure
    const char* truncatedName = "Ms. Eliza";
    int age = 21;
    double housePoints = 64.5;
    const char *house = "Hufflepuff";
    int retVal = addStudent(name, age, housePoints, house);

    ck_assert_int_eq(retVal, SUCCESS);

    ck_assert_int_eq(size, 1);
    ck_assert(strncmp(class[0].name, truncatedName, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[0].age, age);
    ck_assert(class[0].housePoints == housePoints);
    ck_assert(strncmp(class[0].house, house, MAX_HOUSE_SIZE) == 0);
}
END_TEST

START_TEST(test_addStudent_short_house)
{
    const char *name = "Jerry";
    int age = 18;
    double housePoints = 4.0;
    const char *house = "G";
    int retVal = addStudent(name, age, housePoints, house);

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 0);
}
END_TEST

START_TEST(test_addStudent_duplicate_student)
{
    const char *name = "Ginny W";
    int age = 16;
    double housePoints = 45.0;
    const char *house1 = "Ravenclaw";
    const char *house2 = "Gryffindor";
    _add_student(name, age, housePoints, house1);
    int retVal = addStudent(name, age+1, housePoints-0.5, house2); // Should flag as a duplicate based on name only

    ck_assert_int_eq(retVal, FAILURE);

    // The student we inserted manually should remain unchanged
    ck_assert_int_eq(size, 1);

    ck_assert(strncmp(class[0].name, name, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[0].age, age);
    ck_assert(class[0].housePoints == housePoints);
    ck_assert(strncmp(class[0].house, house1, MAX_HOUSE_SIZE) == 0);
}
END_TEST


START_TEST(test_addStudent_too_many_students) {
    for (int i = 0; i < MAX_CLASS_SIZE; i++) {
        // Deterministically generate students
        char name[7];
        sprintf(name, "Mr. %02d", i);
        int age = 18 + i;
        double housePoints = 20.0 - i / 4.0;
        char house[8];
        sprintf(house, "HOUSE%02d", i);

        _add_student(name, age, housePoints, house);
    }
    int retVal = addStudent("One Mohr", 100, 2.0, "HOUSE");
    ck_assert_int_eq(retVal, FAILURE);

    ck_assert_int_eq(size, MAX_CLASS_SIZE);

    // The students we inserted manually should remain unchanged
    for (int i = 0; i < MAX_CLASS_SIZE; i++) {
        char name[7];
        sprintf(name, "Mr. %02d", i);
        int age = 18 + i;
        double housePoints = 20.0 - i / 4.0;
        char house[8];
        sprintf(house, "HOUSE%02d", i);

        ck_assert(strncmp(class[i].name, name, MAX_NAME_SIZE) == 0);
        ck_assert_int_eq(class[i].age, age);
        ck_assert(class[i].housePoints == housePoints);
        ck_assert(strncmp(class[i].house, house, MAX_HOUSE_SIZE) == 0);
    }
}
END_TEST

/* updateStudentName tests */
START_TEST(test_updateStudentName_basic) {
    // The only thing that matters is the name
    const char *name1 = "Arthur";
    const char *name2 = "Molly";
    const char *name3 = "Fred";
    const char *name4 = "George";
    int age = 24;
    double housePoints = 2.8;
    const char *house = "Gryffindor";

    // Even if the only difference is name, it should work
    _add_student(name1, age, housePoints, house);
    _add_student(name2, age, housePoints, house);

    int retVal1 = updateStudentName(class[0], name3);

    // The name is the only part of the struct that actually matters when we're searching
    // Make sure the students aren't checking using the whole struct
    struct hogwarts_student search = class[1];
    search.age++;
    search.housePoints--;
    strcpy(search.house, "Slytherin");
    int retVal2 = updateStudentName(search, name4);

    ck_assert_int_eq(retVal1, SUCCESS);
    ck_assert_int_eq(retVal2, SUCCESS);
    ck_assert_int_eq(size, 2);

    ck_assert(strncmp(class[0].name, name3, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[0].age, age);
    ck_assert(class[0].housePoints == housePoints);
    ck_assert(strncmp(class[0].house, house, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[1].name, name4, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[1].age, age);
    ck_assert(class[1].housePoints == housePoints);
    ck_assert(strncmp(class[1].house, house, MAX_HOUSE_SIZE) == 0);
}
END_TEST

START_TEST(test_updateStudentName_long_name) {
    const char *name = "Mr. Jonathan G. Longname IV"; // This name should get truncated appropriately, do not expect failure
    const char *truncatedName = "Mr. Jonat";
    const char *oldName = "Harry";
    int age = 18;
    double housePoints = 3.3;
    const char *house = "Gryffindor";
    _add_student(oldName, age, housePoints, house);
    int retVal = updateStudentName(class[0], name);

    ck_assert_int_eq(retVal, SUCCESS);

    ck_assert_int_eq(size, 1);
    ck_assert(strncmp(class[0].name, truncatedName, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[0].age, age);
    ck_assert(class[0].housePoints == housePoints);
    ck_assert(strncmp(class[0].house, house, MAX_HOUSE_SIZE) == 0);
}
END_TEST

START_TEST(test_updateStudentName_failure) {
    for (int i = 0; i < 15; i++) {
        // Deterministically generate students
        char name[7];
        sprintf(name, "Prof %d", i);
        int age = 18 + i;
        double housePoints = 4.0 - i / 20.0;
        char house[9];
        sprintf(house, "ABCD00%d", i);

        _add_student(name, age, housePoints, house);
    }

    const char *name = "Snape";
    int age = 23;
    double housePoints = 3.75;
    const char *house = "Slytherin";

    struct hogwarts_student search;
    strcpy(search.name, name);
    search.age = age;
    search.housePoints = housePoints;
    strcpy(search.house, house);

    int retVal = updateStudentName(search, "Shnape");

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 15);
}
END_TEST

START_TEST(test_updateStudentName_empty_array) {
    const char *name = "Luna";
    int age = 20;
    double housePoints = 3.6;
    const char *house = "Hufflepuff";

    _add_student(name, age, housePoints, house);
    size--; // This entry isn't actually in the array!

    int retVal = updateStudentName(class[0], "Cedric");

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 0);
}
END_TEST

/* swapStudents tests */
START_TEST(test_swapStudents_basic) {
    int index1 = 0;
    int index2 = 2;

    const char *name1 = "Luna";
    const char *name2 = "Myrtle";
    const char *name3 = "Malfoy";
    const char *name4 = "Cho";
    int age = 21;
    int age2 = 18;
    double housePoints = 3.3;
    const char *house = "Ravenclaw";
    const char *house2 = "Slytherin";

    _add_student(name1, age, housePoints, house);
    _add_student(name2, age, housePoints, house);
    _add_student(name3, age2, housePoints, house2);
    _add_student(name4, age, housePoints, house);

    int retVal = swapStudents(index1, index2);
    ck_assert_int_eq(retVal, SUCCESS);
    ck_assert_int_eq(size, 4);

    //index 1 = index2
    ck_assert(strncmp(class[index1].name, name3, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[index1].age, age2);
    ck_assert(class[index1].housePoints == housePoints);
    ck_assert(strncmp(class[index1].house, house2, MAX_HOUSE_SIZE) == 0);

    //index2 = index1
    ck_assert(strncmp(class[index2].name, name1, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[index2].age, age);
    ck_assert(class[index2].housePoints == housePoints);
    ck_assert(strncmp(class[index2].house, house, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[1].name, name2, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[1].age, age);
    ck_assert(class[index2].housePoints == housePoints);
    ck_assert(strncmp(class[1].house, house, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[3].name, name4, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[3].age, age);
    ck_assert(class[3].housePoints == housePoints);
    ck_assert(strncmp(class[3].house, house, MAX_HOUSE_SIZE) == 0);
}
END_TEST

START_TEST(test_swapStudents_same) {
    const char *name1 = "Luna";
    const char *name2 = "Myrtle";
    const char *name3 = "Malfoy";
    const char *name4 = "Cho";
    int age = 21;
    int age2 = 18;
    double housePoints = 3.3;
    const char *house = "Ravenclaw";
    const char *house2 = "Slytherin";

    _add_student(name1, age, housePoints, house);
    _add_student(name2, age, housePoints, house);
    _add_student(name3, age2, housePoints, house2);
    _add_student(name4, age, housePoints, house);

    int retVal = swapStudents(1, 1);

    ck_assert_int_eq(retVal, SUCCESS);
    ck_assert_int_eq(size, 4);

    ck_assert(strncmp(class[0].name, name1, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[0].age, age);
    ck_assert(class[0].housePoints == housePoints);
    ck_assert(strncmp(class[0].house, house, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[1].name, name2, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[1].age, age);
    ck_assert(class[1].housePoints == housePoints);
    ck_assert(strncmp(class[1].house, house, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[2].name, name3, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[2].age, age2);
    ck_assert(class[2].housePoints == housePoints);
    ck_assert(strncmp(class[2].house, house2, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[3].name, name4, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[3].age, age);
    ck_assert(class[3].housePoints == housePoints);
    ck_assert(strncmp(class[3].house, house, MAX_HOUSE_SIZE) == 0);

}
END_TEST

START_TEST(test_swapStudents_index_out_of_bound_1) {
    int index1 = -2; //out of bounds
    int index2 = 2;

    const char *name1 = "Luna";
    const char *name2 = "Myrtle";
    const char *name3 = "Padma";
    const char *name4 = "Cho";
    int age = 21;
    double housePoints = 3.3;
    const char *house = "Ravenclaw";

    _add_student(name1, age, housePoints, house);
    _add_student(name2, age, housePoints, house);
    _add_student(name3, age, housePoints, house);
    _add_student(name4, age, housePoints, house);

    int retVal = swapStudents(index1, index2);

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 4);

    ck_assert(strncmp(class[0].name, name1, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[0].age, age);
    ck_assert(class[0].housePoints == housePoints);
    ck_assert(strncmp(class[0].house, house, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[1].name, name2, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[1].age, age);
    ck_assert(class[1].housePoints == housePoints);
    ck_assert(strncmp(class[1].house, house, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[2].name, name3, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[2].age, age);
    ck_assert(class[2].housePoints == housePoints);
    ck_assert(strncmp(class[2].house, house, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[3].name, name4, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[3].age, age);
    ck_assert(class[3].housePoints == housePoints);
    ck_assert(strncmp(class[3].house, house, MAX_HOUSE_SIZE) == 0);
}
END_TEST

START_TEST(test_swapStudents_index_out_of_bound_2) {
    int index1 = 1;
    int index2 = 5; //out of bounds

    const char *name1 = "Luna";
    const char *name2 = "Myrtle";
    const char *name3 = "Padma";
    const char *name4 = "Cho";
    int age = 21;
    double housePoints = 3.3;
    const char *house = "Ravenclaw";

    _add_student(name1, age, housePoints, house);
    _add_student(name2, age, housePoints, house);
    _add_student(name3, age, housePoints, house);
    _add_student(name4, age, housePoints, house);

    int retVal = swapStudents(index1, index2);

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 4);

    ck_assert(strncmp(class[0].name, name1, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[0].age, age);
    ck_assert(class[0].housePoints == housePoints);
    ck_assert(strncmp(class[0].house, house, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[1].name, name2, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[1].age, age);
    ck_assert(class[1].housePoints == housePoints);
    ck_assert(strncmp(class[1].house, house, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[2].name, name3, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[2].age, age);
    ck_assert(class[2].housePoints == housePoints);
    ck_assert(strncmp(class[2].house, house, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[3].name, name4, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[3].age, age);
    ck_assert(class[3].housePoints == housePoints);
    ck_assert(strncmp(class[3].house, house, MAX_HOUSE_SIZE) == 0);
}
END_TEST

START_TEST(test_swapStudents_index_out_of_bound_3) {
    int index1 = 1;

    const char *name1 = "Luna";
    const char *name2 = "Myrtle";
    const char *name3 = "Padma";
    const char *name4 = "Cho";
    int age = 21;
    double housePoints = 3.3;
    const char *house = "Ravenclaw";

    _add_student(name1, age, housePoints, house);
    _add_student(name2, age, housePoints, house);
    _add_student(name3, age, housePoints, house);
    _add_student(name4, age, housePoints, house);

    int index2 = size; //out of bounds

    int retVal = swapStudents(index1, index2);

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 4);

    ck_assert(strncmp(class[0].name, name1, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[0].age, age);
    ck_assert(class[0].housePoints == housePoints);
    ck_assert(strncmp(class[0].house, house, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[1].name, name2, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[1].age, age);
    ck_assert(class[1].housePoints == housePoints);
    ck_assert(strncmp(class[1].house, house, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[2].name, name3, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[2].age, age);
    ck_assert(class[2].housePoints == housePoints);
    ck_assert(strncmp(class[2].house, house, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[3].name, name4, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[3].age, age);
    ck_assert(class[3].housePoints == housePoints);
    ck_assert(strncmp(class[3].house, house, MAX_HOUSE_SIZE) == 0);
}
END_TEST

/* removeStudent tests */
START_TEST(test_removeStudent_basic_1) {

    const char *name1 = "Samantha";
    const char *name2 = "Matt";
    const char *name3 = "Amanda";
    const char *name4 = "Chris";
    int age = 21;
    double housePoints = 20.3;
    const char *house = "Gryffindor";

    _add_student(name1, age, housePoints, house);
    _add_student(name2, age, housePoints, house); //student being removed
    _add_student(name3, age, housePoints, house);
    _add_student(name4, age, housePoints, house);

    int retVal = removeStudent(class[1]);

    ck_assert_int_eq(size, 3);
    ck_assert_int_eq(retVal, SUCCESS);

    ck_assert(strncmp(class[0].name, name1, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[0].age, age);
    ck_assert(class[0].housePoints == housePoints);
    ck_assert(strncmp(class[0].house, house, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[1].name, name3, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[1].age, age);
    ck_assert(class[1].housePoints == housePoints);
    ck_assert(strncmp(class[1].house, house, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[2].name, name4, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[2].age, age);
    ck_assert(class[2].housePoints == housePoints);
    ck_assert(strncmp(class[2].house, house, MAX_HOUSE_SIZE) == 0);
}
END_TEST

START_TEST(test_removeStudent_basic_2) {

    const char *name1 = "Samantha";
    const char *name2 = "Matt";
    const char *name3 = "Amanda";
    const char *name4 = "Chris";
    int age = 21;
    double housePoints = 13.3;
    const char *house = "Hufflepuff";

    _add_student(name1, age, housePoints, house);
    _add_student(name2, age, housePoints, house);
    _add_student(name3, age, housePoints, house);
    _add_student(name4, age, housePoints, house); //student being removed

    int retVal = removeStudent(class[3]);

    ck_assert_int_eq(size, 3);
    ck_assert_int_eq(retVal, SUCCESS);

    ck_assert(strncmp(class[0].name, name1, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[0].age, age);
    ck_assert(class[0].housePoints == housePoints);
    ck_assert(strncmp(class[0].house, house, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[1].name, name2, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[1].age, age);
    ck_assert(class[1].housePoints == housePoints);
    ck_assert(strncmp(class[1].house, house, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[2].name, name3, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[2].age, age);
    ck_assert(class[2].housePoints == housePoints);
    ck_assert(strncmp(class[2].house, house, MAX_HOUSE_SIZE) == 0);
}
END_TEST

START_TEST(test_removeStudent_student_does_not_exist) {
    const char *name1 = "Samantha";
    const char *name2 = "Matt";
    const char *name3 = "Amanda";
    const char *name4 = "Chris";
    int age = 21;
    double housePoints = 33.3;
    const char *house = "Ravenclaw";

    _add_student(name1, age, housePoints, house);
    _add_student(name2, age, housePoints, house);
    _add_student(name3, age, housePoints, house);
    _add_student(name4, age, housePoints, house);

    const char *name5 = "Tara";
    int age2 = 20;
    double housePoints2 = 3.35;
    const char *house2 = "Slytherin";

    struct hogwarts_student s;
    strcpy(s.name, name5);
    s.age = age2;
    s.housePoints = housePoints2;
    strcpy(s.house, house2);

    int retVal = removeStudent(s);

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 4);

}
END_TEST

START_TEST(test_removeStudent_empty_array) {
    const char *name = "Jimmy";
    int age = 20;
    double housePoints = 0.0;
    const char *house = "Hufflepuff";

    _add_student(name, age, housePoints, house);
    size--; // This entry doesn't actually exist in the array!

    int retVal = removeStudent(class[0]);

    ck_assert_int_eq(retVal, FAILURE);
    ck_assert_int_eq(size, 0);
}
END_TEST

/* compareStudentName tests */
START_TEST(test_compareStudentName_basic_equal) {
    const char *name1 = "Jeffany";
    const char *name2 = "Tiffany";
    int age1 = 25;
    int age2 = 28;
    double housePoints1 = 3.38;
    double housePoints2 = 3.90;
    const char *house1 = "Hogwarts";
    const char *house2 = "Hufflepuff";

    _add_student(name1, age1, housePoints1, house1);
    _add_student(name2, age2, housePoints2, house2);

    int retVal = compareStudentName(class[0], class[1]);

    ck_assert_int_eq(retVal, 0);
}
END_TEST
START_TEST(test_compareStudentName_basic_less_than_1) {
  const char *name1 = "Claire";
  const char *name2 = "Victor";
  int age1 = 22;
  int age2 = 24;
  double housePoints1 = 2.88;
  double housePoints2 = 3.11;
  const char *house1 = "Hogwarts";
  const char *house2 = "Hogwarts";

  _add_student(name1, age1, housePoints1, house1);
  _add_student(name2, age2, housePoints2, house2);

  int retVal = compareStudentName(class[0], class[1]);

  ck_assert_int_lt(retVal, 0);
}
END_TEST
START_TEST(test_compareStudentName_basic_less_than_2) {
  const char *name1 = "Freddy";
  const char *name2 = "George";
  int age1 = 12;
  int age2 = 14;
  double housePoints1 = 20.88;
  double housePoints2 = 13.11;
  const char *house1 = "Hogwarts";
  const char *house2 = "Hogwarts";

  _add_student(name1, age1, housePoints1, house1);
  _add_student(name2, age2, housePoints2, house2);

  int retVal = compareStudentName(class[0], class[1]);

  ck_assert_int_lt(retVal, 0);
}
END_TEST

START_TEST(test_compareStudentName_basic_greater_than_1) {
  const char *name1 = "Victor";
  const char *name2 = "Claire";
  int age1 = 18;
  int age2 = 16;
  double housePoints1 = 14.88;
  double housePoints2 = 13.11;
  const char *house1 = "Ravenclaw";
  const char *house2 = "Ravenclaw";

  _add_student(name1, age1, housePoints1, house1);
  _add_student(name2, age2, housePoints2, house2);

  int retVal = compareStudentName(class[0], class[1]);

  ck_assert_int_gt(retVal, 0);
}
END_TEST

START_TEST(test_compareStudentName_basic_greater_than_2) {
  const char *name1 = "Victor";
  const char *name2 = "Zhang";
  int age1 = 22;
  int age2 = 24;
  double housePoints1 = 2.88;
  double housePoints2 = 3.11;
  const char *house1 = "Slytherin";
  const char *house2 = "Slytherin";

  _add_student(name1, age1, housePoints1, house1);
  _add_student(name2, age2, housePoints2, house2);

  int retVal = compareStudentName(class[0], class[1]);

  ck_assert_int_gt(retVal, 0);
}
END_TEST

/* sortStudents tests */
// TODO: compare now uses the name, not id, fix for 3 sort tests below
START_TEST(test_sortStudents_1) {
    const char *name1 = "Maeve"; // sorted: 2
    const char *name2 = "Dave"; // sorted: 1
    const char *name3 = "Eve"; // sorted: 0
    int age1 = 20;
    int age2 = 23;
    int age3 = 19;
    double housePoints1 = 2.77;
    double housePoints2 = 2.94;
    double housePoints3 = 3.98;
    const char *house1 = "Gryffindor";
    const char *house2 = "Hufflepuff";
    const char *house3 = "Ravenclaw";

    _add_student(name1, age1, housePoints1, house1);
    _add_student(name2, age2, housePoints2, house2);
    _add_student(name3, age3, housePoints3, house3);

    sortStudents();

    ck_assert_int_eq(size, 3);

    ck_assert(strncmp(class[0].name, name3, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[0].age, age3);
    ck_assert(class[0].housePoints == housePoints3);
    ck_assert(strncmp(class[0].house, house3, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[1].name, name2, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[1].age, age2);
    ck_assert(class[1].housePoints == housePoints2);
    ck_assert(strncmp(class[1].house, house2, MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[2].name, name1, MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[2].age, age1);
    ck_assert(class[2].housePoints == housePoints1);
    ck_assert(strncmp(class[2].house, house1, MAX_HOUSE_SIZE) == 0);
}
END_TEST

START_TEST(test_sortStudents_2) {
    const char *name[] = {"Neville", "Dean", "Seamus", "Lavender", "Parvati"};
              // sorted: {"Parvati", "Lavender", "Dean", "Neville", "Seamus"}
              //           4          3           1       0          2
    int age[] = {18, 21, 21, 19, 22};
    double housePoints[] = {1.00, 3.42, 2.99, 3.56, 4.00};
    const char *house[] = {
        "Gryffindo1",
        "Gryffindo2",
        "Gryffindo3",
        "Gryffindo4",
        "Gryffindo5"
    };
    for (int i = 0; i < 5; i++) {
        _add_student(name[i], age[i], housePoints[i], house[i]);
    }

    sortStudents();

    ck_assert_int_eq(size, 5);

    ck_assert(strncmp(class[0].name, name[4], MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[0].age, age[4]);
    ck_assert(class[0].housePoints == housePoints[4]);
    ck_assert(strncmp(class[0].house, house[4], MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[1].name, name[3], MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[1].age, age[3]);
    ck_assert(class[1].housePoints == housePoints[3]);
    ck_assert(strncmp(class[1].house, house[3], MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[2].name, name[1], MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[2].age, age[1]);
    ck_assert(class[2].housePoints == housePoints[1]);
    ck_assert(strncmp(class[2].house, house[1], MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[3].name, name[0], MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[3].age, age[0]);
    ck_assert(class[3].housePoints == housePoints[0]);
    ck_assert(strncmp(class[3].house, house[0], MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[4].name, name[2], MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[4].age, age[2]);
    ck_assert(class[4].housePoints == housePoints[2]);
    ck_assert(strncmp(class[4].house, house[2], MAX_HOUSE_SIZE) == 0);
}
END_TEST

START_TEST(test_sortStudents_3) {
    const char *name[] = {"Draco", "Vincent", "Gregory", "Blaise", "Theodore", "Pansy", "Millicant", "Daphne"};
    //           after removing last two:
    //           sorted: {"Draco", "Vincent", "Blaise", "Pansy", "Theodore", "Gregory"}
    //                     0        1          3         5        4           2
    int age[] = {18, 21, 21, 19, 22, 20, 18, 21};
    double housePoints[] = {3.00, 3.42, 2.99, 1.56, 4.00, 4.00, 2.74, 1.23};
    const char *house[] = {
        "Slytheri1",
        "Slytheri2",
        "Slytheri3",
        "Slytheri4",
        "Slytheri5",
        "Slytheri6",
        "Slytheri7",
        "Slytheri8",
    };
    for (int i = 0; i < 8; i++) {
        _add_student(name[i], age[i], housePoints[i], house[i]);
    }
    size -= 2; // Millicant and Daphne don't exist :(

    sortStudents();

    ck_assert_int_eq(size, 6);

    ck_assert(strncmp(class[0].name, name[0], MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[0].age, age[0]);
    ck_assert(class[0].housePoints == housePoints[0]);
    ck_assert(strncmp(class[0].house, house[0], MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[1].name, name[1], MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[1].age, age[1]);
    ck_assert(class[1].housePoints == housePoints[1]);
    ck_assert(strncmp(class[1].house, house[1], MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[2].name, name[3], MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[2].age, age[3]);
    ck_assert(class[2].housePoints == housePoints[3]);
    ck_assert(strncmp(class[2].house, house[3], MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[3].name, name[5], MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[3].age, age[5]);
    ck_assert(class[3].housePoints == housePoints[5]);
    ck_assert(strncmp(class[3].house, house[5], MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[4].name, name[4], MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[4].age, age[4]);
    ck_assert(class[4].housePoints == housePoints[4]);
    ck_assert(strncmp(class[4].house, house[4], MAX_HOUSE_SIZE) == 0);

    ck_assert(strncmp(class[5].name, name[2], MAX_NAME_SIZE) == 0);
    ck_assert_int_eq(class[5].age, age[2]);
    ck_assert(class[5].housePoints == housePoints[2]);
    ck_assert(strncmp(class[5].house, house[2], MAX_HOUSE_SIZE) == 0);
}
END_TEST



///////////////////////////////////////////////////////////////////////////////////////////////////
/************************************** HELPER FUNCTIONS *****************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Wipe out the array - since they are globals, it is reasonable for students to expect the array to be zeroed and size to be 0 before each test
 * Also try to detect any funky stuff going on with including <string(s).h>
 */
static void setup(void)
{
    memset(class, 0, sizeof(class));
    size = 0;
    int dontReverseEngineerBro = whatIsA2110StudentDoingHere();
    if (dontReverseEngineerBro != NO_STRING_H) {
        ck_abort();
    }
}

/**
 * Adds a student - doesn't deal with error cases, so be careful about what you pass in
 */
static void _add_student(const char *name, int age, double housePoints, const char *house) {

    strncpy(class[size].name, name, my_strlen(name) + 1);
    class[size].age = age;
    class[size].housePoints = housePoints;
    strncpy(class[size].house, house, my_strlen(house) + 1);
    size++;
}
/**
 * This file can be huge, let's trust student a little bit and make sure even if they do add additional libraries, they add it at the top
 * WARNING: this does not work on the entire file (@see counterLimit)
 *
 * @return int a status code (@see #defines at the top)
 */
static int whatIsA2110StudentDoingHere(void)
{
    FILE *hw7DotC = fopen("hw7.c", "r");
    if (!hw7DotC)
    {
        printf("ERROR: Can't open hw7.c\n\n");
        return HW7_C_NOT_FOUND;
    }

    char buffer[512]; // Should not have code lines more than this size --> This could result in a bug if anybody bypasses this length

    // only checking the first 200 lines
    int counterLimit = 200;

    // Checking for disallowed stuff
    while (!feof(hw7DotC) && --counterLimit)
    {
        if (fgets(buffer, sizeof(buffer), hw7DotC))
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
                    return HW7_FAILURE;
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

                if (theRestAfterEnd1 || theRestAfterEnd2)
                {
                    printf("ALL TESTS FAILED: Disallowed header used.\n\n");
                    return HW7_FAILURE;
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
                    return HW7_FAILURE;
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

            // Temp was malloced, free that man
            if (commFlag)
            {
                free(temp);
            }
        }
    }

    // Nice one ese
    return NO_STRING_H;
}

Suite *hw7_suite(void)
{
    Suite *s = suite_create("hw7_suite");

    tcase_hack(s, setup, NULL, test_addStudent_single);
    tcase_hack(s, setup, NULL, test_addStudent_multiple_1);
    tcase_hack(s, setup, NULL, test_addStudent_multiple_2);
    tcase_hack(s, setup, NULL, test_addStudent_null_terminator);
    tcase_hack(s, setup, NULL, test_addStudent_long_name);
    tcase_hack(s, setup, NULL, test_addStudent_short_house);
    tcase_hack(s, setup, NULL, test_addStudent_duplicate_student);
    tcase_hack(s, setup, NULL, test_addStudent_too_many_students);

    tcase_hack(s, setup, NULL, test_updateStudentName_basic);
    tcase_hack(s, setup, NULL, test_updateStudentName_long_name);
    tcase_hack(s, setup, NULL, test_updateStudentName_failure);
    tcase_hack(s, setup, NULL, test_updateStudentName_empty_array);

    tcase_hack(s, setup, NULL, test_swapStudents_basic);
    tcase_hack(s, setup, NULL, test_swapStudents_same);
    tcase_hack(s, setup, NULL, test_swapStudents_index_out_of_bound_1);
    tcase_hack(s, setup, NULL, test_swapStudents_index_out_of_bound_2);
    tcase_hack(s, setup, NULL, test_swapStudents_index_out_of_bound_3);

    tcase_hack(s, setup, NULL, test_removeStudent_basic_1);
    tcase_hack(s, setup, NULL, test_removeStudent_basic_2);
    tcase_hack(s, setup, NULL, test_removeStudent_student_does_not_exist);
    tcase_hack(s, setup, NULL, test_removeStudent_empty_array);

    tcase_hack(s, setup, NULL, test_compareStudentName_basic_equal);
    tcase_hack(s, setup, NULL, test_compareStudentName_basic_less_than_1);
    tcase_hack(s, setup, NULL, test_compareStudentName_basic_less_than_2);
    tcase_hack(s, setup, NULL, test_compareStudentName_basic_greater_than_1);
    tcase_hack(s, setup, NULL, test_compareStudentName_basic_greater_than_2);

    tcase_hack(s, setup, NULL, test_sortStudents_1);
    tcase_hack(s, setup, NULL, test_sortStudents_2);
    tcase_hack(s, setup, NULL, test_sortStudents_3);
    // Return Testing Suite
    return s;
}
