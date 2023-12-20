// DO NOT MODIFY THIS FILE

/**
 * @brief Header file for global macros, structures and fields to be used by the
 * hw7 program.
 */
#ifndef HW7_H
#define HW7_H

#include <stddef.h>

#define UNUSED_PARAM(x) ((void) x) // This macro is only used for turning off compiler errors initially
#define UNUSED_FUNC(x) ((void) x)  // This macro is only used for turning off compiler errors initially

// Success and failure codes for function return
#define SUCCESS 1
#define FAILURE 0

// Sizes for different arrays
#define MAX_CLASS_SIZE  64
#define MIN_NAME_SIZE   3
#define MAX_NAME_SIZE   10
#define MAX_HOUSE_SIZE  12
#define MIN_HOUSE_SIZE  4

// hogwarts_student struct
struct hogwarts_student {
    char    name[MAX_NAME_SIZE];
    int     age;
    double  housePoints;
    char    house[MAX_HOUSE_SIZE];
};
extern struct hogwarts_student class[MAX_CLASS_SIZE];
extern int size;

// Prototype hw7.c functions
int addStudent(const char *, int, double, const char *);
int updateStudentName(struct hogwarts_student, const char *);
int swapStudents(int, int);
int removeStudent(struct hogwarts_student);
int compareStudentName(struct hogwarts_student, struct hogwarts_student);
void sortStudents(void);

void printClass(void);

#endif
