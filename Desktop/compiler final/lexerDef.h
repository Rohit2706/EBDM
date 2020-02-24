// This file implements data structures needed for the lexical analyser(lexer.c)

#define HASH_SIZE 33
#define INT_MAX 2147483647

// TOKEN is an enum variable for possible tokens in the ERPLAG language
#ifndef tokens
#define tokens
typedef enum{EPSILON, DOLLAR,INTEGER,REAL,BOOLEAN,OF,ARRAY,START,END,DECLARE,MODULE,DRIVER,PROGRAM,GET_VALUE,PRINT,USE,
             WITH,PARAMETERS,TRUE,FALSE,TAKES,INPUT,RETURNS,AND,OR,FOR,IN,SWITCH,CASE,BREAK,DEFAULT,WHILE,
             PLUS, MINUS, MUL, DIV, LT, LE, GE, GT, EQ, NE, DRIVERDEF, DRIVERENDDEF, DEF, ENDDEF, COLON, RANGEOP, 
             SEMICOL, COMMA, ASSIGNOP, SQBO, SQBC, BO, BC, ID, NUM, RNUM
             } TOKEN;
             
#endif

          
// VALUE is a tagged union that stores the numeric value for lexemes of type NUM(tag=1) and RNUM(tage=2). For others VALUE is displayed as none(tag=0)
typedef union{
	unsigned int num_value;
	float rnum_value;
}VALUE;

// TokenInfo contains all the required information about the tokenized lexeme, to be returned to the parser on demand.
typedef struct{
	TOKEN token;
	char lexeme[25];
	unsigned int line_no;
	int length;
	VALUE value;
	int tag;
}TokenInfo;


// Data Structure for Hash Table for Keywords (implemented in Hash_table.c)

// Datapair is a structure that stores the key-value pair
typedef struct Datapair {
   char* key;   
   TOKEN value;
   struct Datapair *next;
}Datapair;

// Hashtable is a data structure containing all the Datapairs 
typedef struct {
    int size;
    Datapair **table;
}hashtable;

// Function declarations for has table
hashtable* hashtable_create(int size);
int hash_func(hashtable *ht, char* key );
Datapair* create_pair(char* key, TOKEN val);
void insert_entry(hashtable *ht, char* key, TOKEN val);
TOKEN get_value(hashtable *ht,char* key);
void add_keywords(hashtable *ht);