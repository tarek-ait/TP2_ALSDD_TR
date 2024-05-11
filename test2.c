#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Library.h"
#include "stacks.h"
#include "queue.h"

// THE DELETION WORKS AND I'M SURE OF IT (CUZ I FIXED IT BY MY OWN) 
void delete(node ** root,int value){
    node * P;
    node * Q;
    node* ParentQ;
    node * parentP;
    Rech(root,value,&parentP,&P);
    if(P == NULL){
        printf(">ERROR : The value doesn't exist in the tree");
    }else{
        if(LC(P) == NULL){
            if(RC(P) == NULL){
                if(parentP !=  NULL){// if P is not the root of the tree 
                    if(P == RC(parentP)){
                        ass_RC(parentP,NULL);
                    }else{
                        ass_LC(parentP,NULL);
                    }
                }else{
                    *root = NULL; // we delete the whole tree, the RC child and the LC child are both equal to null and the parent is null which means that we are deleting the latest element in the tree 
                }
            }else{
                if(parentP !=  NULL){// if P is not the root of the tree 
                    if(P == RC(parentP)){
                        ass_RC(parentP,NULL);
                    }else{
                        ass_LC(parentP,RC(P));
                    }
                }else{// the Q is null which means that we are deleing with the root of the tree 
                    *root = RC(P); // we delete the whole tree 
                }
            }
        }else{
            if (RC(P) == NULL)  // Cas 3
            {
                if (parentP != NULL)
                {
                    if (P == LC (parentP))
                        ass_LC(parentP, LC(P));
                    else
                        ass_RC(parentP, LC(P));
                }
                else
                {
                    *root= LC(P);    // Mise à jour de la racine
                }
            }
            else{
                // 1. Rechercher le plus petit descendant du sous-arbre droit de (P)
                Q = RC(P);
                ParentQ = P;
                while (LC(Q) != NULL)
                {
                    ParentQ = Q;
                    Q = LC (Q);
                } // we find the smallest node of the RC subtree of the node P 
                // we repmace the value of P with the value of Q the smallest node in the RC side of P
                P->info = info (Q);
                // 3. Remplacer Q par RC(Q)
                if (Q == LC(ParentQ))
                    ass_LC (ParentQ, RC(Q));
                else
                    ass_RC (ParentQ, RC(Q));

		         P = Q;     // Car c'est Q qui va être réellement supprimé
            }
        }
        FreeNode(P);    
        // printf("\n,The value has been deleted Correctly ! :)\n");
    }
}




void printStack(stack P){
    cells * temp;
    temp = P;
    if(temp == NULL){
        printf("the stack is empty\n");
    }else{
        while(temp != NULL){
            printf("%d |",temp->element->info);
            temp = temp->next;
        }
    }
}

void printQueue(Queue P){
    cell * temp;
    temp = P.head;
    if(temp == NULL){
        printf("the Queue is empty\n");
    }else{
        while(temp != NULL){
            printf("%d |",temp->element->info);
            temp = temp->next;
        }
    }
}

void freestack(stack* P) {
    cells* temp;
    while (*P != NULL) {
        temp = *P;
        *P = (*P)->next;
        free(temp->element); // Assuming that the 'node' also needs to be deallocated
        free(temp);
    }
}


void LL_LR(node *root)
{
    stack S;
    node * temp;

    createStack(&S);
    

    push(&S, root);
    
    bool stop = false;
    // traversing all the leavs
    while(!stop){
        while(!emptyStack(S)){
            temp = pop(&S);
            if(RC(temp) == NULL && LC(temp) == NULL && !temp->visited){
                printf("%d | ",temp->info);
                temp->visited = true;
            }
            if(RC(temp) != NULL && !RC(temp)->visited){
                push(&S,RC(temp));
            }
            if(LC(temp)!= NULL && !LC(temp)->visited){
                push(&S,LC(temp));
            }
            if(RC(temp) != NULL && RC(temp)->visited && LC(temp) == NULL && !temp->visited){
                printf("%d | ",temp->info);
                temp->visited = true;   
            }
            if(LC(temp) != NULL && LC(temp)->visited && RC(temp) == NULL && !temp->visited){
                printf("%d | ",temp->info);
                temp->visited = true;   
            }    
            if(RC(temp) != NULL && LC(temp) != NULL && RC(temp)->visited && LC(temp)->visited){
                printf("%d | ",temp->info);
                temp->visited = true; 
            }      
        }
        if(!root->visited){
            push(&S,root);
            stop = false;
        }else{
            stop = true;
        }
    }
    
}


void LL_RL(node *root)
{
    stack S,S2;
    node * temp;

    createStack(&S);
    createStack(&S2);

    push(&S, root);
    
    bool stop = false;
    // traversing all the leavs
    while(!stop){
        while(!emptyStack(S)){
            temp = pop(&S);
            if(RC(temp) == NULL && LC(temp) == NULL && !temp->visited){
                printf("%d | ",temp->info);
                temp->visited = true;
            }
           
            if(LC(temp)!= NULL && !LC(temp)->visited){
                push(&S,LC(temp));
            }

            if(RC(temp) != NULL && !RC(temp)->visited){
                push(&S,RC(temp));
            }
            if(RC(temp) != NULL && RC(temp)->visited && LC(temp) == NULL && !temp->visited){
                printf("%d | ",temp->info);
                temp->visited = true;   
            }
            if(LC(temp) != NULL && LC(temp)->visited && RC(temp) == NULL && !temp->visited){
                printf("%d | ",temp->info);
                temp->visited = true;   
            }    
            if(RC(temp) != NULL && LC(temp) != NULL && RC(temp)->visited && LC(temp)->visited){
                printf("%d | ",temp->info);
                temp->visited = true; 
            }      
        }

        if(!root->visited){
            push(&S,root);
            stop = false;
        }else{
            stop = true;
        }
    }
    
}




