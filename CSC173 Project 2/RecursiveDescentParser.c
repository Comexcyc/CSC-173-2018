//
// Created by 杜 浩志 on 2018/10/15.
//


#include <stdio.h>
#include <stdlib.h>
#include "RecursiveDescentParser.h"
#define FAILED NULL

TREE makeNode0 (char x);
TREE makeNode1(char x, TREE t);
TREE makeNode2 (char x, TREE t1, TREE t2);
TREE makeNode3 (char x, TREE t1, TREE t2, TREE t3);

TREE parseTree; /* holds the result of the parse */
char *nextTerminal; /* current position in input string */


TREE makeNode0 (char x){
    TREE root;

    root = (TREE) malloc(sizeof(struct NODE));
    root->label = x;
    root->leftmostChild = NULL;
    root->rightSibling = NULL;
    return root;
}

TREE makeNode1 (char x, TREE t1){
    TREE root;

    root = makeNode0(x);
    root->leftmostChild = t1;
    return root;
}

TREE makeNode2 (char x, TREE t1, TREE t2){
    TREE root;

    root = makeNode1(x,t1);
    t1->rightSibling = t2;
    return root;
}

TREE makeNode3 (char x, TREE t1, TREE t2, TREE t3){
    TREE root;

    root = makeNode1(x,t1);
    t1->rightSibling = t2;
    t2->rightSibling = t3;
    return root;
}

/* <D> --> 0|1|...|9 */
TREE D(){
    if (*nextTerminal == '0'){

        nextTerminal ++;
        return makeNode1('D', makeNode0('0'));

    } else if (*nextTerminal == '1'){

        nextTerminal ++;
        return makeNode1('D', makeNode0('1'));

    } else if (*nextTerminal == '2'){

        nextTerminal ++;
        return makeNode1('D', makeNode0('2'));

    } else if (*nextTerminal == '3'){

        nextTerminal ++;
        return makeNode1('D', makeNode0('3'));

    }else if (*nextTerminal == '4'){

        nextTerminal ++;
        return makeNode1('D', makeNode0('4'));

    }else if (*nextTerminal == '5'){

        nextTerminal ++;
        return makeNode1('D', makeNode0('5'));

    }else if (*nextTerminal == '6'){

        nextTerminal ++;
        return makeNode1('D', makeNode0('6'));

    }else if (*nextTerminal == '7'){

        nextTerminal ++;
        return makeNode1('D', makeNode0('7'));

    }else if (*nextTerminal == '8'){

        nextTerminal ++;
        return makeNode1('D', makeNode0('8'));

    }else if (*nextTerminal == '9'){

        nextTerminal ++;
        return makeNode1('D', makeNode0('9'));

    }else{
        return FAILED;
    }

}

/* <NT> --> <N> | e */
TREE NT(){
    TREE N1;
    N1 = N();
    if(N1!=FAILED){
        return makeNode1('n',N1);/* label changed from 'NT' to 'n' */
    }else{
        return makeNode1('n',makeNode0('e'));/* label changed from 'NT' to 'n' */
    }
}


/* <N> --> <D> <NT> */
TREE N(){
    TREE D1, NT1;
    D1= D();
    if(D1 != FAILED){
        NT1 = NT();
        if (NT1 != FAILED){
            return makeNode2('N',D1, NT1);
        }else{
            return FAILED;
        }
    }else{
        return FAILED;
    }
}


/* <F> --> <N> | (<E>)*/
TREE F(){
    TREE N1, E1;
    if (*nextTerminal == '('){
        nextTerminal ++;
        E1 = E();
        if (E1 != FAILED && *nextTerminal == ')'){

            nextTerminal++;
            return makeNode3('F',makeNode0('('), E1, makeNode0(')'));
        } else{
            return FAILED;
        }
    }else {
        N1 = N();
        if (N1 != FAILED){
            return makeNode1('F',N1);
        }
    }
    return 0;
}

