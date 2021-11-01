//
// Created by 杜 浩志 on 2018/10/15.
//

#ifndef CSC173_PROJECT_2_TABLEDRIVENPARSER_H
#define CSC173_PROJECT_2_TABLEDRIVENPARSER_H

#include <stdio.h>
#include "LMCRS.h"
#include "stack.h"

typedef struct _T_parser *T_parser;

struct _T_parser{
    char *input;
    Node root;
    Stack stack;
};

extern T_parser T_new(char* input);
extern char T_getnext(T_parser parser);
extern int  T_lookahead(T_parser, char c);
extern int  T_isTerminal(char c);
extern Node T_get_left_node(Node n);
extern int  s_to_int(char c);
extern int  i_to_int(char c);
extern void process_production(T_parser parser, int i);
extern void add_production(T_parser parser, char *c);
extern void parsing(T_parser parser);


#endif 