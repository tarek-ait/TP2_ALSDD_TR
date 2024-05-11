#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



typedef struct node node ; // the definition of the node 
typedef int element; // the element of the node in our tree

typedef struct node {
    int info; // the element which we can give it the definition of element 
    struct node* LC;// the left chil of the node 
    struct node* RC; // the right child of the node 
    bool visited; // For LL-LR and LL-RL traversals
} node;
 

// the trees model functions

node * Createnode  (element val) // the creation of the node 
{
    node * p;
    p = (node *)malloc(sizeof(node ));// we alocate the node 
    p->info = val; // we assign the value of the head
    p->LC = NULL; // we assign the value of the LC child to be NULL
    p->RC = NULL;// we assign the value of the RC child to be NULL
    p->visited = false; // at the initialization the node is not visited of course 
    return (p);// then we return the head of our tree
}

// Procédure qui libère (détruit) le node  poelementé par (p)
void FreeNode  (node * p)
{
    free(p); // using the predefined function free 
}

// Fonction qui retourne le contenu du champ (LC) du node  poelementé par (p)
node * LC (node * p)
{
    if(p->LC){
        return p->LC; // return the left child of the node 
    }else{
        return NULL;// else we return null ie the left child doesn't exists 
    }   // we return the value of the LC child of the node  poelementer by the poelementer p
}

// Fonction qui retourne le contenu du champ (RC) du node  poelementé par (p)
node * RC (node * p)
{
    if(p->RC){
        return p->RC; // if the node has a right child 
    }else{
        return NULL;  // else if the right child doesnt exist 
    } // in this function we do the same but this time is the RC child 
}

// Fonction qui retourne l'information stockée dans le node  poelementé par (p)
element info (node * p)
{
    return ( p->info ); // we return the information stored in the info field of the node 
}

// Procédure qui assecte (val) dans le champ (info) du node  poelementé par (p)
void ass_info(node * p, element val)
{
    p->info = val; // we assign the info to the node 
}

// Procédure qui assecte (q) dans le champ (LC) du node  poelementé par (p)
void ass_LC (node * p, node * q)
{
    p->LC = q; // we assign the LC child to the node 
}

// Procédure qui assecte (q) dans le champ (RC) du node  poelementé par (p)
void ass_RC (node * p, node * q)
{
    p->RC = q;  // we assign the RC child to the node  
}


// the end of the trees modal functions (ie the functions of the abstract machine)


// the library funtcions 

element max(element a, element b) { // the max between to values 
    return a > b ? a : b; // function to compute the max between to integer values 
}

void ClrScr(){ // clearing the screen function
    system("cls");
}
void head(){ // title of the program 
    printf("*********************************************\n");
    printf("******* ALSDD : Binary search trees *********\n");
    printf("*********************************************\n");
}
void Menu(){ // displaying the menu and the choice message 
    printf("1- The construction of a binary search tree\n");
    printf("2- Informations about the tree\n");
    printf("3- The preorder displaying of the tree\n");
    printf("4- The inorder display of the tree\n");
    printf("5- The postorder display of the tree\n");
    printf("6- The searching of a specified value whithin the tree\n");
    printf("7- The insertion of a new value whithin th tree\n");
    printf("8- The deletion of a value in a tree\n");
    printf("9- Graphical elementerface of the tree\n");
    printf("10- Printing the tree in the tree format\n");
    printf("0- Leave the program\n");
    printf("\n");
    printf("please enter your choice ==> ");
}

// this function compute the number of nodes in the tree 
element Nbnodes (node* R)
{
    if (R == NULL) 
        return 0;
    else
        return (1 + Nbnodes(LC(R)) + Nbnodes(RC(R))); // we recall the function on the LC and the RC childs 
} 

// this function calculate the number of Feuilles in the tree 
element NbFeuilles(node* R)
{
    if (R == NULL)
        return 0;
    else
        if (LC(R)==NULL && RC(R)==NULL) // we need to verify that the node has no child so it would be counted as a fuielle
            return 1;
        else
            return (NbFeuilles(LC(R)) + NbFeuilles(RC(R)));
}

// depth of the tree 
element depth(node * root){
    if(root == NULL){
        return -1;// the depth of a node which has the value null
    }else{
        return 1 + max(depth(RC(root)),depth(LC(root)));
    }
}
// computing the sum of all the values in the nodes of the tree (the recursive version)
int sum_nodes(node * root){
    if(root == NULL){
        return 0;
    }else{
        return info(root) + sum_nodes(LC(root)) + sum_nodes(RC(root));
    }

}

// this function return the value true if the tree is strictly binary
bool strictBinary(node * root){ // one must know that a stric binary tree is a tree that each nodes has either the two childs or none of them 
    if(root == NULL){
        return false;
    }else 
        if((LC(root) == NULL && RC(root) == NULL)){
        return true; 
    }else if(RC(root) != NULL && RC(root) != NULL){
        return strictBinary(RC(root)) && strictBinary(LC(root));
    }
}

// function that returns a boolean wheather a tree is completed or note 
bool complete(node * root){// we must use the function strict binary 
    if(root == NULL){// an empty tree is not even a tree 
        return true;
    }else{
        int p1,p2; 
        p1 = depth(RC(root));// the depth of the right subtree
        p2 = depth(LC(root));// the depth of the left subtree

        return (complete(RC(root)) && complete(LC(root)) && (p1 == p2)); // the depth  must be the same for each sub tree in the tree 
    }
}

// searching for a vaule using a recursion function

void Rech(node **R, int Val, node **Pereq, node **Q)
{
    node *P;
    bool Trouve;

    *Pereq = NULL;
    *Q = *R;
    Trouve = false;
    while (((Trouve == false) && (*Q != NULL))){
        if ((info(*Q) == Val)){
            Trouve = true;
        }
        else{
            *Pereq = *Q;
            if ((info(*Q) > Val)){
                *Q = LC(*Q);
            }
            else{
                *Q = RC(*Q);
            }
        }
    }
}

