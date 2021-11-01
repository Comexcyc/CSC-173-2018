//
// Created by 杜 浩志 on 2018/10/15.
//


#ifndef CSC173_PROJECT_2_RECURSIVEDESCENTPARSER_H
#define CSC173_PROJECT_2_RECURSIVEDESCENTPARSER_H

typedef struct NODE *TREE;

struct NODE{
    char label;
    TREE leftmostChild, rightSibling;
};

extern TREE parseTree;
extern char *nextTerminal;

extern TREE makeNode0 (char x);
extern TREE makeNode1(char x, TREE t);
extern TREE makeNode2 (char x, TREE t1, TREE t2);
extern TREE makeNode3 (char x, TREE t1, TREE t2, TREE t3);
extern TREE D();
extern TREE NT();
extern TREE N();
extern TREE F();
extern TREE FT();
extern TREE T();
extern TREE TT();
extern TREE E();
extern void printTree(TREE tree, int Indentation);
extern int evaluate(TREE root);


#endif 
