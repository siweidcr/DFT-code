#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include <lcthw/list.h>


//bubble sort function, need a compare function input
int List_bubble_sort(List *list, List_compare list_compare);

List *List_merge_sort(List *list, List_compare cmp);

#endif
