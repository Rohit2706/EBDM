//Group No. 7
//ANIRUDH GOYAL 2017A7PS0031P
//ANISHKUMAR SS 2017A7PS0069P
//ROHIT JAIN 2017A7PS0122P
//ADITYA SAXENA 2017A7PS0166P

// This file implements the stack and tree functionalities to be used while parsing

#include "parserDef.h"

// Function definations for stack

// To create a stack
stack* makeStack(){
    stack* res=(stack*)malloc(sizeof(stack));
    res->capacity=STACK_CAPACITY;
    res->pos=-1;
    return res;
}

// To push into the stack
void push(stack* inpStack, tree_node* pushnode){
    
    if(inpStack->pos<inpStack->capacity){
        inpStack->pos++;
        inpStack->vals[inpStack->pos]=pushnode;
    }
    else
        return;
    
}

// To update the current size of the stack
int size(stack* inpStack){
    return inpStack->pos+1;
}

// To get the top element in the stack
tree_node* top(stack* inpStack){
    return (tree_node*)inpStack->vals[inpStack->pos];
}

// To pop from top of the stack
tree_node* pop(stack* inpStack){
    if(inpStack->pos==-1){
        return NULL;
    }
    
    else{
        inpStack->pos--;
        return (tree_node*)inpStack->vals[inpStack->pos+1];
    }
    
}

// To create a node in the parse tree
tree_node* makenode(tagged_union inputtag){
    tree_node* newnode = (tree_node*) malloc(sizeof(tree_node));
    newnode->val=inputtag;
    newnode->child=NULL;
    newnode->no_child=0;
    newnode->no_leftchild = 0;
    return newnode;
}

// To add child of the parent node (head) in the parse tree
tree_node* addsinglenode( tree_node* head, tagged_union newtag){

    tree_node* newnode = makenode(newtag);

    head->child = realloc(head->child, (head->no_child+1)*(sizeof(tree_node)));
    head->child[head->no_child] = newnode; 
    head->no_child++;

    return newnode;
}