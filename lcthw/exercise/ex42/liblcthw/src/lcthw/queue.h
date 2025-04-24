#ifndef lcthw_Queue_h
#define lcthw_Queue_h

#include <stdlib.h>

struct QueueNode;

typedef struct QueueNode {
    struct QueueNode *next;
    void *value;
} QueueNode;

typedef struct Queue {
    int count;
    QueueNode *tail;
    QueueNode *head;
} Queue;

Queue *Queue_create();
void Queue_destroy(Queue *queue);


#define Queue_count(A) ((A)->count)
#define Queue_peek(A) ((A)->tail != NULL ? (A)->tail->value : NULL)

#define QUEUE_FOREACH(S, V) QueueNode *_node = NULL;\
    QueueNode *V = NULL;\
    for(V = _node = S->tail; _node != NULL; V = _node = _node->next)

#endif
void Queue_push(Queue *queue, void *value);
void *Queue_pop(Queue *queue);


Queue *Queue_create(){
    return calloc(1, sizeof(Queue));
}
void Queue_destroy(Queue *queue){
    QUEUE_FOREACH(queue, cur){
        free(cur);
    }
    free(queue);
}
void Queue_send(Queue *queue, void *value){
    QueueNode *node = calloc(1, sizeof(QueueNode));
    check_mem(node);

    node->value = value; 

    if(queue->tail == NULL){
        queue->tail = node;
	queue->head = node;
    } 
    else{
	queue->head->next = node;
	queue->head = node;
    }
    queue->count++;
error:
    return;
}
void *Queue_recv(Queue *queue){
    QueueNode *node = queue->tail; 
    if(node == NULL){
        return NULL;
    }   
    else{
        queue->tail = node->next;
	queue->count--;
    }

    void *result = node->value;
    free(node);

    return result;
}


