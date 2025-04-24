#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/** Our old friend die from ex17. */
void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

// a typedef creates a fake type, in this
// case for a function pointer
typedef int (*compare_cb)(int a, int b);

/**
 * A classic bubble sort function that uses the
 * compare_cb to do the sorting.
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));

    if(!target) die("Memory error.");

    memcpy(target, numbers, count * sizeof(int));

    for(i = 0; i < count; i++) {
        for(j = 0; j < count - 1; j++) {
            if(cmp(target[j], target[j+1]) > 0) {
                temp = target[j+1];
                target[j+1] = target[j];
                target[j] = temp;
            }
        }
    }

    return target;
}
//快速排序算法，将数据分为两组，分别排序
int *fast_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int m = 0;
    int n = 0;
    int count1 = count/2; //选择一个数据作为分界点
    int *target1 = malloc(count * sizeof(int));
    int *big = malloc(count * sizeof(int));
    int *small = malloc(count * sizeof(int));
    if(!target1||!big||!small) die("Memory error.");

    memcpy(target1, numbers, count * sizeof(int));
    //将target1中的原始数据，按照大于或者小于target1[count1]，分为两组
    for(i = 0; i < count; i++){
	if(target1[i] > target1[count1]){
	    big[m] = target1[i];
            m = m + 1;
        }
	else
        {
	    small[n] = target1[i];
            n = n + 1;
        }	    
    }
    //分别排序
    for(i = 0; i < m; i++) {
        for(j = 0; j < m - 1; j++) {
            if(cmp(big[j], big[j+1]) > 0) {
                temp = big[j+1];
                big[j+1] = big[j];
                big[j] = temp;
            }
        }
    }
    for(i = 0; i < n; i++) {
        for(j = 0; j < n - 1; j++) {
            if(cmp(small[j], small[j+1]) > 0) {
                temp = small[j+1];
                small[j+1] = small[j];
                small[j] = temp;
            }
        }
    }
    //将排序后的数据放入target1数组中
    int k = n;
    for(i = 0; i < count; i++) { 
        if((m > 0)&&(n == 0)){
            target1[i] = big[i-k];
	    m = m - 1; 
        }
        if(n > 0){
            target1[i] = small[i];
            n = n - 1;
        }
    }
    free(big);
    free(small);
    return target1;
    
}


int sorted_order(int a, int b)
{
    return a - b;
}

int reverse_order(int a, int b)
{
    return b - a;
}

int strange_order(int a, int b)
{
    if(a == 0 || b == 0) {
        return 0;
    } else {
        return a % b;
    }
}

/**
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out.
 */
void test_sorting(int *numbers, int count, compare_cb cmp)
{
    int i = 0;
    int *sorted = bubble_sort(numbers, count, cmp);

    if(!sorted) die("Failed to sort as requested.");

    for(i = 0; i < count; i++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");
    unsigned char *data = (unsigned char *)cmp;

    for(i = 0; i < 25; i++) {
    	printf("%02x:", data[i]);
    }
    printf("\n");
    free(sorted);

    printf("*********************\n");

    int j = 0;
    int *fast_sorted = fast_sort(numbers, count, cmp);

    if(!fast_sorted) die("Failed to sort as requested.");

    for(j = 0; j < count; j++) {
        printf("%d ", fast_sorted[j]);
    }
    printf("\n");
    unsigned char *data1 = (unsigned char *)cmp;

    for(j = 0; j < 25; j++) {
        printf("%02x:", data1[j]);
    }
    printf("\n");
    free(fast_sorted);
}


int main(int argc, char *argv[])
{
    if(argc < 2) die("USAGE: ex18 4 3 1 5 6");

    int count = argc - 1;
    int i = 0;
    char **inputs = argv + 1;

    int *numbers = malloc(count * sizeof(int));
    if(!numbers) die("Memory error.");

    for(i = 0; i < count; i++) {
        numbers[i] = atoi(inputs[i]);
    }

    test_sorting(numbers, count, sorted_order);
 //   test_sorting(numbers, count, reverse_order);
 //   test_sorting(numbers, count, strange_order);
    
    free(numbers);

    return 0;
}
