/**
 * @file hw7.c
 * @brief structs, pointers, pointer arithmetic, arrays, strings, and macros
 * @date 2021-06-xx
 */

// DO NOT MODIFY THE INCLUDE(S) LIST
#include <stdio.h>
#include "hw7.h"
#include "my_string.h"

// Global array of student structs
struct hogwarts_student class[MAX_CLASS_SIZE];

int size = 0;

/** addStudent
 *
 * @brief creates a new hogwarts_student struct and adds it to the array of hogwarts_student structs, "class"
 *
 *
 * @param "name" name of the student being created and added
 *               NOTE: if the length of name (including the null terminating character)
 *               is above MAX_NAME_SIZE, truncate name to MAX_NAME_SIZE. If the length
 *               is below MIN_NAME_SIZE, return FAILURE.  
 *               
 * @param "age" age of the student being created and added
 * @param "housePoints" gpa of the student being created and added
 * @param "house" Hogwarts house of the student being created and added
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) "name" is less than MIN_NAME_SIZE
 *         (2) a student with the name "name" already exits in the array "class"
 *         (3) adding the new student would cause the size of the array "class" to
 *             exceed MAX_CLASS_SIZE
 */
int addStudent(const char *name, int age, double housePoints, const char *house)
{
  // if not enough space in array, return failure
  if (size >= MAX_CLASS_SIZE) {
    return FAILURE;
  }

  // check if id is too short, if so return failure
  if (my_strlen(house) < MIN_HOUSE_SIZE) {
    return FAILURE;
  }
  // check if name is long enough
  if (my_strlen(name) < MIN_NAME_SIZE){
    return FAILURE;
  }
  // copy over id
  my_strncpy(class[size].house, house, my_strlen(house) + 1);

  // Check name, if it is too long, truncate it
  if (my_strlen(name) >= MAX_NAME_SIZE) {
    my_strncpy(class[size].name, name, MAX_NAME_SIZE - 1);
    class[size].name[MAX_NAME_SIZE - 1] = 0;
  } else {
    my_strncpy(class[size].name, name, my_strlen(name) + 1);
  }

  // copy over age and gpa
  class[size].housePoints = housePoints;
  class[size].age = age;

  // check for duplicates, based on name
  // only want to check up until the null terminator of the given name
  for (int i = 0; i < size; i++) {
    if (my_strncmp(class[i].name, class[size].name, my_strlen(class[size].name)) == 0) {
      return FAILURE;
    }
  }

  // add created student to class, just increment size since its already in array
  size++;
  return SUCCESS;
}

/** updateStudentName
 *
 * @brief updates the name of an existing hogwarts_student in the array of hogwarts_student structs, "class"
 *
 * @param "s" hogwarts_student struct that exists in the array "class"
 * @param "name" new name of hogwarts_student "s"
 *               NOTE: if the length of name (including the null terminating character)
 *               is above MAX_NAME_SIZE, truncate name to MAX_NAME_SIZE
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) the hogwarts_student struct "s" can not be found in the array "class"
 */
int updateStudentName(struct hogwarts_student s, const char *name)
{
  // iterate through array and look for student with the same name
  for (int i = 0; i < size; i++) {
    if (my_strncmp(class[i].name, s.name, my_strlen(class[i].name) + 1) == 0) {
      // if same name found, update
      if (my_strlen(name) >= MAX_NAME_SIZE) {
        // truncate long names
        my_strncpy(class[i].name, name, MAX_NAME_SIZE - 1);
        class[i].name[MAX_NAME_SIZE - 1] = 0;
        return SUCCESS;
      } else {
        // update normal len name
        my_strncpy(class[i].name, name, my_strlen(name) + 1);
        return SUCCESS;
      }
    }
  }

  // if same name not found, return failure
  return FAILURE;
}

