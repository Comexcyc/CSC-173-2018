//
// Created by 杜 浩志 on 2018/10/15.
//

#ifndef CSC173_PROJECT_2_LMCRS_H
#define CSC173_PROJECT_2_LMCRS_H
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node *Node;

struct _Node{
    char data;
    Node leftChild;
    Node rightSibling;
    Node parent;
    int depth;
};

extern Node LR_new_node(char c);
extern void LR_setLMC(Node n, Node LMC);
extern void LR_setRS(Node n, Node RS);
extern void LR_setParent(Node n, Node P);
extern int  LR_getDepth(Node n);
extern void LR_setDepth_ALL(Node n);
extern void LR_print(Node n);

#endif