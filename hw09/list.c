/**
 * CS 2110 - Summer 2021 - Homework 9
 *
 * @author YOUR NAME HERE
 *
 * list.c: Complete the functions!
 */

/**
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!-IMPORTANT-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * For any function that must use malloc, if malloc returns NULL, the function
 * itself should return NULL if needs to return something (or return FAILURE if
 * the function returns an int).
 */

// Do not add ANY additional includes!!!
#include "list.h"

/* You should NOT have any global variables. */

/* These are static helper functions not intended to be called anywhere outside this file. */
static Student *create_student(char *name, int id, ContentQuestion question);
static Node *create_node(char *name, int id, ContentQuestion question);
static int student_equal(const Student *student1, const Student *student2);

/** create_student
 *
 * Helper function that creates a Student by allocating memory for it on the heap
 * and initializing with the passed in data. You MUST create a deep copy of
 * the name by malloc'ing space for it on the heap.
 *
 * If malloc returns NULL, you should free everything you've allocated and return NULL.
 *
 * @param the fields of the Student struct
 * @return a Student, return NULL if malloc fails
 */
static Student *create_student(char *name, int id, ContentQuestion question)
{
    Student *student;
    if (!(student = (Student *) malloc(sizeof(Student)))) return NULL;

    int name_len;
    char *n_name = NULL;

    if (name != NULL) {
        name_len = strlen(name);
        if (!(n_name = (char *) malloc(name_len + 1))) {
            free(student);
            return NULL;
        }
        strncpy(n_name, name, name_len + 1);
    }

    student->name = n_name;
    student->id = id;
    student->question = question;

    return student;
}


/** create_node
  *
  * Helper function that creates a Node by allocating memory for it on the heap.
  * Be sure to set its next pointer to NULL.
  *
  * Remember that you need to malloc both the node itself and the Student
  * that's contained in the struct. You might want to call create_student instead of
  * malloc'ing again.
  *
  * If malloc returns NULL for either of them, you should return NULL to indicate failure.
  * In the case that you successfully malloc one of them but fail to malloc the other one,
  * you should free the one you successfully malloc'd.
  *
  * @param the fields of the Student struct
  * @return a Node
  */
static Node* create_node(char *name, int id, ContentQuestion question)
{
    Node *node = (Node *) malloc(sizeof(Node));
    if (node == NULL) return NULL;

    Student *student;
    if (!(student = create_student(name, id, question))) {
        free(node);
        return NULL;
    }
    node->data = student;
    node->next = NULL;

    return node;
}

/** student_equal
 * Helper function to help you compare two student structs.
 *
 * If the name and id are both equal, you should return 1.
 * Otherwise, return 0.
 *
 * NOTE: struct members that are pointers may be null!
 * If two students both have null for a certain pointer, the pointers are
 * considered equal.
 * However, if either of the input students is NULL, you should return 0.
 *
 * Make sure you're using the right function when comparing the name.
 * Remember that you are allowed to use functions from string.h
 *
 * This is meant to be used as a helper function in 'contains'; it is not tested
 * by the autograder.
 *
 * @param the two Student structs to be compared
 * @return 1 if equal, 0 otherwise
 */
static int student_equal(const Student *student1, const Student *student2)
{
    if (student1 == student2) return 1;
    if (student1 == NULL || student2 == NULL) return 0;

    if (student1->id != student2->id) return 0;

    if (student1->name != student2->name) {
        if (student1->name == NULL || student2->name == NULL) return 0;
        if (strcmp(student1->name, student2->name)) return 0;
    }

    return 1;
}

/** create_list
 *
 * Creates a LinkedList by allocating memory for it on the heap.
 * Be sure to initialize size to zero and head to NULL.
 *
 * If malloc returns NULL, you should return NULL to indicate failure.
 *
 * @return a pointer to a new struct list or NULL on failure
 */
LinkedList *create_list(void)
{
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
    if (!list) return NULL;
    list->head = NULL;
    list->size = 0;

    return list;
}

/** push_front
 *
 * Adds the element at the front of the LinkedList.
 *
 * @param list a pointer to the LinkedList structure.
 * @param the fields of the Student struct
 * @return 1 if the LinkedList is NULL or if allocating the new node fails, 0 if
 * successful.
 */
int push_front(LinkedList *list, char *name, int id, ContentQuestion question)
{
    if (!list) return FAILURE;
    Node *node = create_node(name, id, question);
    if (!node) return FAILURE;
    node->next = list->head;
    list->head = node;
    list->size += 1;
    return SUCCESS;
}

/** push_back
 *
 * Adds the element to the back of the LinkedList.
 *
 * @param list a pointer to the LinkedList structure.
 * @param the fields of the Student struct
 * @return 1 if the LinkedList is NULL or if allocating the new node fails, 0 if
 * successful.
 */
