//Group No. 7
//ANIRUDH GOYAL 2017A7PS0031P
//ANISHKUMAR SS 2017A7PS0069P
//ROHIT JAIN 2017A7PS0122P
//ADITYA SAXENA 2017A7PS0166P

// This file implements the hash table data structure for lexerDef.h

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "lexerDef.h"

// Function definations

// 1. To create hash table
hashtable* hashtable_create(int size){

    hashtable *newtable = (hashtable *)malloc(sizeof(hashtable));
    newtable->table = (Datapair **)malloc(sizeof(Datapair*) * size);

    for(int i=0;i<size;i++)
        newtable->table[i]=NULL;

    newtable->size = size;

    return newtable;

}

// 2. To design hash function.
// About the hash function:
// If key is c1c2c3 where c1, c2, c3 are characters
// Then the hash value is decimal equivalent of
// [bit(c1) bit(c2) bit(c3)] % (size of hash table)
// where bit(c) is the bit representation of the ASCII value of c

int hash_func(hashtable *ht, char* key ){

    int hashvalue=0,i=0;

    while(hashvalue<INT_MAX && i< strlen(key) ){
        hashvalue = hashvalue << 8;
        hashvalue +=key[i];
        i++;
    }

    return (hashvalue%(ht->size));
}


// 3. to create the key-value Datapair
Datapair* create_pair(char* key, TOKEN val){

    Datapair *newpair = malloc(sizeof(Datapair));
    newpair->value = val;
    newpair->key = strdup(key);

    return newpair;
}

// 4. To insert an entry in the hashtable
void insert_entry(hashtable *ht, char* key, TOKEN val){

    
    int hashval =hash_func(ht,key);

    Datapair *end=NULL;
    Datapair *next = ht->table[hashval];
    
    while(next!=NULL && next->key!=NULL && strcmp(key,next->key) > 0){
        end = next;
        next = next->next;
    }

    Datapair *newpair = create_pair(key,val);

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
TOKEN get_value(hashtable *ht,char* key){

    Datapair* pair = NULL;
    int hashvalue =hash_func(ht,key);

    pair = ht->table[hashvalue];
    while(pair!=NULL && pair->key !=NULL && strcmp(key,pair->key) > 0){
        pair = pair->next;
    }

    if( pair == NULL||pair->key == NULL||strcmp( key, pair->key ) != 0 ) {
		return ID;
    }
    return pair->value;
    
}

// 6. To populate our hash table with keywords
void add_keywords(hashtable *ht){

    insert_entry(ht,"integer",INTEGER);
    insert_entry(ht,"real",REAL);
    insert_entry(ht,"boolean",BOOLEAN);
    insert_entry(ht,"of",OF);
    insert_entry(ht,"array",ARRAY);
    insert_entry(ht,"start",START);
    insert_entry(ht,"end",END);
    insert_entry(ht,"declare",DECLARE);
    insert_entry(ht,"module",MODULE);
    insert_entry(ht,"driver",DRIVER);
    insert_entry(ht,"program",PROGRAM);
    insert_entry(ht,"get_value",GET_VALUE);
    insert_entry(ht,"print",PRINT);
    insert_entry(ht,"use",USE);
    insert_entry(ht,"with",WITH);
    insert_entry(ht,"parameters",PARAMETERS);
    insert_entry(ht,"true",TRUE);
    insert_entry(ht,"false",FALSE);
    insert_entry(ht,"takes",TAKES);
    insert_entry(ht,"input",INPUT);
    insert_entry(ht,"returns",RETURNS);
    insert_entry(ht,"AND",AND);
    insert_entry(ht,"OR",OR);
    insert_entry(ht,"for",FOR);
    insert_entry(ht,"in",IN);
    insert_entry(ht,"switch",SWITCH);
    insert_entry(ht,"case",CASE);
    insert_entry(ht,"break",BREAK);
    insert_entry(ht,"default",DEFAULT);
    insert_entry(ht,"while",WHILE);
}