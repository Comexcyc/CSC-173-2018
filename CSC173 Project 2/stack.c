//
// Created by 杜 浩志 on 2018/10/15.
//


#include "stack.h"

Stack Stack_new(){
    Stack stack = (Stack) malloc(sizeof(struct _Stack));
    stack->list = LinkedList_new();
    return stack;
}

int Stack_is_empty(Stack stack){
    return LinkedList_is_empty(stack->list);
}

void Stack_push(Stack stack, char *data){
    LinkedList_add_at_front(stack->list, data);
}

char* Stack_pop(Stack stack){
//    return (char*) LinkedList_pop(stack->list);
    return LinkedList_pop(stack->list);
}