int push_back(LinkedList *list, char *name, int id, ContentQuestion question)
{
    if (!list) return FAILURE;

    if (list->size == 0) return push_front(list, name, id, question);

    Node *node = create_node(name, id, question);
    if (!node) return FAILURE;

    Node *curr = list->head;
    while (curr->next != NULL) curr = curr->next;
    curr->next = node;
    list->size += 1;

    return SUCCESS;
}

/** add_at_index
 *
 * Add the element at the specified index in the LinkedList. This index must lie in
 * the inclusive range [0,size].
 * For example, if you have no elements in the LinkedList,
 * you should be able to add to index 0 but no further.
 * If you have two elements in the LinkedList,
 * you should be able to add to index 2 but no further.
 *
 * @param list a pointer to the LinkedList structure
 * @param index 0-based, starting from the head in the inclusive range
 *              [0,size]
 * @param the fields of the Student struct
 * @return 1 if the index is out of bounds or the LinkedList is NULL or malloc fails
 *         (do not add the data in this case)
 *         otherwise (on success) return 0
 */
int add_at_index(LinkedList *list, int index, char *name, int id, ContentQuestion question)
{
    if (list == NULL || index < 0 || index > list->size) return FAILURE;
    if (index == 0) return push_front(list, name, id, question);
    if (index == list->size) return push_back(list, name, id, question);

    Node *node = create_node(name, id, question);
    if (!node) return FAILURE;

    Node *curr = list->head;
    int i = 1;
    while (curr->next != NULL && i < index) {
        curr = curr->next; i++;
    }

    node->next = curr->next;
    curr->next = node;
    list->size += 1;
    return SUCCESS;
}

/** get
 *
 * Gets the data at the specified index in the LinkedList
 *
 * @param list a pointer to the LinkedList structure
 * @param index 0-based, starting from the head.
 * @param dataOut A pointer to a pointer used to return the data from the
 *        specified index in the LinkedList or NULL on failure.
 * @return 1 if dataOut is NULL or index is out of range of the LinkedList or
 *         the LinkedList is NULL, 0 (on success) otherwise
 */
int get(LinkedList *list, int index, Student **dataOut)
{
    if (list == NULL || dataOut == NULL || index < 0 || index >= list->size) return FAILURE;

    Node *curr = list->head;
    int i = 0;
    while (curr != NULL && i < index) {
        curr = curr->next; i++;
    }
    *dataOut = curr->data; 
    return SUCCESS;
}

/** contains
  *
  * Traverses the LinkedList, trying to see if the LinkedList contains some
  * data. We say the list contains some input if there exists some node with
  * equal data as the input.
  *
  * You should use 'student_equal' here to compare the data. Note that pointers are
  * allowed to be null!
  *
  * If there are multiple pieces of data in the LinkedList which are equal to
  * the "data" parameter, return the one at the lowest index.
  *
  *
  * @param list a pointer to the LinkedList structure
  * @param data The data, to see if it exists in the LinkedList
  * @param dataOut A pointer to a pointer used to return the data contained in
  *                the LinkedList or NULL on failure
  * @return int    0 if dataOut is NULL, the list is NULL, or the list
  *                does not contain data, else 1
  */
int contains(LinkedList *list, Student *data, Student **dataOut)
{
    if(list == NULL || dataOut == NULL) return 0;

    Node *curr = list->head;
    while(curr != NULL && student_equal(curr->data, data) == 0) {
        curr = curr -> next;
    }
    if(curr == NULL) {
        *dataOut = NULL;
        return 0;
    }

    *dataOut = curr->data;
    return 1;
}

/** pop_front
  *
  * Removes the Node at the front of the LinkedList, and returns its data to the program user.
  *
  * @param list a pointer to the LinkedList.
  * @param dataOut A pointer to a pointer used to return the data in the first
  *                Node or NULL if the LinkedList is NULL or empty
  * @return 1 if dataOut is NULL (the LinkedList is NULL or empty), else (on success) 0
  */
int pop_front(LinkedList *list, Student **dataOut)
{
    if (list == NULL || dataOut == NULL || list->size == 0) return FAILURE;

    Node *f_node = list->head;
    list->head = f_node->next;
    list->size -= 1;
    *dataOut = f_node->data;
    free(f_node);
    return SUCCESS;
}

/** pop_back
  *
  * Removes the Node at the back of the LinkedList, and returns its data to the program user.
  *
  * @param list a pointer to the LinkedList.
  * @param dataOut A pointer to a pointer used to return the data in the last
  *                Node or NULL if the LinkedList is NULL or empty
  * @return 1 if dataOut is NULL (the LinkedList is NULL or empty), else (on success) 0
  */
