#include "nfa.h"
#include <stdlib.h>
#include <printf.h>

typedef struct State{
    Set trans[128] ;
    bool accept;
} *State ;


typedef struct NFA{
    int states_num;
    Set current;
    State *states;
} *NFA;

/**
 * Allocate and return a new NFA containing the given number of states.
 */
extern NFA NFA_new(int nstates){
    NFA nfa = (NFA)malloc(sizeof(struct NFA));
    nfa -> states_num = nstates;
    nfa->current = Set_new();
    Set_add(nfa->current,0) ;
    nfa->states = (State*)malloc(sizeof(State) * nstates);
    for(int i = 0; i < nstates; i++){
        nfa->states[i] = (State)malloc(sizeof(struct State));
        nfa->states[i]->accept = false;
        for(int ii = 0; ii < 128; ii++){
            nfa->states[i]->trans[ii] = Set_new();
        }

    }

    return nfa;
}

/**
 * Free the given NFA.
 */
extern void NFA_free(NFA nfa){
    nfa = NULL;
}

/**
 * Return the number of states in the given NFA.
 */
extern int NFA_get_size(NFA nfa){
    return nfa->states_num;
}

/**
 * Return the set of next states specified by the given NFA's transition
 * function from the given state on input symbol sym.
 */
extern Set NFA_get_transitions(NFA nfa, int state, char sym){
    return nfa->states[state]->trans[(int)sym];
}

/**
 * For the given NFA, add the state dst to the set of next states from
 * state src on input symbol sym.
 */
extern void NFA_add_transition(NFA nfa, int src, char sym, int dst){
    Set_add(nfa->states[src]->trans[(int)sym],dst);
}

/**
 * Add a transition for the given NFA for each symbol in the given str.
 */
extern void NFA_add_transition_str(NFA nfa, int src, char *str, int dst){
    while(*str != '\0'){
        Set_add(nfa->states[src]->trans[(int)*str],dst);
        str++;
    }

}

/**
 * Add a transition for the given NFA for each input symbol.
 */
extern void NFA_add_transition_all(NFA nfa, int src, int dst){
    for(int i = 0; i < 128; i++){
        Set_add(nfa->states[src]->trans[i],dst);
    }
}

/**
 * Set whether the given NFA's state is accept or not.
 */
extern void NFA_set_accepting(NFA nfa, int state, bool value){
    nfa->states[state]->accept = value;
}

/**
 * Return true if the given NFA's state is an accept state.
 */
extern bool NFA_get_accepting(NFA nfa, int state){
    return nfa->states[state]->accept;
}

/**
 * Run the given NFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
extern bool NFA_execute(NFA nfa, char *input){
    nfa->current = nfa->states[0]->trans[*input];
    input++;
    //SetIterator possibleTrans = Set_iterator(nfa->states)
    while(*input != '\0'){
        SetIterator possibleStates = Set_iterator(nfa->current);
        Set newCurrent = Set_new();

        while(SetIterator_has_next(possibleStates)){
            int nextState = SetIterator_next(possibleStates);
            if(!Set_is_empty(nfa->states[nextState]->trans[*input])){
                Set_union(newCurrent,nfa->states[nextState]->trans[*input]);

            }

        }
        nfa->current = newCurrent;
        input++;
    }
    SetIterator availStates = Set_iterator(nfa->current);
    while(SetIterator_has_next(availStates)){
        int next = SetIterator_next(availStates);
        if(nfa->states[next]->accept){
            return true;
        }
    }

    return false;
}

/**
 * Print the given NFA to System.out.
 */
extern void NFA_print(NFA nfa);

//#endif