/** swapStudents
 *
 * @brief swaps the position of two hogwarts_student structs in the array of hogwarts_student structs, "class"
 *
 * @param "index1" index of the first hogwarts_student struct in the array "class"
 * @param "index2" index of the second hogwarts_student struct in the array "class"
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) "index1" and/or "index2" are negative numbers
 *         (2) "index1" and/or "index2" are out of bounds of the array "class"
 */
int swapStudents(int index1, int index2)
{
  // bounds checks
  if (index1 < 0 || index1 >= size) return FAILURE;
  if (index2 < 0 || index2 >= size) return FAILURE;

  // swap ages
  int age = class[index1].age;
  class[index1].age = class[index2].age;
  class[index2].age = age;

  // swap housePoints
  double hp = class[index1].housePoints;
  class[index1].housePoints = class[index2].housePoints;
  class[index2].housePoints = hp;

  // swap names
  char name[MAX_NAME_SIZE];
  my_strncpy(name, class[index1].name, my_strlen(class[index1].name) + 1);
  my_strncpy(class[index1].name, class[index2].name, my_strlen(class[index2].name) + 1);
  my_strncpy(class[index2].name, name, my_strlen(name) + 1);

  // swap house names
  char house[MAX_HOUSE_SIZE];
  my_strncpy(house, class[index1].house, my_strlen(class[index1].house) + 1);
  my_strncpy(class[index1].house, class[index2].house, my_strlen(class[index2].house) + 1);
  my_strncpy(class[index2].house, house, my_strlen(house) + 1);

  return SUCCESS;
}

/** removeStudent
 *
 * @brief removes student in the array of hogwarts_student structs, "class", that has the same name
 *
 * @param "s" student struct that exists in the array "class"
 * @return FAILURE on failure, SUCCESS on success
 *         Failure if any of the following are true:
 *         (1) the student struct "s" can not be found in the array "class"
 */
int removeStudent(struct hogwarts_student s)
{
  // search for student to remove
  int i;
  for (i = 0; i < size; i++) {
    if (my_strncmp(class[i].name, s.name, my_strlen(class[i].name) + 1) == 0) {
      break;
    }
  }

  // if reached the end of the array, did not find student
  if (i == size) {
    return FAILURE;
  }

  // swap all the way down to remove the student
  for (int j = i; j < size; j++) {
    swapStudents(j, j + 1);
  }

  size--;
  return SUCCESS;
}

/** compareStudentName
 *
 * @brief using ASCII, compares the last three characters (not including the NULL
 * terminating character) of two students' names
 *
 * @param "s1" hogwarts_student struct that exists in the array "class"
 * @param "s2" hogwarts_student struct that exists in the array "class"
 * @return negative number if s1 is less than s2, positive number if s1 is greater
 *         than s2, and 0 if s1 is equal to s2
 */
int compareStudentName(struct hogwarts_student s1, struct hogwarts_student s2)
{
  // pointers for last 3 chars of ID
  char *name1, *name2;

  name1 = s1.name + my_strlen(s1.name) - 3;
  name2 = s2.name + my_strlen(s2.name) - 3;

  return my_strncmp(name1, name2, 3);

}

/** sortStudents
 *
 * @brief using the compareStudentName function, sort the students in the array of
 * student structs, "class," by the last three characters of their names 
 *
 * @param void
 * @return void
 */
void sortStudents(void)
{
  // selection sort shenanigans :)
  for (int i = 0; i < size; i++) {
    int min = i;
    for (int j = i; j < size; j++) {
      if (compareStudentName(class[j], class[min]) < 0) {
        min = j;
      }
    }
    swapStudents(i, min);
  }
}

void printClass(void) {
  for (int i = 0; i < size; i++) {
    printf("%s%d\n", "On student ", i);
    printf("%s%s\n", "Student name is ", class[i].name);
    printf("%s%d\n", "Student Age is ", class[i].age);
    printf("%s%s\n", "Student house is ", class[i].house);
    printf("%s%f\n", "Student housePts is ", class[i].housePoints);
  }
}
