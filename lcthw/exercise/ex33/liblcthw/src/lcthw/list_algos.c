#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>


int List_bubble_sort(List *list, List_compare list_compare){

    ListNode *Back_cur = NULL;
    ListNode *inlayer_cur = NULL;
    if((list->last == NULL)&&(list->first == NULL)){
        return 0;
    }
    for(Back_cur = list->last; Back_cur != list->first; Back_cur = Back_cur->prev){
	for(inlayer_cur = list->first; inlayer_cur != Back_cur; inlayer_cur = inlayer_cur->next){
            if(list_compare(inlayer_cur->value,inlayer_cur->next->value) > 0){
	        //exchange the order; the order is from small to big
		
		if((inlayer_cur == list->first) && (inlayer_cur->next != list->last)){
		    list->first = inlayer_cur->next;
		    inlayer_cur->next->next->prev = inlayer_cur;
		    inlayer_cur->next->prev = NULL;
                    inlayer_cur->next = inlayer_cur->next->next;
		    list->first->next = inlayer_cur;
		    inlayer_cur->prev = list->first;

		}
		else if((inlayer_cur != list->first) && (inlayer_cur->next == list->last)){
		    inlayer_cur->prev->next = inlayer_cur->next;
		    list->last = inlayer_cur;
		    inlayer_cur->next->prev = inlayer_cur->prev;
		    inlayer_cur->next = NULL;
		    inlayer_cur->prev->next->next = inlayer_cur;
		    inlayer_cur->prev = inlayer_cur->prev->next;
		}
		else if((inlayer_cur == list->first) && (inlayer_cur->next == list->last)){
		    inlayer_cur->prev = inlayer_cur->next;
		    inlayer_cur->next = NULL;
		    inlayer_cur->prev->next = inlayer_cur;
		    inlayer_cur->prev->prev = NULL;
		    list->first = inlayer_cur->prev;
		    list->last = inlayer_cur;
		}
		else {
                    inlayer_cur->prev->next = inlayer_cur->next;
		    inlayer_cur->next->next->prev = inlayer_cur;
    
    		    inlayer_cur->next->prev = inlayer_cur->prev;

		    inlayer_cur->next = inlayer_cur->next->next;
		    inlayer_cur->prev->next->next = inlayer_cur;

		    inlayer_cur->prev = inlayer_cur->prev->next;
	        }
                inlayer_cur = inlayer_cur->prev;//have exchange inlayer_cur flag, so back it
                if(inlayer_cur == Back_cur){
		    Back_cur = Back_cur->next; //gonna exchange back flag, so up it first

		}
	    }
        }
    }
    return 0;
}

inline List *List_merge(List *left, List *right, List_compare cmp)
{
    List *result = List_create();
    void *val = NULL;

    while(List_count(left) > 0 || List_count(right) > 0) {
        if(List_count(left) > 0 && List_count(right) > 0) {
            if(cmp(List_first(left), List_first(right)) <= 0) {
                val = List_shift(left);
            } else {
                val = List_shift(right);
            }

            List_push(result, val);
        } else if(List_count(left) > 0) {
            val = List_shift(left);
            List_push(result, val);
        } else if(List_count(right) > 0) {
            val = List_shift(right);
            List_push(result, val);
        }
    }

    return result;
}

List *List_merge_sort(List *list, List_compare cmp)
{
    if(List_count(list) <= 1) {
        return list;
    }

    List *left = List_create();
    List *right = List_create();
    int middle = List_count(list) / 2;

    LIST_FOREACH(list, first, next, cur) {
        if(middle > 0) {
            List_push(left, cur->value);
        } else {
            List_push(right, cur->value);
        }

        middle--;
    }

    List *sort_left = List_merge_sort(left, cmp);
    List *sort_right = List_merge_sort(right, cmp);

    List *result = List_merge(sort_left, sort_right, cmp);
    
    if(sort_left != left) List_destroy(sort_left);
    if(sort_right != right) List_destroy(sort_right);

    List_destroy(left);
    List_destroy(right);
   
    return result; 

}

