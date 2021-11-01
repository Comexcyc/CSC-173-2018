//
// Created by 杜 浩志 on 2018/10/15.
//

#ifndef CSC173_PROJECT_2_STACK_H
#define CSC173_PROJECT_2_STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

typedef struct _Stack *Stack;
struct _Stack{
    LinkedList *list;
};

extern Stack Stack_new();
extern int Stack_is_empty(Stack stack);
extern void Stack_push(Stack stack, char *data);
extern char* Stack_pop(Stack stack);

#endif
