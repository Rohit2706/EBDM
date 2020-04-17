
// This file implements the symbol table data structure for SymbolTable.h

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "SymbolTable.h"

// Function definations

// 1. To create symbol table
SYMBOL_TABLE* st_create(int size, char* name, SYMBOL_TABLE* parent){

    SYMBOL_TABLE *newtable = (SYMBOL_TABLE *)malloc(sizeof(SYMBOL_TABLE));
    newtable->table = (STEntry **)malloc(sizeof(STEntry*) * size);
    newtable->parent = parent;
    strcpy(newtable->name,name);
    for(int i=0;i<size;i++)
        newtable->table[i]=NULL;

    newtable->size = size;
    newtable->capacity = 0;
    newtable->curr_offset = 0;
    newtable->no_child = 0;
    newtable->child = (SYMBOL_TABLE **)malloc(sizeof(SYMBOL_TABLE*) * 10);

    for(int i=0;i<10;i++)
        newtable->child[i] = NULL;
    return newtable;

}

// 2. To design hash function.
// About the hash function:
// If key is c1c2c3 where c1, c2, c3 are characters
// Then the hash value is decimal equivalent of
// [bit(c1) bit(c2) bit(c3)] % (size of hash table)
// where bit(c) is the bit representation of the ASCII value of c

int st_hash_func(SYMBOL_TABLE *ht, char* key ){

    int hashvalue=0,i=0;

    while(hashvalue<INT_MAX && i< strlen(key) ){
        hashvalue = hashvalue << 8;
        hashvalue +=key[i];
        i++;
    }

    return (hashvalue%(ht->size));
}


// 3. to create the key-value STEntry
STEntry* st_create_pair(char* key, STValue* val){

    STEntry *newpair = malloc(sizeof(STEntry));
    newpair->value = val;
    newpair->key = strdup(key);

    return newpair;
}

// 4. To insert an entry in the SYMBOL_TABLE
void insert_stentry(SYMBOL_TABLE *ht, char* key, STValue* val){

    if(ht->capacity == ht->size-1){
        ht->size += 5;
        ht->table = (STEntry **)realloc(ht->table, sizeof(STEntry*) * (ht->size));
    }

    ht->capacity++;

    int hashval = st_hash_func(ht,key);

    STEntry *end=NULL;
    STEntry *next = ht->table[hashval];
    
    while(next!=NULL && next->key!=NULL && strcmp(key,next->key) > 0){
        end = next;
        next = next->next;
    }

    STEntry *newpair = st_create_pair(key,val);

    if(next == ht->table[hashval]){
        newpair->next = next;
        ht->table[hashval] = newpair;
        }
        else if(next == NULL){
            end->next = newpair; 
        }   else{
                newpair->next = next;
                end->next = newpair;
        }

}

// 5. To get the value given a key
STValue* get_stvalue(SYMBOL_TABLE *ht, char* key){

    STEntry* pair = NULL;
    int hashvalue = st_hash_func(ht,key);

    pair = ht->table[hashvalue];
    while(pair!=NULL && pair->key !=NULL && strcmp(key,pair->key) > 0){
        pair = pair->next;
    }

    if( pair == NULL||pair->key == NULL||strcmp( key, pair->key ) != 0 ) {
		return NULL;
    }
    return pair->value;
    
}

void addSTchild(SYMBOL_TABLE* parent, SYMBOL_TABLE* newchild){
    parent->no_child++;
    parent->child[parent->no_child-1] = newchild;
}