// This file implements the mapping table for terminals and non-terminals

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAPTABLE_SIZE 91
#define INT_MAX 2147483647


#ifndef tokens
#define tokens
typedef enum{EPSILON, DOLLAR,INTEGER,REAL,BOOLEAN,OF,ARRAY,START,END,DECLARE,MODULE,DRIVER,PROGRAM,GET_VALUE,PRINT,USE,
             WITH,PARAMETERS,TRUE,FALSE,TAKES,INPUT,RETURNS,AND,OR,FOR,IN,SWITCH,CASE,BREAK,DEFAULT,WHILE,
             PLUS, MINUS, MUL, DIV, LT, LE, GE, GT, EQ, NE, DRIVERDEF, DRIVERENDDEF, DEF, ENDDEF, COLON, RANGEOP, 
             SEMICOL, COMMA, ASSIGNOP, SQBO, SQBC, BO, BC, ID, NUM, RNUM
             } TOKEN;
#endif

#ifndef non_terminal
#define non_terminal
typedef enum{PROGRAM_NT,MODULEDECLARATIONS,MODULEDECLARATION,OTHERMODULES,DRIVERMODULE,MODULE_NT,RET,INPUT_PLIST,
             INPUT_PLIST_1,OUTPUT_PLIST,OUTPUT_PLIST_1,DATATYPE,TYPE,MODULEDEF,STATEMENTS,STATEMENT,IOSTMT,VAR,
             VAR_ID_NUM,BOOLCONSTT,WHICHID,SIMPLESTMT,ASSIGNMENTSTMT,WHICHSTMT,LVALUEIDSTMT,LVALUEARRSTMT,INDEX,
             MODULEREUSESTMT,OPTIONAL,IDLIST,IDLIST_1,EXPRESSION,U,U_1,ARMORBOOL,N7,ANYTERM,N8,ARITHMETICEXPR,
             ARITHMETICEXPR_1,TERM,TERM_1,FACTOR,OP1,OP2,LOGICALOP,RELATIONALOP,DECLARESTMT,CONDITIONALSTMT,CASESTMT,
             CASESTMT_1,VALUE_NT,DEFAULT_NT,ITERATIVESTMT,RANGE_ARRAYS,RANGE} NON_TERMINAL;
#endif

// Symbol represents each symbol in the grammar rule and is either a terminal(token) or a non-termianl
typedef union symbol{

    NON_TERMINAL nt_val;
    TOKEN t_val;
}Symbol;

// Datapair is a structure that stores the key-value pair
typedef struct Datapair2 {
   char* key;   
   Symbol value;
   int tag;
   struct Datapair2 *next;
}Datapair2;

// hashtable is a data structure containing all the Datapairs (required mapping table)
typedef struct {
    int size;
    Datapair2 **table;
}hashtable2;

typedef struct{
  Symbol value;
  int tag;
}tagged_union;

// Function prototypes
hashtable2* mappingtable_create(int size);
int mapping_hash_func(hashtable2 *ht, char* key );
Datapair2* create_pair_terminal(char* key, TOKEN val);
Datapair2* create_pair_nonterminal(char* key, NON_TERMINAL val);
void insert_entry_terminal(hashtable2 *ht, char* key, TOKEN val);
void insert_entry_nonterminal(hashtable2 *ht, char* key, NON_TERMINAL val);
tagged_union mapping_get_value(hashtable2 *ht,char* key);
void add_terminals(hashtable2 *ht);
void add_nonterminals(hashtable2 *ht);