/* <FT > → * / <F > <FT> | e */
TREE FT(){
    TREE F1, FT1;
    if(*nextTerminal == '*'){
        nextTerminal ++;
        F1 = F();
        if (F1 != FAILED){
            FT1 = FT();
            if (FT1 != FAILED){
                return makeNode3('f',makeNode0('*'),F1,FT1); /* label changed from 'FT' to 'f' */
            }else{
                return FAILED;
            }
        }else {
            return FAILED;
        }
    }else if(*nextTerminal == '/'){
        nextTerminal ++;
        F1 = F();
        if (F1 != FAILED){
            FT1 = FT();
            if (FT1 != FAILED){
                return makeNode3('f',makeNode0('/'),F1,FT1);/* label changed from 'FT' to 'f' */
            }else{
                return FAILED;
            }
        }else {
            return FAILED;
        }
    }else {
        return makeNode1('f',makeNode0('e'));/* label changed from 'FT' to 'f' */
    }
}
/* <T> --> <F> <FT> */
TREE T(){
    TREE F1, FT1;
    F1 = F();
    if (F1 != FAILED){
        FT1 =FT();
        if(FT1 != FAILED){
            return makeNode2('T',F1,FT1);
        }else {
            return FAILED;
        }
    }else {
        return FAILED;
    }
}
/* <TT> --> +- <T> <TT> | e */
TREE TT(){
    TREE T1, TT1;
    if(*nextTerminal == '+'){
        nextTerminal ++;
        T1 = T();
        if (T1 != FAILED){
            TT1 = TT();
            if(TT1 != FAILED){

                return makeNode3('t',makeNode0('+'),T1,TT1);/* label changed from 'TT' to 't' */
            }else{
                return FAILED;
            }
        }else{
            return FAILED;
        }
    }else if (*nextTerminal == '-'){
        nextTerminal++;
        T1 = T();
        if (T1 != FAILED){
            TT1 = TT();
            if(TT1 != FAILED){
                return makeNode3('t',makeNode0('-'),T1,TT1);/* label changed from 'TT' to 't' */
            }else{
                return FAILED;
            }
        }else{
            return FAILED;
        }
    }else{
        return makeNode1('t',makeNode0('e'));/* label changed from 'TT' to 't' */
    }
}
/* <E> --> <T><TT> */
TREE E(){

    TREE T1, TT1;
    T1 = T();
    if(T1 != FAILED){
        TT1 = TT();
        if (TT1 != FAILED){
            return makeNode2('E',T1,TT1);
        }else{
            return FAILED;
        }
    }else{
        return FAILED;
    }
}

void printTree(TREE tree, int Indentation) {

    if (tree == FAILED ) {
        printf("*** Parsing Failed ***\n");
    } else {

        printf("\n");
        for (int i = 0; i < Indentation; i++) {
            printf("\t");
        }

        printf("%c", tree->label);

        if (tree->leftmostChild != NULL) {
            printTree(tree->leftmostChild, Indentation+1);
        }

        if (tree->rightSibling != NULL) {
            printTree(tree->rightSibling, Indentation);
        }

    }
}
int isDigit(char c){
    if(c == '1'|c =='2'|c=='3'|c=='4'|c=='5'|c=='6'|c=='7'|c=='8'| c=='9' |c=='0'){
        return 1;
    }else{
        return 0;
    }
}

int isOperator (char c){
    if(c =='+'|c=='-'| c=='*'|c=='/'){
        return 1;
    }else{
        return 0;
    }
}

int evaluate(TREE root) {
    //int result = 0;
    char str[128];
    switch (root->label) {

        case 'E':
            return evaluate(root->leftmostChild);

        case 't':
            return evaluate(root->leftmostChild);

        case 'T':
            if(!isOperator(root->rightSibling->leftmostChild->label)) {
                return evaluate(root->leftmostChild);
            }
            if (root->rightSibling->leftmostChild->label == '+'){
                return evaluate(root->leftmostChild) + evaluate(root->rightSibling->leftmostChild->rightSibling);
            }
            if (root->rightSibling->leftmostChild->label == '-'){
                return evaluate(root->leftmostChild) - evaluate(root->rightSibling->leftmostChild->rightSibling);
            }

        case 'f':
            return evaluate(root->leftmostChild);

        case 'F':
            if (root->leftmostChild->label == '(') {
                if(root->rightSibling->leftmostChild->label == 'e'){
                    return evaluate(root->leftmostChild->rightSibling);
                }
                if(root->rightSibling->leftmostChild->label == '*'){
                    return evaluate(root->leftmostChild->rightSibling) * evaluate(root->rightSibling->leftmostChild->rightSibling);
                }if(root->rightSibling->leftmostChild->label == '/'){
                    return evaluate(root->leftmostChild->rightSibling) / evaluate(root->rightSibling->leftmostChild->rightSibling);
                }
            }
            if(root->rightSibling->leftmostChild->label == 'e'){
                return evaluate(root->leftmostChild);
            }
            if (root->rightSibling->leftmostChild->label == '/') {
                return evaluate(root->leftmostChild) / evaluate(root->rightSibling->leftmostChild->rightSibling);
            }
            if (root->rightSibling->leftmostChild->label == '*') {
                return evaluate(root->leftmostChild) * evaluate(root->rightSibling->leftmostChild->rightSibling);
            }

        case 'N':

            return evaluate(root->leftmostChild);

        case 'n':
            return evaluate(root->leftmostChild);

        case 'D':
            if(root->rightSibling->leftmostChild->label == 'e'){
                return evaluate(root->leftmostChild);
            }
            sprintf(str, "%d%d", evaluate(root->leftmostChild), evaluate(root->rightSibling));
            return atoi(str);

        case 'e':
            return 0;

        case '0':
            return 0;

        case '1':
            return 1;

        case '2':
            return 2;

        case '3':
            return 3;

        case '4':
            return 4;

        case '5':
            return 5;

        case '6':
            return 6;

        case '7':
            return 7;

        case '8':
            return 8;

        case '9':
            return 9;

    } 
    return -1;

}