
//Group No. 7
//ANIRUDH GOYAL 2017A7PS0031P
//ANISHKUMAR SS 2017A7PS0069P
//ROHIT JAIN 2017A7PS0122P
//ADITYA SAXENA 2017A7PS0166P


// This file implements the mapping table for terminals and non-terminals

#include "mappingTable.h"

// Function Definations

// 1. To create hash table
hashtable2* mappingtable_create(int size){

    hashtable2 *newtable = (hashtable2 *)malloc(sizeof(hashtable2));
    newtable->table = (Datapair2 **)malloc(sizeof(Datapair2*) * size);

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

int mapping_hash_func(hashtable2 *ht, char* key ){

    int hashvalue=0,i=0;

    while(hashvalue<INT_MAX && i< strlen(key) ){
        hashvalue = hashvalue << 8;
        hashvalue +=key[i];
        i++;
    }

    return (hashvalue%(ht->size));
}


// 3. to create the key-value Datapair2
Datapair2* create_pair_terminal(char* key, TOKEN val){

    Datapair2 *newpair = malloc(sizeof(Datapair2));
    newpair->value.t_val = val;
    newpair->key = strdup(key);
    newpair->tag = 1;
    return newpair;
}

Datapair2* create_pair_nonterminal(char* key, NON_TERMINAL val){

    Datapair2 *newpair = malloc(sizeof(Datapair2));
    newpair->value.nt_val = val;
    newpair->key = strdup(key);
    newpair->tag = 2;
    return newpair;
}

// 4. To insert an entry in the hashtable2
void insert_entry_terminal(hashtable2 *ht, char* key, TOKEN val){

    
    int hashval =mapping_hash_func(ht,key);

    Datapair2 *end=NULL;
    Datapair2 *next = ht->table[hashval];
    
    while(next!=NULL && next!=(Datapair2 *)(0x20) && next->key!=NULL && strcmp(key,next->key) > 0){
        end = next;
        next = next->next;
    }

    Datapair2 *newpair = create_pair_terminal(key,val);

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

void insert_entry_nonterminal(hashtable2 *ht, char* key, NON_TERMINAL val){

    
    int hashval =mapping_hash_func(ht,key);

    Datapair2 *end=NULL;
    Datapair2 *next = ht->table[hashval];
    
    while(next!=NULL && next!=(Datapair2 *)(0x20) && next->key!=NULL && strcmp(key,next->key) > 0){
        end = next;
        next = next->next;
    }

    Datapair2 *newpair = create_pair_nonterminal(key,val);

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
tagged_union mapping_get_value(hashtable2 *ht,char* key){

    Datapair2* pair = NULL;
    int hashvalue =mapping_hash_func(ht,key);

    pair = ht->table[hashvalue];
    while(pair!=NULL && pair->key !=NULL && strcmp(key,pair->key) > 0){
        pair = pair->next;
    }
    tagged_union T;
    T.tag = pair->tag;
    T.value = pair->value;
    return T;
}

// 6. To add terminals and non-terminals
void add_terminals(hashtable2 *ht){
    insert_entry_terminal(ht,"PLUS",PLUS);
    insert_entry_terminal(ht,"MINUS",MINUS);
    insert_entry_terminal(ht,"MUL",MUL);
    insert_entry_terminal(ht,"DIV",DIV);
    insert_entry_terminal(ht,"LT",LT);
    insert_entry_terminal(ht,"LE",LE);
    insert_entry_terminal(ht,"GE",GE);
    insert_entry_terminal(ht,"GT",GT);
    insert_entry_terminal(ht,"EQ",EQ);
    insert_entry_terminal(ht,"NE",NE);
    insert_entry_terminal(ht,"DRIVERDEF",DRIVERDEF);
    insert_entry_terminal(ht,"DRIVERENDDEF",DRIVERENDDEF);
    insert_entry_terminal(ht,"DEF",DEF);
    insert_entry_terminal(ht,"ENDDEF",ENDDEF);
    insert_entry_terminal(ht,"COLON",COLON);
    insert_entry_terminal(ht,"RANGEOP",RANGEOP);
    insert_entry_terminal(ht,"SEMICOL",SEMICOL);
    insert_entry_terminal(ht,"COMMA",COMMA);
    insert_entry_terminal(ht,"ASSIGNOP",ASSIGNOP);
    insert_entry_terminal(ht,"SQBO",SQBO);
    insert_entry_terminal(ht,"SQBC",SQBC);
    insert_entry_terminal(ht,"BO",BO);
    insert_entry_terminal(ht,"BC",BC);
    insert_entry_terminal(ht,"ID",ID);
    insert_entry_terminal(ht,"NUM",NUM);
    insert_entry_terminal(ht,"RNUM",RNUM);
    insert_entry_terminal(ht,"EPSILON",EPSILON);
    insert_entry_terminal(ht,"DOLLAR",DOLLAR);
    insert_entry_terminal(ht,"INTEGER",INTEGER);
    insert_entry_terminal(ht,"REAL",REAL);
    insert_entry_terminal(ht,"BOOLEAN",BOOLEAN);
    insert_entry_terminal(ht,"OF",OF);
    insert_entry_terminal(ht,"ARRAY",ARRAY);
    insert_entry_terminal(ht,"START",START);
    insert_entry_terminal(ht,"END",END);
    insert_entry_terminal(ht,"DECLARE",DECLARE);
    insert_entry_terminal(ht,"MODULE",MODULE);
    insert_entry_terminal(ht,"DRIVER",DRIVER);
    insert_entry_terminal(ht,"PROGRAM",PROGRAM);
    insert_entry_terminal(ht,"GET_VALUE",GET_VALUE);
    insert_entry_terminal(ht,"PRINT",PRINT);
    insert_entry_terminal(ht,"USE",USE);
    insert_entry_terminal(ht,"WITH",WITH);
    insert_entry_terminal(ht,"PARAMETERS",PARAMETERS);
    insert_entry_terminal(ht,"TRUE",TRUE);
    insert_entry_terminal(ht,"FALSE",FALSE);
    insert_entry_terminal(ht,"TAKES",TAKES);
    insert_entry_terminal(ht,"INPUT",INPUT);
    insert_entry_terminal(ht,"RETURNS",RETURNS);
    insert_entry_terminal(ht,"AND",AND);
    insert_entry_terminal(ht,"OR",OR);
    insert_entry_terminal(ht,"FOR",FOR);
    insert_entry_terminal(ht,"IN",IN);
    insert_entry_terminal(ht,"SWITCH",SWITCH);
    insert_entry_terminal(ht,"CASE",CASE);
    insert_entry_terminal(ht,"BREAK",BREAK);
    insert_entry_terminal(ht,"DEFAULT",DEFAULT);
    insert_entry_terminal(ht,"WHILE",WHILE);
}


void add_nonterminals(hashtable2 *ht){

     insert_entry_nonterminal(ht,"program",PROGRAM_NT);
     insert_entry_nonterminal(ht,"moduleDeclarations",MODULEDECLARATIONS);
     insert_entry_nonterminal(ht,"moduleDeclaration",MODULEDECLARATION);
     insert_entry_nonterminal(ht,"otherModules",OTHERMODULES);
     insert_entry_nonterminal(ht,"driverModule",DRIVERMODULE);
     insert_entry_nonterminal(ht,"module",MODULE_NT);
     insert_entry_nonterminal(ht,"ret",RET);
     insert_entry_nonterminal(ht,"input_plist",INPUT_PLIST);
     insert_entry_nonterminal(ht,"input_plist_1",INPUT_PLIST_1);
     insert_entry_nonterminal(ht,"output_plist",OUTPUT_PLIST);
     insert_entry_nonterminal(ht,"output_plist_1",OUTPUT_PLIST_1);
     insert_entry_nonterminal(ht,"dataType",DATATYPE);
     insert_entry_nonterminal(ht,"type",TYPE);
     insert_entry_nonterminal(ht,"moduleDef",MODULEDEF);
     insert_entry_nonterminal(ht,"statements",STATEMENTS);
     insert_entry_nonterminal(ht,"statement",STATEMENT);
     insert_entry_nonterminal(ht,"ioStmt",IOSTMT);
     insert_entry_nonterminal(ht,"var",VAR);
     insert_entry_nonterminal(ht,"var_id_num",VAR_ID_NUM);
     insert_entry_nonterminal(ht,"boolConstt",BOOLCONSTT);
     insert_entry_nonterminal(ht,"whichId",WHICHID);
     insert_entry_nonterminal(ht,"simpleStmt",SIMPLESTMT);
     insert_entry_nonterminal(ht,"assignmentStmt",ASSIGNMENTSTMT);
     insert_entry_nonterminal(ht,"whichStmt",WHICHSTMT);
     insert_entry_nonterminal(ht,"lvalueIDStmt",LVALUEIDSTMT);
     insert_entry_nonterminal(ht,"lvalueARRStmt",LVALUEARRSTMT);
     insert_entry_nonterminal(ht,"index",INDEX);
     insert_entry_nonterminal(ht,"moduleReuseStmt",MODULEREUSESTMT);
     insert_entry_nonterminal(ht,"optional",OPTIONAL);
     insert_entry_nonterminal(ht,"idList",IDLIST);
     insert_entry_nonterminal(ht,"idList_1",IDLIST_1);
     insert_entry_nonterminal(ht,"expression",EXPRESSION);
     insert_entry_nonterminal(ht,"U",U);
     insert_entry_nonterminal(ht,"U_1",U_1);
     insert_entry_nonterminal(ht,"armOrbool",ARMORBOOL);
     insert_entry_nonterminal(ht,"N7",N7);
     insert_entry_nonterminal(ht,"AnyTerm",ANYTERM);
     insert_entry_nonterminal(ht,"N8",N8);
     insert_entry_nonterminal(ht,"arithmeticExpr",ARITHMETICEXPR);
     insert_entry_nonterminal(ht,"arithmeticExpr_1",ARITHMETICEXPR_1);
     insert_entry_nonterminal(ht,"term",TERM);
     insert_entry_nonterminal(ht,"term_1",TERM_1);
     insert_entry_nonterminal(ht,"factor",FACTOR);
     insert_entry_nonterminal(ht,"op1",OP1);
     insert_entry_nonterminal(ht,"op2",OP2);
     insert_entry_nonterminal(ht,"logicalOp",LOGICALOP);
     insert_entry_nonterminal(ht,"relationalOp",RELATIONALOP);
     insert_entry_nonterminal(ht,"declareStmt",DECLARESTMT);
     insert_entry_nonterminal(ht,"conditionalStmt",CONDITIONALSTMT);
     insert_entry_nonterminal(ht,"caseStmt",CASESTMT);
     insert_entry_nonterminal(ht,"caseStmt_1",CASESTMT_1);
     insert_entry_nonterminal(ht,"value",VALUE_NT);
     insert_entry_nonterminal(ht,"default",DEFAULT_NT);
     insert_entry_nonterminal(ht,"iterativeStmt",ITERATIVESTMT);
     insert_entry_nonterminal(ht,"range_arrays",RANGE_ARRAYS);
     insert_entry_nonterminal(ht,"range",RANGE);

}