void search(node * root,element value,node ** P,node ** Q){
    if(root == NULL){ 
        *P = NULL;
        *Q = NULL;
    }else if(info(root) == value){ 
        *P = root;
        *Q = NULL; 
    }else{
        if(value > info(root)){ 
            search(RC(root),value,P,Q);
        }else{
            search(LC(root),value,P,Q); // else we call it for the LC side
        }
    }
    if(*Q == NULL){
            *Q = root;
    }//Q will always be the last visited node in the tree 
}

// inserting a value elemento the tree, ofc it will be using the searching function
void insert(node ** root , element value){ // we can modify the root so it will be a call by variable not by value
    node * P;
    node * Q;
    if(*root == NULL){
        *root = Createnode(value);
    }else{
        search(*root,value,&P,&Q);// teh value mustn't be existing in the tree, so which means that the P is NULL and the Q will take the parent value which is the root of the tree 
        if(P == NULL){// Q will be the parent and the last visited node 
            P = Createnode(value);// we create a new node
            if(value < info(Q)){
                Q->LC = P;
            }else if(value > info(Q)){
                Q->RC = P;
            }
        }else{
            // printf("\n");
            // printf(">ERR0R : The value exists in the tree");
        }
    }
}

// the recursive version of the insertion function, the recusion is now on the insertInTree function instead of searching for the node 
// gg for the github copilot 
void insertInTree(node ** root,element value){
    if(*root == NULL){
        *root = Createnode(value);// the value is assinged in the createnode function 
    }else{
        if(value < info(*root)){
            insertInTree(&((*root)->LC),value); // we insert from the left, notice that we are giving the address of the left child of the root same as the right child 
        }else if(value > info(*root)){ // we are linking the root with it's right child when we are passing the adrees of the left child to the create node function 
            insertInTree(&((*root)->RC),value); // else we insert from the right branch of the tree 
        }
    }
}

// THE DELETION WORKS AND I'M SURE OF IT (CUZ I FIXED IT BY MY OWN) 
void deletion(node ** root,int value){
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

// the creation of a binary search tree of a giving number of nodes by the user 
void createBTree(node **root,int n){
    int i = 1;
    node *P,*Q;
    *root = NULL;
    while(i <= n){
        element value;
        if(*root == NULL){
            printf("give the root of your tree : \n");
        }
        printf("give the value (%d): ",i);
        scanf("%d", &value);
        insertInTree(root,value); // we just call the function insert 
        i++;
    }
}

// function to create binary searching tree randomly by giving the min and the max and filling the node of the tree with respecting the BST structure 
void *createBTreeRandom(node **root,int n){
    int i=1;
    node *P,*Q;
    *root = NULL;
    int min,max;
    element value;
    printf("give the maximum value : ");
    scanf("%d",&max);
    printf("give the minimum value : ");
    scanf("%d",&min);

    while(i<=n)
    {
        value = rand()%(max-min)+min;
        search(*root, value, &P, &Q);
        if (P == NULL)
        {
            insert (root, value);
            i++;
        }
    }
}




// the usuall traversing functions of BSTs  

void inordre(node * root){ // the inorder which consist of going through the left sub tree and then the root and then the right subtree 
    if(root != NULL){ // which is ofcourse recursive function 
        inordre(LC(root)); //  the left subtree 
        printf("%d | ",info(root));  // display the value of the root (we can use anything )
        inordre(RC(root)); // the right subtree
    }
}

void preordre(node * root){ // the preordre traversal process 
    if(root != NULL){
        printf("%d | ",info(root)); // throught the root first 
        preordre(LC(root)); // then through the left subtree
        preordre(RC(root)); // at the end through the right subtree 
    }
}

void postordre(node * root){ // the postordre which consist of the following 
    if(root != NULL){
        postordre(LC(root)); // the left subtree
        postordre(RC(root)); // the right subtree
        printf("%d | ",info(root)); // we process the root of the tree and the end 
    }
}

void printTree(node* root, int level) { // recursive module for printing our tree , which takes as an argument the root itself and the level 
    if (root == NULL)
        return;
    printTree(  RC(root), level + 1);
    for (int i = 0; i < level; i++){
        printf("   ");
    }
    printf("%d\n", root->info);
    printTree(LC(root), level + 1);
}


//***************************************************************//
//  printing the tree in the graphical format using the graphiz  //
//***************************************************************//

void bst_print_dot_null(int info, int nullcount, FILE* stream)
{
    fprintf(stream, "    null%d [shape=point];\n", nullcount);
    fprintf(stream, "    %d -> null%d;\n", info, nullcount);
}

void bst_print_dot_aux(node* node, FILE* stream)
{
    static int nullcount = 0;

    if (node->LC)
    {
        fprintf(stream, "    %d -> %d;\n", node->info, node->LC->info);
        bst_print_dot_aux(node->LC, stream);
    }
    else
        bst_print_dot_null(node->info, nullcount++, stream);

    if (node->RC)
    {
        fprintf(stream, "    %d -> %d;\n", node->info, node->RC->info);
        bst_print_dot_aux(node->RC, stream);
    }
    else
        bst_print_dot_null(node->info, nullcount++, stream);
}

void bst_print_dot(node* tree, FILE* stream)
{
    fprintf(stream, "digraph BST {\n");
    fprintf(stream, "    node [fontname=\"Arial\"];\n");

    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->RC && !tree->LC)
        fprintf(stream, "    %d;\n", tree->info);
    else
        bst_print_dot_aux(tree, stream);

    fprintf(stream, "}\n");
}


#endif
