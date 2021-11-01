//
// Created by 杜 浩志 on 2018/10/15.
//

#include "TableDrivenParser.h"

/**
 * 0  E -> Tt
 * 1  t -> e
 * 2  t -> +Tt
 * 3  t -> -Tt
 * 4  T -> Ff
 * 5  f -> e
 * 6  f -> *Ff
 * 7  f -> /Ff
 * 8  F -> N
 * 9  F -> (E)
 * 10 N -> Dn
 * 11 n -> e
 * 12 n -> N
 * 13 D -> 0|1|2|3|4|5|6|7|8|9 returns the digit
 */

int table[8][16] = {
            //{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, +, -, *, /, (, )}
        /*E*/{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        /*T*/{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
        /*t*/{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 1, 1, 1, 1},
        /*F*/{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,-1,-1,-1,-1, 9,-1},
        /*f*/{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 7, 5, 5},
        /*N*/{10,10,10,10,10,10,10,10,10,10,-1,-1,-1,-1,-1,-1},
        /*n*/{12,12,12,12,12,12,12,12,12,12,11,11,11,11,11,11},
        /*D*/{13,14,15,16,17,18,19,20,21,22,-1,-1,-1,-1,-1,-1}
};

T_parser T_new(char* input){
    T_parser parser = (T_parser)malloc(sizeof(struct _T_parser));
    parser->input = input;
    parser->root = LR_new_node('E');
    parser->stack = Stack_new();
    parsing(parser);

    if (!T_lookahead(parser, '\n')){
        parser->root = NULL;
    }

    return parser;
}

char T_getnext(T_parser parser){
    return *parser->input;
}

int T_lookahead(T_parser parser, char c){
    if (*parser->input == c){
        parser->input ++;
        return 1;
    }
    else{
        return 0;
    }
}

int T_isTerminal(char c){
    switch (c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
        case 'e':
            return 1;
        default:
            return 0;
    }
}

int s_to_int(char c){
    switch (c) {
        case 'E': return 0;
        case 'T': return 1;
        case 't': return 2;
        case 'F': return 3;
        case 'f': return 4;
        case 'N': return 5;
        case 'n': return 6;
        case 'D': return 7;
        default: return -1;
    }
}

int i_to_int(char c){
    switch(c){
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case '+': return 10;
        case '-': return 11;
        case '*': return 12;
        case '/': return 13;
        case '(': return 14;
        case ')': return 15;
        case '\n':return -2;
        default : return -1;
    }
}

Node T_get_left_node(Node n){
    if (n->leftChild != NULL){
        Node temp1 = T_get_left_node(n->leftChild);
        if (temp1 != NULL){
            return temp1;
        }
    }
    else if (!T_isTerminal(n->data)){
        return n;
    }

    if (n->rightSibling != NULL){
        Node temp2 = T_get_left_node(n->rightSibling);
        if (temp2 != NULL){
            return temp2;
        }
    }

    return NULL;
}

void process_production(T_parser parser, int i){
    Node n = T_get_left_node(parser->root);
    switch (i){
        case -2:
            LR_setLMC(n, LR_new_node('e'));
            break;
        case -1:
            while (!Stack_is_empty(parser->stack)){
                Stack_pop(parser->stack);
            }
            parser->root = NULL;
            break;
        case 0:
            Stack_push(parser->stack, "t");
            Stack_push(parser->stack, "T");
            LR_setLMC(n,LR_new_node('T'));
            LR_setRS(n->leftChild, LR_new_node('t'));
            break;
        case 1:
            Stack_push(parser->stack, "e");
            LR_setLMC(n, LR_new_node('e'));
            break;
        case 2:
            Stack_push(parser->stack, "t");
            Stack_push(parser->stack, "T");
            Stack_push(parser->stack, "+");
            LR_setLMC(n, LR_new_node('+'));
            LR_setRS(n->leftChild, LR_new_node('T'));
            LR_setRS(n->leftChild->rightSibling, LR_new_node('t'));
            break;
        case 3:
            Stack_push(parser->stack, "t");
            Stack_push(parser->stack, "T");
            Stack_push(parser->stack, "-");
            LR_setLMC(n, LR_new_node('-'));
            LR_setRS(n->leftChild, LR_new_node('T'));
            LR_setRS(n->leftChild->rightSibling, LR_new_node('t'));
            break;
        case 4:
            Stack_push(parser->stack, "f");
            Stack_push(parser->stack, "F");
            LR_setLMC(n,LR_new_node('F'));
            LR_setRS(n->leftChild, LR_new_node('f'));
            break;
        case 5:
            Stack_push(parser->stack, "e");
            LR_setLMC(n, LR_new_node('e'));
            break;
        case 6:
            Stack_push(parser->stack, "f");
            Stack_push(parser->stack, "F");
            Stack_push(parser->stack, "*");
            LR_setLMC(n, LR_new_node('*'));
            LR_setRS(n->leftChild, LR_new_node('F'));
            LR_setRS(n->leftChild->rightSibling, LR_new_node('f'));
            break;
        case 7:
            Stack_push(parser->stack, "f");
            Stack_push(parser->stack, "F");
            Stack_push(parser->stack, "/");
            LR_setLMC(n, LR_new_node('/'));
            LR_setRS(n->leftChild, LR_new_node('F'));
            LR_setRS(n->leftChild->rightSibling, LR_new_node('f'));
            break;
        case 8:
            Stack_push(parser->stack, "N");
            LR_setLMC(n, LR_new_node('N'));
            break;
        case 9:
            Stack_push(parser->stack, ")");
            Stack_push(parser->stack, "E");
            Stack_push(parser->stack, "(");
            LR_setLMC(n, LR_new_node('('));
            LR_setRS(n->leftChild, LR_new_node('E'));
            LR_setRS(n->leftChild->rightSibling, LR_new_node(')'));
            break;
        case 10:
            Stack_push(parser->stack, "n");
            Stack_push(parser->stack, "D");
            LR_setLMC(n,LR_new_node('D'));
            LR_setRS(n->leftChild, LR_new_node('n'));
            break;
        case 11:
            Stack_push(parser->stack, "e");
            LR_setLMC(n, LR_new_node('e'));
            break;
        case 12:
            Stack_push(parser->stack, "N");
            LR_setLMC(n, LR_new_node('N'));
            break;
        case 13:
            Stack_push(parser->stack, "0");
            LR_setLMC(n, LR_new_node('0'));
            break;
        case 14:
            Stack_push(parser->stack, "1");
            LR_setLMC(n, LR_new_node('1'));
            break;
        case 15:
            Stack_push(parser->stack, "2");
            LR_setLMC(n, LR_new_node('2'));
            break;
        case 16:
            Stack_push(parser->stack, "3");
            LR_setLMC(n, LR_new_node('3'));
            break;
        case 17:
            Stack_push(parser->stack, "4");
            LR_setLMC(n, LR_new_node('4'));
            break;
        case 18:
            Stack_push(parser->stack, "5");
            LR_setLMC(n, LR_new_node('5'));
            break;
        case 19:
            Stack_push(parser->stack, "6");
            LR_setLMC(n, LR_new_node('6'));
            break;
        case 20:
            Stack_push(parser->stack, "7");
            LR_setLMC(n, LR_new_node('7'));
            break;
        case 21:
            Stack_push(parser->stack, "8");
            LR_setLMC(n, LR_new_node('8'));
            break;
        case 22:
            Stack_push(parser->stack, "9");
            LR_setLMC(n, LR_new_node('9'));
            break;
        default:
            return;
    }
}

void add_production(T_parser parser, char *c){
    int p = table[s_to_int(*c)][i_to_int(T_getnext(parser))];

    if (i_to_int(T_getnext(parser)) == -2){
        p = -2;
    }
    if (i_to_int(T_getnext(parser)) == -1){
        p = -1;
    }

    process_production(parser, p);
}

void parsing(T_parser parser){
    Stack_push(parser->stack, "E");

    while (!Stack_is_empty(parser->stack)){
        char *pop = Stack_pop(parser->stack);

        if (T_isTerminal(*pop)){
            T_lookahead(parser, *pop);
        }
        else{
            add_production(parser, pop);
        }
    }
}

