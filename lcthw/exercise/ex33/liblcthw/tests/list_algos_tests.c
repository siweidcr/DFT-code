#include "minunit.h"
#include <lcthw/list_algos.h>
#include <assert.h>
#include <string.h>
#include <time.h>

char *values[] = {"xx87", "xx71", "xx22", "xx96", "xx53", "xx42", "ac2d", "4d8y", "cctx", "1687"};
char *str = NULL;
#define NUM_VALUES 10
#define NUM_TIMES 100000

List *create_words()
{
    int i;
    List *words = List_create();

    for(i = 0; i < NUM_VALUES; i++) {
        List_push(words,values[i]);
    }

    return words;
}
//生成随机字符
char random_char() {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int key = rand() % (sizeof(charset) - 1);
    return charset[key];
}

// 生成随机字符串
void *generate_random_string(int length) {
    str = (char*)malloc((length + 1) * sizeof(char));
    check_mem(str);

    for (int i = 0; i < length; i++) {
        str[i] = random_char();
    }
    str[length] = '\0';
    
    return 0;

error:
    return;

}
//创建不同长度的随机链表


List *create_many_words(int length)
{
    mu_assert(length > 0, "need a vaild length.");
    int i,j;
    List *words = List_create();
    j = rand()%10;
    
    for(i = 0; i < j; i++) {
	generate_random_string(length);
        List_push(words,str);
    }
    return words;
}

List *create_sorted_words(int length)
{
    mu_assert(length > 0, "need a vaild length.");
    int i,j;
    List *words = List_create();
    j = rand()%10;
    
    for(i = 0; i < j; i++) {
	generate_random_string(length);
        List_insert_sorted(words, str, (List_compare)strcmp);
    }
    return words;
}



int is_sorted(List *words)
{
    LIST_FOREACH(words, first, next, cur) {
        if(cur->next && strcmp(cur->value, cur->next->value) > 0) {
            debug("%s %s", (char *)cur->value, (char *)cur->next->value);
            return 0;
        }
    }

    return 1;
}
char *test_insert_sorted()
{
    List *words =  create_sorted_words(NUM_VALUES);
    mu_assert(is_sorted(words), "Words are not sorted by create sorted words.");
    List_clear_destroy(words);

    return NULL;

}
char *test_bubble_sort()
{
   
    List *words = create_many_words(NUM_VALUES);
    // should work on a list that needs sorting
    int rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort failed.");
    mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");
    // should work on an already sorted list
    rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort of already sorted failed.");
    mu_assert(is_sorted(words), "Words should be sort if already bubble sorted.");

    List_clear_destroy(words);
    // should work on an empty list
    words = List_create(words);
    rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort failed on empty list.");
    mu_assert(is_sorted(words), "Words should be sorted if empty.");

    List_clear_destroy(words);

    return NULL;
}

char *test_merge_sort()
{
    List *words = create_many_words(NUM_VALUES);

    // should work on a list that needs sorting
    List *res = List_merge_sort(words, (List_compare)strcmp);
    mu_assert(is_sorted(res), "Words are not sorted after merge sort.");

    List *res2 = List_merge_sort(res, (List_compare)strcmp);
    mu_assert(is_sorted(res), "Should still be sorted after merge sort.");
    List_destroy(res2);
    List_destroy(res);

    List_clear_destroy(words);
    return NULL;
}

void *test_time_sort()
{ 


    clock_t start,end;  
    start = clock();
    int i;
    for(i = 0; i < NUM_TIMES; i++)
    {
        test_bubble_sort();
    }
    
    end = clock();  

    printf("time=%f\n",(double)(end-start)/CLOCKS_PER_SEC);  
 
}
void *test_time_merge_sort()
{ 


    clock_t start,end;  
    start = clock();
    int i;
    for(i = 0; i < NUM_TIMES; i++)
    {
        test_merge_sort();
    }
    
    end = clock();  

    printf("time=%f\n",(double)(end-start)/CLOCKS_PER_SEC);  
 
}
void *test_time_insert_sorted()
{ 


    clock_t start,end;  
    start = clock();
    int i;
    for(i = 0; i < NUM_TIMES; i++)
    {
        test_insert_sorted();
    }
    
    end = clock();  

    printf("time=%f\n",(double)(end-start)/CLOCKS_PER_SEC);  
 
}

char *all_tests()
{
    mu_suite_start();
    srand((unsigned int) time(NULL));
    printf("NUM_VALUES: %d, NUM_TIMES: %d\n", NUM_VALUES, NUM_TIMES);
//    mu_run_test(test_bubble_sort);
//    mu_run_test(test_merge_sort);
    printf("test_bubble_sort:");
    mu_run_test(test_time_sort);
    printf("test_merge_sort:");
    mu_run_test(test_time_merge_sort);
    printf("test_insert_sorted:");
    mu_run_test(test_time_insert_sorted);
    return NULL;
}

RUN_TESTS(all_tests);
