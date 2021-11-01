//
// Created by 杜 浩志 on 2018/10/15.
//

#include "LMCRS.h"

Node LR_new_node(char c){
    Node n = (Node)malloc(sizeof(struct _Node));
    n->data = c;
    n->leftChild = NULL;
    n->rightSibling = NULL;
    n->parent = NULL;
    n->depth = 0;
    return n;
}

void LR_setLMC(Node n, Node LMC){
    n->leftChild = LMC;
    LR_setParent(LMC, n);
}

void LR_setRS(Node n, Node RS){
    n->rightSibling = RS;
    LR_setParent(RS, n->parent);
}

void LR_setParent(Node n, Node P){
    n->parent = P;
}

int LR_getDepth(Node n){
    if(n->parent != NULL){
        return LR_getDepth(n->parent)+1;
    }else{
        return 0;
    }
}

void LR_setDepth_ALL(Node n){
    if (n != NULL){
        n->depth = LR_getDepth(n);
        LR_setDepth_ALL(n->leftChild);
        LR_setDepth_ALL(n->rightSibling);
    }
}

void LR_print(Node n){
    if (n != NULL){
        for (int i = 0; i < n->depth; i++){
            printf("  ");
        }
        printf("%c\n", n->data);

        LR_print(n->leftChild);
        LR_print(n->rightSibling);
    }
}