#ifndef lcthw_Stack_h
#define lcthw_Stack_h

#include <stdlib.h>

struct StackNode;

typedef struct StackNode {
    struct StackNode *next;
    void *value;
} StackNode;

typedef struct Stack {
    int count;
    StackNode *head;
} Stack;

Stack *Stack_create();
void Stack_destroy(Stack *stack);


#define Stack_count(A) ((A)->count)
#define Stack_peek(A) ((A)->head != NULL ? (A)->head->value : NULL)

#define STACK_FOREACH(S, V) StackNode *_node = NULL;\
    StackNode *V = NULL;\
    for(V = _node = S->head; _node != NULL; V = _node = _node->next)

#endif
void Stack_push(Stack *stack, void *value);
void *Stack_pop(Stack *stack);


Stack *Stack_create(){
    return calloc(1, sizeof(Stack));
}
void Stack_destroy(Stack *stack){
    STACK_FOREACH(stack, cur){
        free(cur);
    }
    free(stack);
}
void Stack_push(Stack *stack, void *value){
    StackNode *node = calloc(1, sizeof(StackNode));
    check_mem(node);

    node->value = value; 

    if(stack->head == NULL){
        stack->head = node;
    } 
    else{
        node->next = stack->head;
	stack->head = node;
    }
    stack->count++;
error:
    return;
}
void *Stack_pop(Stack *stack){
    StackNode *node = stack->head; 
    if(node == NULL){
        return NULL;
    }   
    else{
        stack->head = node->next;
	stack->count--;
    }

    void *result = node->value;
    free(node);

    return result;
}


