#define NT_SIZE 56
#define TOKEN_SIZE 58

// TOKEN is an enum variable for possible tokens in the ERPLAG language
#ifndef tokens
#define tokens
typedef enum{EPSILON, DOLLAR,INTEGER,REAL,BOOLEAN,OF,ARRAY,START,END,DECLARE,MODULE,DRIVER,PROGRAM,GET_VALUE,PRINT,USE,
             WITH,PARAMETERS,TRUE,FALSE,TAKES,INPUT,RETURNS,AND,OR,FOR,IN,SWITCH,CASE,BREAK,DEFAULT,WHILE,
             PLUS, MINUS, MUL, DIV, LT, LE, GE, GT, EQ, NE, DRIVERDEF, DRIVERENDDEF, DEF, ENDDEF, COLON, RANGEOP, 
             SEMICOL, COMMA, ASSIGNOP, SQBO, SQBC, BO, BC, ID, NUM, RNUM
             } TOKEN;
#endif

// NON_TERMINAL is an enum variable for possible non-terminals in the ERPLAG grammar
#ifndef non_terminal
#define non_terminal
typedef enum{PROGRAM_NT,MODULEDECLARATIONS,MODULEDECLARATION,OTHERMODULES,DRIVERMODULE,MODULE_NT,RET,INPUT_PLIST,
             INPUT_PLIST_1,OUTPUT_PLIST,OUTPUT_PLIST_1,DATATYPE,TYPE,MODULEDEF,STATEMENTS,STATEMENT,IOSTMT,VAR,
             VAR_ID_NUM,BOOLCONSTT,WHICHID,SIMPLESTMT,ASSIGNMENTSTMT,WHICHSTMT,LVALUEIDSTMT,LVALUEARRSTMT,INDEX,
             MODULEREUSESTMT,OPTIONAL,IDLIST,IDLIST_1,EXPRESSION,U,U_1,ARMORBOOL,N7,ANYTERM,N8,ARITHMETICEXPR,
             ARITHMETICEXPR_1,TERM,TERM_1,FACTOR,OP1,OP2,LOGICALOP,RELATIONALOP,DECLARESTMT,CONDITIONALSTMT,CASESTMT,
             CASESTMT_1,VALUE_NT,DEFAULT_NT,ITERATIVESTMT,RANGE_ARRAYS,RANGE} NON_TERMINAL;
#endif

// VALUE is a tagged union that stores the numeric value for lexemes of type NUM(tag=1) and RNUM(tage=2). For others VALUE is displayed as none(tag=0)
#ifndef values
#define values
typedef union{
    unsigned int num_value;
    float rnum_value;
}VALUE;
#endif


typedef struct leaf_node{
    char lexeme[25];
    TYPE type;
    TOKEN t_val;
    VALUE value;
    unsigned int line_no;
    STentry* stptr;
}leaf_node;

typedef struct nonleaf_node{

    char label[25];
    TYPE type;
    NON_TERMINAL nt_val;
    VALUE value;
    unsigned int no_child;
    int scope[2];
    struct ast_node ** child;
    
}nonleaf_node;

typedef union{
    leaf_node lnode;
    nonleaf_node nlnode;
}node_union;

typedef struct ast_node{
    node_union node;
    int tag;
}ast_node;