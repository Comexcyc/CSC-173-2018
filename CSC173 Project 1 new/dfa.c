
#include "dfa.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <printf.h>

typedef struct State{
    int trans[128] ;
    bool accept;
} *State ;

typedef struct DFA{

    int states_num;
    int current;
    State *states;
} *DFA  ;

DFA DFA_new(int nstates){

    DFA dfa = (DFA)malloc(sizeof(struct DFA));
    dfa -> states_num = nstates;
    dfa ->current = 0 ;
    dfa->states = (State*)malloc(sizeof(struct State) * nstates);
    for(int i = 0; i < nstates; i++){
        dfa->states[i] = (State)malloc(sizeof(struct State));
        dfa->states[i]->accept = false;
        for(int ii = 0; ii < 128; ii++){
            dfa->states[i]->trans[ii] = -1;
        }

    }
    return dfa;
}

void DFA_free(DFA dfa){

    dfa = NULL;
}

int DFA_get_size(DFA dfa){
    return dfa-> states_num;

}

/**
 * Return the state specified by the given DFA's transition function from
 * state src on input symbol sym.
 */
int DFA_get_transition(DFA dfa, int src, char sym){

    return dfa->states[src]->trans[(int)sym];
}

/**
 * For the given DFA, set the transition from state src on input symbol
 * sym to be the state dst.
 */
void DFA_set_transition(DFA dfa, int src, char sym, int dst){

    dfa->states[src]->trans[(int)sym] = dst;

}

/**
 * Set the transitions of the given DFA for each symbol in the given str.
 * This is a nice shortcut when you have multiple labels on an edge between
 * two states.
 */
void DFA_set_transition_str(DFA dfa, int src, char *str, int dst){

    while(*str != '\0'){ //i was starting from 0
        dfa->states[src]->trans[*str] = dst;
        str++;
    }
}

/**
 * Set the transitions of the given DFA for all input symbols.
 * Another shortcut method.
 */
void DFA_set_transition_all(DFA dfa, int src, int dst){

    for(int i = 0; i < 128; i++){
        dfa->states[src]->trans[i] = dst;
    }

}

/**
 * Set whether the given DFA's state is accept or not.
 */
void DFA_set_accepting(DFA dfa, int state, bool value){
    dfa->states[state]->accept = value;
}

/**
 * Return true if the given DFA's state is an accept state.
 */
bool DFA_get_accepting(DFA dfa, int state) {
    return dfa->states[state]->accept;

}

/**
 * Run the given DFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
extern bool DFA_execute(DFA dfa, char *input){

    while(*input != '\0'){
        if(dfa->states[dfa->current]->trans[*input] >= 0){
            dfa->current = dfa->states[dfa->current]->trans[*input];
        }else{
            return false;
        }
        input++;
    }

    return dfa->states[dfa->current]->accept;
}


/**
 * Print the given DFA to System.out.
 */
extern void DFA_print(DFA dfa);


//#endif