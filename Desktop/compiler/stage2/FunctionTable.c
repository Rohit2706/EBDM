
// This file implements the symbol table data structure for SymbolTable.h

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "FunctionTable.h"

// Function definations

// 1. To create function table
FUNCTION_TABLE* ft_create(int size){

    FUNCTION_TABLE *newtable = (FUNCTION_TABLE *)malloc(sizeof(FUNCTION_TABLE));
    newtable->table = (FTEntry **)malloc(sizeof(FTEntry*) * size);

    for(int i=0;i<size;i++)
        newtable->table[i]=NULL;

    newtable->size = size;
    newtable->capacity = 0;
    return newtable;

}

// 2. To design hash function.
// About the hash function:
// If key is c1c2c3 where c1, c2, c3 are characters
// Then the hash value is decimal equivalent of
// [bit(c1) bit(c2) bit(c3)] % (size of hash table)
// where bit(c) is the bit representation of the ASCII value of c

int ft_hash_func(FUNCTION_TABLE *ht, char* key){

    int hashvalue=0,i=0;

    while(hashvalue<INT_MAX && i< strlen(key) ){
        hashvalue = hashvalue << 8;
        hashvalue +=key[i];
        i++;
    }

    return (hashvalue%(ht->size));
}


// 3. to create the key-value FTEntry
FTEntry* ft_create_pair(char* key, FTValue* val){

    FTEntry *newpair = malloc(sizeof(FTEntry));
    newpair->value = val;
    newpair->key = strdup(key);

    return newpair;
}

// 4. To insert an entry in the FUNCTION_TABLE
void insert_FTEntry(FUNCTION_TABLE *ht, char* key, FTValue* val){

    if(ht->capacity == ht->size){
        ht->size += 5;
        ht->table = (FTEntry **)realloc(ht->table, sizeof(FTEntry*) * ht->size);
    }

    ht->capacity++;

    int hashval = ft_hash_func(ht,key);

    FTEntry *end=NULL;
    FTEntry *next = ht->table[hashval];
    
    while(next!=NULL && next->key!=NULL && strcmp(key,next->key) > 0){
        end = next;
        next = next->next;
    }

    FTEntry *newpair = ft_create_pair(key,val);

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
FTValue* get_ftvalue(FUNCTION_TABLE *ht, char* key){

    FTEntry* pair = NULL;
    int hashvalue =ft_hash_func(ht,key);

    pair = ht->table[hashvalue];
    while(pair!=NULL && pair->key !=NULL && strcmp(key,pair->key) > 0){
        pair = pair->next;
    }

    if( pair == NULL||pair->key == NULL||strcmp( key, pair->key ) != 0 ) {
		return NULL;
    }
    return pair->value;
    
}

/*
int main(){
    FTValue* ptr = (FTValue*)malloc(sizeof(FTValue));
    ptr->functionState = DEFINED;
    ptr->flag=3;
    FUNCTION_TABLE* ht = ft_create(2);
    insert_FTEntry(ht, "func1", ptr);
    ptr = get_ftvalue(ht, "func1");
    printf("%d\n%d\n",ptr->functionState, ptr->flag);
    return 0;
}*/