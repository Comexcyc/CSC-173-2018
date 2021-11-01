//
// Created by 杜 浩志 on 2018/10/15.
//

#include "RecursiveDescentParser.h"
#include "TableDrivenParser.h"

#include <stdio.h>
#include <string.h>

int main() {

    while(1){
        char *expression = (char*)malloc(65);
        printf("Please enter the expression, or enter 'quit' to quit: \n");
    
        fgets(expression, 65, stdin);
        int q = strcmp(expression, "quit");
        if(q == 0){
            return 0;
        }
        
        printf("Table Driven Parser: \n");
        T_parser tdp = T_new(expression);
        if(tdp->root != NULL){
            LR_setDepth_ALL(tdp->root);
            LR_print(tdp->root);
        }
        printf("\n");

        printf("Recursive Descent Parser: \n");
        nextTerminal = expression;
        parseTree = E();

        printTree(parseTree, 0);
        printf("\n");
        printf("result: %d\n", evaluate(parseTree));
        ///////test////////


        ///////test/////////

        
    }
   

}