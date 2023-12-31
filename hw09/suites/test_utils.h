#include "../list.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define tcase_hack(suite, setup_fixture, teardown_fixture, func) { \
    TCase *tc = tcase_create(STRINGIFY(func)); \
    tcase_add_checked_fixture(tc, setup_fixture, teardown_fixture); \
    tcase_add_test(tc, func); \
    suite_add_tcase(s, tc); \
}

extern char *_malloc_string(char* str);

extern struct linked_list *_create_list(void);

extern void _push_front(struct linked_list *list, struct student *new_user);
extern struct student *_pop_front(struct linked_list *list);

extern struct node *_create_node(struct student *user);
extern struct student *_create_user(char *name, int id, ContentQuestion q);

extern int user_equal(struct student *user1, struct student *user2);

extern void _free_user(struct student *user);
extern void _free_node(struct node* node);
extern void _free_list(struct linked_list *list);
