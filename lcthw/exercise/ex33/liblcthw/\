#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>


//a compare function create
typedef int (*List_compare)(const char *str1, const char *str2);

struct ListNode;

typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
    void *value;
} ListNode;

typedef struct List {
    int count;
    ListNode *first;
    ListNode *last;
} List;

List *List_create();
void List_destroy(List *list);
void List_clear(List *list);
void List_clear_destroy(List *list);

void List_my_destroy(List *list);
void List_my_clear(List *list);
void List_my_clear_destroy(List *list);


#define List_count(A) ((A)->count)
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

void List_push(List *list, void *value);
void List_insert_sorted(List *list, void *value, List_compare list_compare);

void *List_pop(List *list);

void List_unshift(List *list, void *value);
void *List_shift(List *list);

void *List_remove(List *list, ListNode *node);
void *List_print(List *node);
void *List_print_back(List *node);


#define LIST_FOREACH1(L, S, M, V, ...) ListNode *_node = NULL;\
    ListNode *V = NULL;\
    for(V = _node = L->S; _node != NULL; V = _node = _node->M, ##__VA_ARGS__)

#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL;\
    ListNode *V = NULL;\
    for(V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif
