#ifndef STACKS_H_INCLUDED
#define STACKS_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include "Library.h"


//interface 

typedef struct cells {
    node *element;
    struct cells *next;
}cells;

typedef struct cells * stack; // or we can define another type conains a pointer to cells called top

cells *Allocate();
void Ass_adr(cells * P,cells * Q);
void Ass_node(cells * P,node *Q);
cells * Next(cells * p);
node * nodeP(cells * P);
void Free(cells *P);
void createStack(stack *p);
bool emptyStack(stack p);
bool  fullStack(stack p);
void push(stack *p,node *P);// we push the node to be the element in the cells
node * pop(stack *p);// the popping will give us the node itself



cells *Allocate(){
    return ((cells *)malloc(sizeof(cells)));
}

void Ass_adr(cells * P,cells * Q){
    P->next = Q;
};

void Ass_node(cells * P,node *Q){
    P->element = Q;
}

cells * Next(cells * p){
    return p=p->next;
}

node * nodeP(cells * P){
    return (P->element);
}

void Free(cells *P){
    free(P);
}

/**************************************************************/
/**** Implementation of the stack modules using the lists  ****/
/**************************************************************/
 // hello my name is tarek ait ahmed i'm a first year student at the higher school of computer science algeria 
void createStack(stack *p){ 
    *p=NULL;
}

bool emptyStack(stack p){
    return (p == NULL);
}

bool  fullStack(stack p){
    return (0);
}

void push(stack *p,node *P){ 
    cells *q;
    q = Allocate();// we alocate a new cells 
    q->element = P;// we assign the element to the new cells and
    Ass_adr(q,*p);// we link the with the head of the stack and let it be the top of the stack
    *p=q; // the next of the q will be the first element, this will allow keeping us tracking the latest element in the stack, so we can pop it in the following function
}

node *pop(stack *p){
    node *temp;
    if(emptyStack(*p)){
        return NULL; // Return NULL or handle the error as appropriate
    } else {
        temp = nodeP(*p);
        *p = Next(*p);
        free(p);
        return temp;
    }
}


#endif
