/**
 * CS 2110 - Spring 2021 - Homework 9
 *
 * Do not modify this file!
 *
 * struct list.h
 */

#ifndef LIST_H
#define LIST_H 


#include <stdlib.h>
#include <string.h>

// Values to return from functions that return an int for success or failure
#define FAILURE 1
#define SUCCESS 0

// This is just to remove compiler warnings associated with unused variables.
// Delete calls to this as you implement functions.
#define UNUSED(x) ((void)(x))

/**************************
 ** Datatype definitions **
 **************************/

/*
 * The following structs define the linked list and node types for use in
 * list.c. DO NOT MODIFY THESE STRUCT DEFINITIONS!
 */
typedef enum content_question {
	ASSEMBLY, C, BITOPS
} ContentQuestion;

typedef struct student{
	char *name;
	int id;
	ContentQuestion question;
} Student;

typedef struct node {
    struct node *next; // pointer to the next node
    struct student *data; 
} Node;


typedef struct linked_list {
    Node *head; 		// Head pointer either points to a node with data or if the struct list is empty NULL
    int size;          // Size of the struct list
} LinkedList;

/***************************************************
** Prototypes for struct list library functions.  **
**                                                **
** For more details on their functionality,       **
** check list.c.                                  **
***************************************************/

/* Creating */
LinkedList *create_list(void);

/* Adding */
int push_front(LinkedList *list, char *name, int id, ContentQuestion question);
int push_back(LinkedList *list, char *name, int id, ContentQuestion question);
int add_at_index(LinkedList *list, int index, char *name, int id, ContentQuestion question);

/* Querying */
int get(LinkedList *list, int index, Student **dataOut);
int contains(LinkedList *list, Student *data, Student **dataOut);

/* Removing */
int pop_front(LinkedList *list, Student **dataOut);
int pop_back(LinkedList *list, Student **dataOut);
int remove_at_index(LinkedList *list, Student **dataOut, int index);
void empty_list(LinkedList *list);

/* Others */
int replace_name_at_index(LinkedList *list, int index, char *newName);
int avoid_assembly(LinkedList *list, int *dataOut);

#endif