int pop_back(LinkedList *list, Student **dataOut)
{
    if (list == NULL || dataOut == NULL || list->size == 0) return FAILURE;

    if(list->size == 1) {
        return pop_front(list, dataOut);
    }

    Node *curr = list->head;
    while(curr->next->next != NULL) {
        curr = curr->next;
    }
    *dataOut = curr->next->data;
    Node *to_free = curr->next;
    curr->next = NULL;
    free(to_free);
    list->size -= 1;
    return SUCCESS;
}


/** remove_at_index
 *
 * Remove the element at the specified index in the LinkedList.
 *
 * @param list a pointer to the LinkedList structure
 * @param dataOut A pointer to a pointer used to return the data in the last
 *                Node or NULL if the LinkedList is NULL or empty
 * @param index 0-based, starting from the head in the inclusive range
 *              [0,size-1]
 * @return 1 if the index is out of bounds, the LinkedList is NULL or
 *         the dataOut is NULL
 *         otherwise return 0
 */
int remove_at_index(LinkedList *list, Student **dataOut, int index)
{
    if (list == NULL || dataOut == NULL || list->size == 0 || index < 0 || index >= list->size) return FAILURE;

    if (index == 0) return pop_front(list, dataOut);

    Node *curr = list->head;
    int i = 1;
    while (curr->next->next != NULL && i < index) {
        curr = curr->next; i++;
    }
    *dataOut = curr->next->data;
    Node *f_node = curr->next;
    curr->next = f_node->next;
    list->size -= 1;
    free(f_node);
    return SUCCESS;
}

/** empty_list
 *
 * Empties the LinkedList. After this is called, the LinkedList should be
 * empty. This does NOT free the LinkedList struct itself, just all nodes and
 * data within. Make sure to check that the list is not NULL before
 * using it.
 *
 * Once again, the things that need to be freed after this method are:
 * - the nodes
 * - the Student structs within the nodes
 * - all pointers in the Student struct
 *
 * However, if you're using other methods you've written (which you should be),
 * those methods might take care of some of the freeing for you.
 *
 * You may call free on a char pointer as well as a struct pointer.
 *
 * If 'list' is NULL, simply return.
 *
 * @param list a pointer to the LinkedList structure
 */
void empty_list(LinkedList *list)
{
    if (list == NULL) return;
    Student *dummy_data = NULL;
    while (list->size > 0) {
        pop_front(list, &dummy_data);
        if (dummy_data == NULL) return;
        free(dummy_data->name);
        free(dummy_data);
    }
}

/** replace_name_at_index
 *
 * Replaces the name field in the Student data struct of the node at the specified index
 * with a new name
 * 
 * Note that new name may be a different size than old one (hint: use realloc to resize the buffer).
 *
 * @param list a pointer to the LinkedList structure
 * @param index 0-based, starting from the head in the inclusive range
 *              [0,size-1]
 * @param newName a pointer to the new name
 * @return 1 if the index is out of bounds, the LinkedList is NULL or
 *         realloc fails
 *         otherwise return 0
 */
int replace_name_at_index(LinkedList *list, int index, char *newName)
{
    if (list == NULL || index < 0 || index >= list->size) return FAILURE;

    int i = 0;
    Node *curr = list->head;
    while (curr->next != NULL && i < index) {
        curr = curr->next;
        i++;
    }
    int len = strlen(newName);
    char *n_name = (char*) realloc(curr->data->name, len + 1);
    if (!n_name) return FAILURE;

    strncpy(n_name, newName, len + 1);
    curr->data->name = n_name;

    return SUCCESS;
}

/** avoid_assembly
 *
 *
 * Traverse the Office Hours queue(LinkedList) as a TA and count how many students want to ask
 * you questions about assembly so you can promptly avoid them or ask another TA to help them.
 * In other words, traverse the LinkedList and count the number of students who have a ContentQuestion
 * equal to ASSEMBLY.
 *
 * @param list a pointer to the LinkedList structure
 * @param dataOut A pointer to int used to return a count of how many students have 
 *                a ContentQuestion about assembly
 *                or -1 if the LinkedList is NULL or empty
 * @return FAILURE if the LinkedList is NULL or empty, else SUCCESS
 */
int avoid_assembly(LinkedList *list, int *dataOut)
{
    if (list == NULL || list->size == 0) {
        *dataOut = -1;
        return 1;
    }
    int count = 0;
    Node *curr = list->head;
    for (int i = 0; i < list->size; i++) {
        if (curr->data != NULL && curr->data->question == ASSEMBLY) {
            count+= 1;
        }
        curr = curr->next;
    }
    *dataOut = count;
    return 0;
}
