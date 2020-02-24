// This file implements the lexical analyser

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "lexer.h"
#define buffer_size 512

// Global variables
FILE* file;
char* forward;
int status = 1;
int line_count = 1;
int *flag;
hashtable *ht_keywords;
char *buffer1, *buffer2;

// getStream loads a chunk of size = buffer_size in buffer by reading file. 
void getStream(char* buffer){
	int size = fread(buffer, sizeof(char), buffer_size, file);
	if(size!=buffer_size)
		buffer[size] = '\0';
	forward = buffer;
}

// getNextToken returns next valid Token to the calling function. In case a lexical error it prints error and goes to the next token
TokenInfo getNextToken(){
  TokenInfo newToken;
  newToken.length = 0;
  newToken.tag=0;
  int start = 0;
  char c;
  int* state = &start;

  while(1){
    switch(*state){
    case 0:
        c=getNextChar(newToken.lexeme, &(newToken.length));

        if((c>='a' && c<='z') || (c>='A' && c<='Z')) *state=1;
        else if(c==';') *state=3;
        else if(c>='0' && c<='9') *state=4;
        else if(c=='.') *state=12;
        else if(c=='*') *state=14;
        else if(c=='/') *state=19;
        else if(c==',') *state=20;
        else if(c=='[') *state=21;
        else if(c==']') *state=22;
        else if(c=='=') *state=23;
        else if(c=='!') *state=25;
        else if(c=='(') *state=27;
        else if(c==')') *state=28;
        else if(c=='<') *state=29;
        else if(c=='>') *state=33;
        else if(c==':') *state=37;
        else if(c=='+') *state=40;
        else if(c=='-') *state=41;
        else if(c==' ' || c=='\r' || c=='\t'){ 
          *state=0;
          newToken.length--;
        }
        else if(c=='\n'){ 
          *state=42;
          newToken.length--;
        }
        else{
          return failure(newToken, c);
        }
        break;
    
    case 1:
        c=getNextChar(newToken.lexeme, &(newToken.length));
        if((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9') || c=='_') *state=1;
        else    *state=2;

        break;
    
    case 2:
        retract(newToken.lexeme, &(newToken.length));
          if(newToken.length>20){
            return failure(newToken, c);
          }
        return tokenGen(newToken, get_value(ht_keywords, newToken.lexeme));

        break;
    
    case 3:
        return tokenGen(newToken, SEMICOL);

        break;
    
    case 4:
        c=getNextChar(newToken.lexeme, &(newToken.length));
        if((c>='0' && c<='9'))    *state=4;
        else if(c=='.') *state=5;
        else *state=11;
        break;
    
    case 5:
        c=getNextChar(newToken.lexeme, &(newToken.length));
        if((c>='0' && c<='9'))    *state=6;
        else if(c=='.'){
            retract(newToken.lexeme, &(newToken.length));
            retract(newToken.lexeme, &(newToken.length));
            return tokenGen(newToken, NUM);
        }
        else{
          retract(newToken.lexeme, &(newToken.length));
          return failure(newToken, c);
        }
        break;
        
    case 6:
        c=getNextChar(newToken.lexeme, &(newToken.length));
        if((c>='0' && c<='9'))    *state=6;
        else if(c=='E' || c=='e')   *state=7;
        else *state=10;

        break;
    
    case 7:
        c=getNextChar(newToken.lexeme, &(newToken.length));
        if((c>='0' && c<='9'))    *state=9;
        else if(c=='+' || c=='-')   *state=8;
        else{
          retract(newToken.lexeme, &(newToken.length));
          return failure(newToken, c);
        }
        break;
        
    case 8:
        c=getNextChar(newToken.lexeme, &(newToken.length));
        if((c>='0' && c<='9'))    *state=9;
        else{
          retract(newToken.lexeme, &(newToken.length));
          return failure(newToken, c);
        }
        break;
    
    case 9:
        c=getNextChar(newToken.lexeme, &(newToken.length));
        if((c>='0' && c<='9'))    *state=9;
        else *state=10;

        break;
    
    case 10:
        retract(newToken.lexeme, &(newToken.length));
        return tokenGen(newToken, RNUM);

        break;
    
    case 11:
        retract(newToken.lexeme, &(newToken.length));
        return tokenGen(newToken, NUM);  

        break;
        
    case 12:
        c=getNextChar(newToken.lexeme, &(newToken.length));
        if(c=='.')  *state=13;
        else{
          retract(newToken.lexeme, &(newToken.length));
          return failure(newToken, c);
        }
        break;

    case 13:
        return tokenGen(newToken, RANGEOP);

        break;
    
    case 14:
        c=getNextChar(newToken.lexeme, &(newToken.length));
        if(c=='*'){
          *state=15;
          newToken.length -= 2;
        }
        else *state=18;

        break;
        
    case 15:
          c=getNextChar(newToken.lexeme, &(newToken.length));
         if(c=='*')    *state=16;
         else if(c=='\n'){
            line_count++;
            *state=43;
          }
         else{ 
            *state=15;
            
         }
         newToken.length--;
         break;
    
    case 16:
         c=getNextChar(newToken.lexeme, &(newToken.length));
         if(c=='*'){
            *state=17;
         }
         else if(c=='\n'){
             line_count++;
             *state=43;
             
         }
         else *state=15;
          newToken.length--;
         break;
    
    case 17:
         *state=0;
         break; 

    case 18:
        retract(newToken.lexeme, &(newToken.length));
        return tokenGen(newToken, MUL);

        break;
    
    case 19:
        return tokenGen(newToken, DIV);
        break;
    
    case 20:
        return tokenGen(newToken, COMMA);
        break; 
        
    case 21:
        return tokenGen(newToken, SQBO);
        break; 
        
    case 22:
        return tokenGen(newToken, SQBC);
        break; 
    
    case 23:
        c=getNextChar(newToken.lexeme, &(newToken.length));
        if(c=='=')  *state=24;
        else{
          retract(newToken.lexeme, &(newToken.length));
          return failure(newToken, c);
        }
        break;
    
    case 24:
        return tokenGen(newToken, EQ);
        break;
    
    case 25:
        c=getNextChar(newToken.lexeme, &(newToken.length));
        if(c=='=')  *state=26;
        else{
          retract(newToken.lexeme, &(newToken.length));
          return failure(newToken, c);
        }
        break;
    
    case 26:
        return tokenGen(newToken, NE);
        break; 
        
    case 27:
        return tokenGen(newToken, BO);
        break; 
        
    case 28:
        return tokenGen(newToken, BC);
        break; 
        
    case 29:
        c=getNextChar(newToken.lexeme, &(newToken.length));
        if(c=='<')  *state=30;
        else if(c=='=') *state=31;
        else    *state=32;
        break;
    
    case 30:
        c=getNextChar(newToken.lexeme, &(newToken.length));
        if(c=='<')  *state = 44;
        else  *state = 45;
        break; 
    
    case 31:
        return tokenGen(newToken, LE);
        break; 
        
    case 32:
        retract(newToken.lexeme, &(newToken.length));
        return tokenGen(newToken, LT);
        break; 
    
    case 33:
        c=getNextChar(newToken.lexeme, &(newToken.length));
        if(c=='>')  *state=34;
        else if(c=='=') *state=35;
        else    *state=36;
        break; 
    
    case 34:
        c=getNextChar(newToken.lexeme, &(newToken.length));
        if(c=='>')  *state=46;
        else *state=47;
        break; 
    
    case 35:
        return tokenGen(newToken, GE);
        break; 
        
    case 36:
        retract(newToken.lexeme, &(newToken.length));
        return tokenGen(newToken, GT);
        break; 
        
    case 37:
        c=getNextChar(newToken.lexeme, &(newToken.length));
        if(c=='=')  *state=38;
        else    *state=39;
        break; 
    
    case 38:
        return tokenGen(newToken, ASSIGNOP);
        break; 
        
    case 39:
        retract(newToken.lexeme, &(newToken.length));
        return tokenGen(newToken, COLON);
        break; 
    
    case 40:
        return tokenGen(newToken, PLUS);
        break; 
    
    case 41:
        return tokenGen(newToken, MINUS);
        break;   
    
    case 42:
        line_count++;
        *state=0;

        break;

    case 43:
        c=getNextChar(newToken.lexeme, &(newToken.length));
        if(c=='\n'){
          line_count++;
          *state=43;
        }
        else if(c=='*') *state = 16;
        else *state=15;
        newToken.length--;
        break;

    case 44:
      return tokenGen(newToken, DRIVERDEF);
      break; 

    case 45:
      retract(newToken.lexeme, &(newToken.length));
      return tokenGen(newToken, DEF);

      break;

    case 46:
      return tokenGen(newToken, DRIVERENDDEF);
      break;

    case 47:
      retract(newToken.lexeme, &(newToken.length));
      return tokenGen(newToken, ENDDEF);

      break;
  }
}
}

// removeComments removes comments from input source code while preserving the line code
void removeComments(char *testcaseFile){
  while((*testcaseFile)!='\0'){
    
    if(*testcaseFile=='*' && *(testcaseFile+1)=='*'){
      testcaseFile+=2;
      while(!(*testcaseFile=='*' && *(testcaseFile+1)=='*')){
      	if(*testcaseFile=='\n')
          printf("%c", *testcaseFile);
        testcaseFile++;
      }
      testcaseFile+=2;
    }
    else{
      printf("%c", *testcaseFile);
      testcaseFile++;
    } 
  }
}

// driver is called once initially to initialize all the required data structures
void lexer_driver(char* filename){
  file = NULL;
  file = fopen(filename,"r");
  if(file==NULL){
    printf("FILE NOT FOUND\n");
    return;
  }
  flag= (int*) malloc(sizeof(int));
  
  buffer1 = (char*) malloc((buffer_size+1)*sizeof(char));
  buffer2 = (char*) malloc((buffer_size+1)*sizeof(char));
  buffer1[buffer_size] = EOF;
  buffer2[buffer_size] = EOF;

  ht_keywords = hashtable_create(HASH_SIZE);
  add_keywords(ht_keywords);

  getStream(buffer1);
}

// enddriver frees the dynamically allocated memory and closes files
void lexer_enddriver(){
  for(int i=0;i<HASH_SIZE;i++)
        free(ht_keywords->table[i]);
  free(ht_keywords->table);
  free(ht_keywords);
  fclose(file);
  free(buffer1);
  free(buffer2);
  free(flag);
}

// UTILITY FUNCTIONS

// getNextChar returns next character in the buffer stream. If buffer stream is consumed it loads another chunck in the second buffer

char getNextChar(char* lexeme, int* length){
    
  if(*forward !=EOF){
      forward++;
      lexeme[*length]=*(forward-1);
      (*length)++;
      return *(forward-1);
  }
  
  if(feof(file))
      return '\0';
  
  if(*flag==1){
      *flag=0;
      if(forward==buffer1+buffer_size){
          forward=buffer2;
          forward++;
          lexeme[*length]=*(forward-1);
          (*length)++;
          return *(forward-1);
      }
      else if(forward==buffer2+buffer_size){
          forward=buffer1;
          forward++;
          lexeme[*length]=*(forward-1);
          (*length)++;
          return *(forward-1);
      }
  }

  if(status==1){
      getStream(buffer2);
  }
  else{
      getStream(buffer1);
  }
  
  status = status^1;

  forward++;
  lexeme[*length]=*(forward-1);
  (*length)++;
  return *(forward-1);
}


// tokenGen generates a TokenInfo structure instance to be returned to the parser

TokenInfo tokenGen(TokenInfo newToken, TOKEN token_name){
    newToken.lexeme[newToken.length] = '\0';
    newToken.token = token_name;
    newToken.line_no = line_count;

    if(token_name == NUM){
      (newToken.value).num_value = atoi(newToken.lexeme);
      newToken.tag = 1;
    }
    else if(token_name == RNUM){
      (newToken.value).rnum_value = atof(newToken.lexeme);
      newToken.tag = 2;
    }

    return newToken;
}

// retract function retracts by 1 character

void retract(char* lexeme, int* length){
    
   if(forward==buffer2){
        *flag=1;
        forward= buffer1+ buffer_size-1;
        *length=*length-1;
    }
    
    else if(forward==buffer1){
        *flag=1;
        forward= buffer2+ buffer_size-1;
        *length=*length-1;
    }
    
    else{
        forward=forward-1;
        *length=*length-1;
    }
    
    lexeme[*length] = '\0';
}

// failure handles the cases when the program enters a trap state or end of file is reached and prints the errors

TokenInfo failure(TokenInfo newToken, char ch){
  if(ch=='\0')
    return tokenGen(newToken, DOLLAR);
  newToken.lexeme[newToken.length] = '\0';
  newToken.line_no = line_count;
  printf("Found LEXICAL ERROR at line %d: invalid input '%s'\n",newToken.line_no, newToken.lexeme);
  return getNextToken();
}

// It is a utility function to convert token enum to string for printing output
const char* convert_token_lexer(TOKEN sym){
    switch(sym)
    {
        case PLUS: return "PLUS" ; break;
        case MINUS: return "MINUS" ; break;
        case MUL: return "MUL" ; break;
        case DIV: return "DIV" ; break;
        case LT: return "LT" ; break;
        case LE: return "LE" ; break;
        case GE: return "GE" ; break;
        case GT: return "GT" ; break;
        case EQ: return "EQ" ; break;
        case NE: return "NE" ; break;
        case DEF: return "DEF" ; break;
        case ENDDEF: return "ENDDEF" ; break;
        case DRIVERDEF: return "DRIVERDEF" ; break;
        case DRIVERENDDEF: return "DRIVERENDDEF" ; break;
        case COLON: return "COLON" ; break;
        case RANGEOP: return "RANGEOP" ; break;
        case SEMICOL: return "SEMICOL" ; break;
        case COMMA: return "COMMA" ; break;
        case ASSIGNOP: return "ASSIGNOP" ; break;
        case SQBO: return "SQBO" ; break;
        case SQBC: return "SQBC" ; break;
        case BO: return "BO" ; break;
        case BC: return "BC" ; break;
        case ID: return "ID" ; break;
        case NUM: return "NUM" ; break;
        case RNUM: return "RNUM" ; break;
        case INTEGER: return "INTEGER" ; break;
        case REAL: return "REAL" ; break;
        case BOOLEAN: return "BOOLEAN" ; break;
        case OF: return "OF" ; break;
        case ARRAY: return "ARRAY" ; break;
        case START: return "START" ; break;
        case END: return "END" ; break;
        case DECLARE: return "DECLARE" ; break;
        case MODULE: return "MODULE" ; break;
        case DRIVER: return "DRIVER" ; break;
        case PROGRAM: return "PROGRAM" ; break;
        case GET_VALUE: return "GET_VALUE" ; break;
        case PRINT: return "PRINT" ; break;
        case USE: return "USE" ; break;
        case WITH: return "WITH" ; break;
        case PARAMETERS: return "PARAMETERS" ; break;
        case TRUE: return "TRUE" ; break;
        case FALSE: return "FALSE" ; break;
        case TAKES: return "TAKES" ; break;
        case INPUT: return "INPUT" ; break;
        case RETURNS: return "RETURNS" ; break;
        case AND: return "AND" ; break;
        case OR: return "OR" ; break;
        case FOR: return "FOR" ; break;
        case IN: return "IN" ; break;
        case WHILE: return "WHILE"; break;
        case SWITCH: return "SWITCH" ; break;
        case CASE: return "CASE" ; break;
        case BREAK: return "BREAK" ; break;
        case DEFAULT: return "DEFAULT" ; break;
        default: return "UNRECOGNIZED TOKEN"; break;
    }
}