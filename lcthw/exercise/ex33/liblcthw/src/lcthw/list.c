#include <lcthw/list.h>
#include <lcthw/dbg.h>

List *List_create()
{
    return calloc(1, sizeof(List));
}

void List_destroy(List *list)
{
    LIST_FOREACH(list, first, next, cur) {
        if(cur->prev) {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);
}
void *List_print(List *node){
    ListNode *current = node->first;
    while (current != NULL) {
        printf("%s -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}
void *List_print_back(List *node){
    ListNode *current = node->last;
    printf("NULL");

    while (current != NULL) {
        printf("<- %s ", current->value);
        current = current->prev;
    }
    printf("\n");
  }


void List_clear(List *list)
{
    LIST_FOREACH(list, first, next, cur) {
	free(cur->value);
    }

}

void List_clear_destroy(List *list)
{
    List_clear(list);
    List_destroy(list);
}


void List_push(List *list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);
    node->value = value;
    if(list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;

error:
    return;
}
void List_insert_sorted(List *list, void *value, List_compare list_compare)
{
    ListNode *cur = NULL;
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;
    if(list->last == NULL) {
        list->first = node;
        list->last = node;
    } 
    else {
        LIST_FOREACH(list,first, next, cur){
            if((list_compare(cur->value,node->value)> 0)&&(cur == list->first)) {
                list->first->prev = node;
                node->next = list->first;
                list->first = node;
                list->count++;
                return 0;    
            }
	    if((list_compare(cur->value,node->value)> 0)&&(cur != list->first)){
                node->prev = cur->prev;
                node->next = cur;
                cur->prev->next = node;
                cur->prev = node;
                list->count++;
                return 0;
            }
        }	  
         
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;

error:
    return;
}
void *List_pop(List *list)
{
    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if(list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;

error:
    return;
}

void *List_shift(List *list)
{
    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node)
{
    void *result = NULL;

    check(list->first && list->last, "List is empty.");
    check(node, "node can't be NULL");

    if(node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    } else if(node == list->first) {
        list->first = node->next;
        check(list->first != NULL, "Invalid list, somehow got a first that is NULL.");
        list->first->prev = NULL;
    } else if (node == list->last) {
        list->last = node->prev;
        check(list->last != NULL, "Invalid list, somehow got a next that is NULL.");
        list->last->next = NULL;
    } else {
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->count--;
    result = node->value;
    free(node);

error:
    return result;
}
