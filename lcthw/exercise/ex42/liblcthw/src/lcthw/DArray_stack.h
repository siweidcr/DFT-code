#ifndef _Stack_h
#define _Stack_h
#include <stdlib.h>
#include <assert.h>
#include <lcthw/dbg.h>

typedef struct Stack {
    int max;
    int count;
    void **contents;
} Stack;

Stack *Stack_create();

void Stack_destroy(Stack *stack);

int Stack_expand(Stack *stack);

int Stack_contract(Stack *stack);

int Stack_push(Stack *stack, void *el);

void *Stack_pop(Stack *stack);

#define Stack_peek(A) ((A)->contents[(A)->count - 1])
#define Stack_count(A) ((A)->count)
#define Stack_max(A) ((A)->max)

#define INITIAL_MAX 10
#define DEFAULT_EXPAND_RATE 30

#define STACK_FOREACH(S, V) void *V = NULL; int COUNT;\
    for(COUNT = 0, V = S->contents[COUNT]; COUNT < S->count; COUNT++, V = S->contents[COUNT])
Stack *Stack_create()
{
    Stack *stack = malloc(sizeof(Stack));
    check_mem(stack);
    stack->count = 0;
    stack->max = INITIAL_MAX;
    stack->contents = calloc(INITIAL_MAX, sizeof(void *));
    check_mem(stack->contents);

    return stack;

error:
    if(stack) free(stack);
    return NULL;
}

void Stack_destroy(Stack *stack){
    if(stack) {
        if(stack->contents) free(stack->contents);
        free(stack);
    }
}
int Stack_resize(Stack *stack, size_t newsize)
{
    stack->max = newsize;
    check(stack->max > 0, "The newsize must be > 0.");

    void *contents = realloc(stack->contents, stack->max * sizeof(void *));
    // check contents and assume realloc doesn't harm the original on error

    check_mem(contents);

    stack->contents = contents;

    return 0;
error:
    return -1;
}
int Stack_expand(Stack *stack)
{
    size_t old_max = stack->max;
    check(Stack_resize(stack, stack->max + DEFAULT_EXPAND_RATE)  == 0,
            "Failed to expand stack to new size: %d",
            stack->max + DEFAULT_EXPAND_RATE );

    memset(stack->contents + old_max, 0, DEFAULT_EXPAND_RATE + 1);
    return 0;

error:
    return -1;
}

int Stack_contract(Stack *stack)
{
    int new_size = Stack_max(stack) - DEFAULT_EXPAND_RATE;

    return Stack_resize(stack, new_size + 1);
}

int Stack_push(Stack *stack, void *el)
{
    stack->contents[stack->count] = el;
    stack->count++;

    if(Stack_count(stack) >= Stack_max(stack)) {
        return Stack_expand(stack);
    } else {
        return 0;
    }
}

void *Stack_pop(Stack *stack)
{
    check(stack->count - 1 >= 0, "Attempt to pop from empty stack.");

    void *el = stack->contents[stack->count-1];
    stack->count--;

    if(Stack_count(stack) < Stack_max(stack) - DEFAULT_EXPAND_RATE) {
        Stack_contract(stack);
    }

    return el;
error:
    return NULL;
}

#endif
