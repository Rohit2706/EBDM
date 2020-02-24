#include "parserDef.h"

stack* makeStack(){
    stack* res=(stack*)malloc(sizeof(stack));
    res->capacity=STACK_CAPACITY;
    res->pos=-1;
    return res;
}

void push(stack* inpStack, tree_node* pushnode){
    
    if(inpStack->pos<inpStack->capacity){
        inpStack->pos++;
        inpStack->vals[inpStack->pos]=pushnode;
    }
    else
        return;
    
}

int size(stack* inpStack){
    return inpStack->pos+1;
}

tree_node* top(stack* inpStack){
    return (tree_node*)inpStack->vals[inpStack->pos];
}

tree_node* pop(stack* inpStack){
    if(inpStack->pos==-1){
        return NULL;
    }
    
    else{
        inpStack->pos--;
        return (tree_node*)inpStack->vals[inpStack->pos+1];
    }
    
}

tree_node* makenode(tagged_union inputtag){
    tree_node* newnode = (tree_node*) malloc(sizeof(tree_node));
    newnode->val=inputtag;
    newnode->child=NULL;
    newnode->no_child=0;
    return newnode;
}

tree_node* addsinglenode( tree_node* head, tagged_union newtag){

    tree_node* newnode = makenode(newtag);

    head->child = realloc(head->child, (head->no_child+1)*(sizeof(node *)) );
    head->child[head->no_child] = newnode; 
    head->no_child++;

    return newnode;
}