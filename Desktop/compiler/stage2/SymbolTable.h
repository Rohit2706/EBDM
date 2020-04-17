
#define INT_MAX 2147483647

#ifndef tokens
#define tokens
typedef enum{EPSILON, DOLLAR,INTEGER,REAL,BOOLEAN,OF,ARRAY,START,END,DECLARE,MODULE,DRIVER,PROGRAM,GET_VALUE,PRINT,USE,
             WITH,PARAMETERS,TRUE,FALSE,TAKES,INPUT,RETURNS,AND,OR,FOR,IN,SWITCH,CASE,BREAK,DEFAULT,WHILE,
             PLUS, MINUS, MUL, DIV, LT, LE, GE, GT, EQ, NE, DRIVERDEF, DRIVERENDDEF, DEF, ENDDEF, COLON, RANGEOP, 
             SEMICOL, COMMA, ASSIGNOP, SQBO, SQBC, BO, BC, ID, NUM, RNUM
             } TOKEN;
#endif
             
// TYPE_STRUCT structure to store datatype, range in case of arrays and scopes in case of modules
typedef struct TYPE_STRUCT{
  TOKEN dtype;
  int isStatic;
  int begin;
  int end;
  int isArray;
  char* begins;
  char* ends;
}TYPE_STRUCT;

// To encapsulate the data stored in symbol table
typedef struct STValue{
	TYPE_STRUCT type;
  int scope[2];
  int offset;
  int width;
}STValue;

// A row entry in a Symbol Table
typedef struct STEntry{
  char* key;   
  STValue* value;
  struct STEntry *next;
}STEntry;

// Hash Table structure for symbol table
typedef struct SYMBOL_TABLE{
  int size;
  int capacity;
  char name[25];
  int endscope;
  int curr_offset;
  STEntry **table;
  struct SYMBOL_TABLE* parent; 
  struct SYMBOL_TABLE ** child;
  int no_child;
}SYMBOL_TABLE;
 
// Function Prototypes

SYMBOL_TABLE* st_create(int size, char* name, SYMBOL_TABLE* parent);
int st_hash_func(SYMBOL_TABLE *ht, char* key );
STEntry* st_create_pair(char* key, STValue* val);
void insert_stentry(SYMBOL_TABLE *ht, char* key, STValue* val);
STValue* get_stvalue(SYMBOL_TABLE *ht, char* key);
void addSTchild(SYMBOL_TABLE* parent, SYMBOL_TABLE* newchild);