void BB_LR(node * root){// we can do it baby 
    stack S;
    node * temp;
    Queue Q;
    node * temp1;
    createStack(&S);
    createQueue(&Q);
    
    
    temp = root;

    Enqueue(&Q,root);
    while(!EmptyQueue(Q)){
    
        dequeue_periority_LR(&Q,&temp);
        

        while(temp != NULL){
            push(&S,temp);
            temp = LC(temp);
        }
        temp = pop(&S);
        while(temp != NULL){ 
            push(&S,temp);
            temp = RC(temp);
        }
        while(!emptyStack(S)){
            temp = pop(&S);
            if(!temp->visited){
                printf("%d | ",temp->info);
                temp->visited = true;
            }
            if(RC(temp) != NULL && RC(temp)->visited == false){
               Enqueue(&Q,RC(temp));
            }
        }   
    }
}


void BB_RL(node * root){// we can do it baby 
    stack S;
    node * temp;
    Queue Q;
    node * temp1;
    createStack(&S);
    createQueue(&Q);
    temp = root;

    Enqueue(&Q,root);
    while(!EmptyQueue(Q)){
        dequeue_periority_RL(&Q,&temp);
        while(temp != NULL){ 
            push(&S,temp);
            temp = RC(temp);
        }
        temp = pop(&S);
        while(temp != NULL){
            push(&S,temp);
            temp = LC(temp);
        }
        while(!emptyStack(S)){
            temp = pop(&S);
            if(!temp->visited){
                printf("%d | ",temp->info);
                temp->visited = true;
            }
            if(LC(temp) != NULL && LC(temp)->visited == false){
               Enqueue(&Q,LC(temp));
            }
        }   
    }
}

void initialize_visited(node * root){
     if(root != NULL){  
        initialize_visited(LC(root)); 
        root->visited = false;
        initialize_visited(RC(root)); 
    }
}


// verifying the traversal 2 leaf by leaf 


void LL_LR_verification(node *root)
{
    stack S;
    node * temp;

    createStack(&S);
    push(&S,root);
    bool stop = false;
    node * temp1;
    // traversing all the leavs
    while(!stop){
        while(!emptyStack(S)){
            temp = pop(&S);
            if(LC(temp) == NULL && RC(temp) == NULL){
                printf("%d | ",temp->info);
                delete(&root,info(temp));
            } else {
                if(RC(temp) != NULL){
                    push(&S,RC(temp));
                }
                if(LC(temp) != NULL){
                    push(&S,LC(temp));
                }
            }
        }
        if(root != NULL){
            createStack(&S);
            push(&S,root);     
            stop = false;
        } else {
            stop = true;
        }
    }
}



void LL_RL_verification(node *root)
{
    stack S;
    node * temp;

    createStack(&S);
    push(&S,root);
    bool stop = false;
    node * temp1;
    // traversing all the leavs
    while(!stop){
        while(!emptyStack(S)){
            temp = pop(&S);
            if(LC(temp) == NULL && RC(temp) == NULL){
                printf("%d | ",temp->info);
                delete(&root,info(temp));
            } else {
                if(LC(temp) != NULL){
                    push(&S,LC(temp));
                }
                if(RC(temp) != NULL){
                    push(&S,RC(temp));
                }
            }
        }
        if(root != NULL){
            createStack(&S);
            push(&S,root);     
            stop = false;
        } else {
            stop = true;
        }
    }
}



int main(){

    node * root = Createnode(45); // initialize the example tree
    root->LC = Createnode(20);
    root->RC = Createnode(65);
    root->LC->LC = Createnode(10);
    root->LC->RC = Createnode(35);
    root->RC->LC = Createnode(55);
    root->RC->RC = Createnode(85);
    root->RC->RC->LC = Createnode(75);
    root->RC->RC->RC = Createnode(95);
    root->RC->RC->RC->RC = Createnode(98);
    root->RC->RC->RC->LC = Createnode(90);
    root->RC->RC->RC->LC->LC = Createnode(88);
    root->RC->LC->LC = Createnode(50);
    root->RC->LC->RC = Createnode(58);
    root->RC->LC->RC->LC = Createnode(56);
    root->RC->LC->RC->LC->RC = Createnode(57);
    root->RC->LC->RC->RC = Createnode(60);
    root->RC->LC->RC->RC->RC = Createnode(62);



    printf("printing the tree \n");
    printTree(root,0);

  
    // printf("traversing the tree leaf by leaf from the left to the right : \n");
    // LL_LR(root);
    // printf("\n\n");
    // // initialize_visited(root);

    // initialize_visited(root);   

    printf("\n");

    node *P,*Q;

    printf("\n");

    printf("traversing the tree leaf by leaf from the left to the right  : \n\n");
    LL_LR(root);
    // // initialize the visited field 

    initialize_visited(root);

  

    printf("\n\n\n");
    printf("traversing the tree leaf by leaf from the right to the left : \n\n");
    LL_RL(root);


    initialize_visited(root);


    printf("\n\n\n");
    printf("traversing the tree branch by branch from the left to the right : \n\n");
    BB_LR(root);

    
    initialize_visited(root);

    printf("\n\n\n");
    printf("traversing the tree branch by branch from the right to the left : \n\n");
    BB_RL(root);
}


