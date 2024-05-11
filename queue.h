#ifndef QUEUES_H_INCLUDED
#define QUEUES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Library.h"
#include "stacks.h"


typedef struct cell {  
    node *element;
    int periority;
    struct cell * next;
}cell;

typedef struct Queue{  
    struct cell *head;
    struct cell *tail;
}Queue;


void createQueue(Queue *pf);
int EmptyQueue(Queue pf);
int FulllQueue(Queue pf);
int Enqueue(Queue *Q,node *element);
void Dequeue(Queue *Q,node **element);



void createQueue(Queue *pf){ // initialize the head and the tail to the element NULL
    pf->head = NULL;  
    pf->tail = NULL;
}


int EmptyQueue(Queue pf){ 
    return (pf.head == NULL);
}

int FulllQueue(Queue pf){ // it makes no sense because we are in dynamic implementation of the queue
return 0;
}


int Enqueue(Queue *Q,node *element){ 
    struct cell *temp; 
    temp = (cell *)malloc(sizeof(struct cell));
    temp->element= element;
    temp->next = NULL;
    temp->periority = element->info;
    if(!EmptyQueue(*Q)){ // we insert at the end
        Q->tail->next= temp; 
    }else{ // it will be the head of the queue
        Q->head = temp; 
    }
    Q->tail=temp;
    return 1; // the function worked properly
}

 
void Dequeue(Queue *Q,node **element){  // this gives us the element (ie: the element we are storing within the node)
    cell * temp;
    if(Q->head== NULL){
        printf("The list is empty"); // return if the queue is empty 
        return ;
    }else{
        *element= Q->head->element;
        temp = Q->head;
        Q->head=Q->head->next; // we set the head to be the next pointed by the head 
        free(temp);// we free the head 
    }

    if(Q->head==NULL){ // to say that the list is empty after the dequeuing
        Q->tail=NULL;  // if the head is dequeued then the tail will also be null, so the queue is empty
    }
}



void dequeue_periority_LR(Queue *Q ,node **element){
    cell * P;
    cell * previous = NULL;
    cell * temp = NULL;
    cell * previous_temp = NULL;

    P = Q->head;

    if(P != NULL){
        temp = P;
        while(P != NULL){
            if(P->periority < temp->periority){
                temp = P;
                previous_temp = previous;
            }
            previous = P;
            P = P->next;
        }
        if(temp == Q->head){
            Q->head = Q->head->next;
        }else{
            previous_temp->next = temp->next;
        }
        *element = temp->element;
        free(temp);
    }else{
        printf("the queue is empty\n");
    }
}



void dequeue_periority_RL(Queue *Q ,node **element){
    cell * P;
    cell * previous = NULL;
    cell * temp = NULL;
    cell * previous_temp = NULL;

    P = Q->head;

    if(P != NULL){
        temp = P;
        while(P != NULL){
            if(P->periority > temp->periority){
                temp = P;
                previous_temp = previous;
            }
            previous = P;
            P = P->next;
        }
        if(temp == Q->head){
            Q->head = Q->head->next;
        }else{
            previous_temp->next = temp->next;
        }
        *element = temp->element;
        free(temp);
    }else{
        printf("the queue is empty\n");
    }
}

// the iterative function of the number of leavs 

// we will be using a stack, we can also use the queue (fifo)

int leaf_count_iterative(node * root){
    Queue Q;
    node * temp;
    int count = 0;
    createQueue(&Q); 
    Enqueue(&Q,root);

    while(!EmptyQueue(Q)){
        Dequeue(&Q,&temp);
        if(LC(temp) == NULL && RC(temp) == NULL){
            count++;
        }else{
            if(LC(temp) != NULL){
                Enqueue(&Q,LC(temp));
            }
            if(RC(temp) != NULL){
                Enqueue(&Q,RC(temp));
            }
        }
    }

    return count;
}

// the iterative function to calculate the sum of all the nodes 
int sum_nodes_iterative(node * root){
    element sum ;
    node *temp;
    Queue Q;
    sum = 0;
    createQueue(&Q);
    Enqueue(&Q, root); // we push the root to the queue 
    while(!EmptyQueue(Q)){
        Dequeue(&Q,&temp);// 
        sum = sum + temp->info;
        
        if(LC(temp) != NULL){ // we move to the next level
            Enqueue(&Q,LC(temp));
        }
        if(RC(temp) != NULL){
            Enqueue(&Q,RC(temp));
        }
    }
    return sum;
}

// level by level traversal of a tree using the queue 
void level_bylevel_traversing(node *root)
{
    Queue Q;
    node * temp;

    createQueue(&Q);
    Enqueue(&Q, root);

    while(!EmptyQueue(Q)){
        Dequeue(&Q,&temp);

        printf("%d | ",temp->info);
        
        if(LC(temp) != NULL){
            Enqueue(&Q,LC(temp));
        }
        if(RC(temp)!= NULL){
            Enqueue(&Q,RC(temp));
        }
    }
}


void reverseQueue(Queue *Q){
    cell *temp;
    node *element;
    stack S;
    createStack(&S);
    while(!EmptyQueue(*Q)){
        Dequeue(Q,&element);
        push(&S,element);
    }
    while(!emptyStack(S)){
        element = pop(&S);
        Enqueue(Q,element);
    }
}

#endif