#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include "queue.h"
#include "Library.h"



// the main trees program ,

int main(){
    int choice;
    int choice2;
    int n;
    node * root = NULL;
    node *P,*Q;
    bool stop2;
    int value;
    do{ 
        ClrScr();
        head();
        printf("\n");
        Menu();
        do{
            scanf("%d",&choice);
            printf("%d",isdigit(choice));
        }while(isdigit(choice));
        printf("\n");
        switch(choice){
            case 1:
                do{
                    ClrScr();
                    head();
                    printf("\n");
                    printf ("1. Binary search tree construction \n");
                    printf ("   ----------------------- \n\n");
                    printf ("1. Random construction\n");
                    printf ("2. manually construction\n\n");
                    printf (">  your choice : ");
                    scanf ("%d",&choice2);
                    switch(choice2){
                        case 1: 
                            ClrScr();
                            head();
                            printf("\n");
                            printf("1. Binary search tree construction \n");
                            printf("------------------------------- \n");
                            printf("1. Random construction\n\n");
                            printf("give the number of Nodes : ");
                            scanf("%d",&n);
                            createBTreeRandom(&root,n);
                            printf("\n");
                            printf("the tree is constructed !! :)\n");
                            stop2 = true;
                        break;
                        case 2: 
                            ClrScr();
                            head();
                            printf("\n");
                            printf("1. Binary search tree construction \n");
                            printf("---------------------------------- \n");
                            printf("2. manually construction\n\n");
                            printf("give the number of Nodes : ");
                            scanf ("%d",&n);
                            printf("\n");
                            createBTree(&root,n);
                            printf("\n");
                            printf("the tree is constructed !! :)\n");
                            stop2 = true;
                        break;
                    }
                }while(!stop2);
                printf ("\n\n> Press ENTER to continue ...\n");
                fflush(stdin);
                getchar();
            break;
            case 2: 
                ClrScr();
                head();
                printf("\n");
                printf("2- informations about the tree \n");
                printf("---------------------------------- \n\n");
                if(!stop2){ // or if the root has the value null 
                    printf(">ERROR : the Tree is empty\n");
                }else{
                    printf(">> Number of Nodes : %d \n\n", Nbnodes(root));
                    printf(">> Number of leaves using the iterative function : %d \n\n", leaf_count_iterative(root));
                    printf(">> sum of nodes using the iteratvie function : %d \n\n", sum_nodes_iterative(root)); 
                    printf(">> height : %d \n\n", depth(root));
                    printf(">> Strict Binary Search Tree  : ");
                    if (strictBinary(root))
                        printf("Yes \n\n");
                    else
                        printf("No \n\n");
                    printf(">> Complete Tree : ");
                    if (complete(root))
                        printf("Yes \n");
                    else
                        printf("No \n");
                    }
                printf ("\n> Press ENTER to continue ...");
                fflush(stdin);
                getchar();
            break;
            case 3:
                ClrScr();
                head();
                printf("\n");
                printf("3- The preorder displaying of the tree \n");
                printf("---------------------------------- \n\n");
                if(!stop2){
                    printf(">ERROR : the Tree is empty\n");
                }else{
                    preordre(root);
                }
                printf ("\n\n> Press ENTER to continue ...");
                fflush(stdin);
                getchar();
            break;
            case 4:
                ClrScr();
                head();
                printf("\n");
                printf("4- The inorder display of the tree \n");
                printf("---------------------------------- \n\n");
                if(!stop2){
                    printf(">ERROR : the Tree is empty\n");
                }else{
                    inordre(root);
                }
                printf ("\n\n> Press ENTER to continue ...");
                fflush(stdin);
                getchar();
            break;
            case 5:
                ClrScr();
                head();
                printf("\n");
                printf("5- The postorder display of the tree \n");
                printf("---------------------------------- \n\n");
                if(!stop2){
                    printf(">ERROR : the Tree is empty\n");
                }else{
                    postordre(root);
                }
                printf ("\n\n> Press ENTER to continue ...");
                fflush(stdin);
                getchar();
            break;
            case 6:
                ClrScr();
                head();
                printf("\n");
                printf("6- The searching of a specified value whithin the tree \n");
                printf("---------------------------------- \n\n");
                if(!stop2){
                    printf(">ERROR : the Tree is empty\n");
                }else{
                    printf(">> Give the value you want to search for : ");
                    scanf("%d", &value);
                    printf("\n");
                    search(root,value,&P,&Q);
                    if(P == NULL){
                        printf("The value does not exist in the tree.\n");
                    }else{
                        printf("The value exists in the list and it is stored in the node P : \n\n");
                        if(LC(P) == NULL && RC(P) != NULL){
                            printf("P = %p info(P) = %d \nRC(P) = %p info(RC(P)) = %d",P,info(P),RC(P),info(RC(P)));
                            printf("\nthe left child is NULL");
                        }else if(RC(P) == NULL && LC(P) != NULL){
                            printf("P = %p info(P) = %d \nLC(P) = %p info(LC(P)) = %d",P,info(P),LC(P),info(LC(P)));
                            printf("\nthe right child is NULL ");
                        }else if(RC(P) != NULL && LC(P) != NULL){
                            printf("P = %p info(P) = %d\nRC(P) = %p info(RC(P)) = %d\nLC(P) = %p info(LC(P)) = %d",P,info(P),RC(P),info(RC(P)),LC(P),info(LC(P)));
                        }else{
                            printf("P = %p info(P) = %d",P,info(P));
                            printf("\nthe right child and the left child are  NULL\n");
                        }
                    }
                }
                printf ("\n\n> Press ENTER to continue ...");
                fflush(stdin);
                getchar();
            break;
            case 7:
                ClrScr();
                head();
                printf("\n");
                printf("7- The insertion of a new value whithin th tree \n");
                printf("---------------------------------- \n\n");
                printf(">> Give the value you want to insert in the tree : ");
                scanf("%d", &value);
                insert(&root,value);
                printf("\nThe value has been inserted Correctly ! :) \n");
                printf ("\n> Press ENTER to continue ...");
                fflush(stdin);
                getchar();
            break;
            case 8:
                ClrScr();
                head();
                printf("\n");
                printf("8- The deletion of a value in a tree \n");
                printf("---------------------------------- \n\n");
                if(!stop2){
                    printf(">ERROR : the Tree is empty\n");
                }else{
                    printf(">> Give the value you want to delete from the tree : ");
                    scanf("%d", &value);
                    deletion(&root,value);// something is off with the delete function 
                }
                printf ("\n> Press ENTER to continue ...");
                fflush(stdin);
                getchar();
            break;
            case 10:
                ClrScr();
                head();
                printf("\n");
                printf("10- Printing the tree in the tree format \n");
                printf("---------------------------------- \n\n");
                if(!stop2){
                    printf(">ERROR : the Tree is empty\n");
                }else{
                    printf("\n\n");
                    inordre(root);
                    }
                printf ("\n> Press ENTER to continue ...");
                fflush(stdin);
                getchar();
            break;
        }
    }while(choice != 0);
}