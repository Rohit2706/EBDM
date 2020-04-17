
#include "ast.h"

listNode* getList(tree_node* root, SYMBOL_TABLE* enterST){
  
  if((root->child[0]->val).value.t_val==EPSILON)
    return NULL;

  listNode* prev=NULL, *curr,*head;
  STValue* insertVal;

  for(int j=0;j<root->no_child ; j=j+2){

    curr = (listNode*)malloc(sizeof(listNode));
    strncpy(curr->lexeme, root->child[j]->lexeme,25);
    (curr->type).dtype = (root->child[j+1]->val).value.t_val;

    insertVal = get_stvalue(enterST, curr->lexeme);

    if(insertVal != NULL){ 
      if(error_flag)
        printf("Line %d: semantic error - multiple declarations for variable '%s' in function parameters\n", root->child[j]->line_no, root->child[j]->lexeme);
      continue;
    }
  
    insertVal = (STValue*) malloc(sizeof(STValue));
    STValue* lookup;
    if((curr->type).dtype == ARRAY){
      (curr->type).isArray=1;
      (curr->type).dtype = (root->child[j+1]->child[1]->val).value.t_val;

      if((root->child[j+1]->child[0]->child[0]->val).value.t_val == ID){
        (curr->type).isStatic = 0;
        (curr->type).begin = -1;
        (curr->type).begins = root->child[j+1]->child[0]->child[0]->lexeme;
        lookup = returnIfPresentST(root->child[j+1]->child[0]->child[0]->lexeme, enterST, root->child[j+1]->child[0]->child[0]);
        if(lookup == NULL);
        else if((lookup->type).dtype != INTEGER){
          if(error_flag)
            printf("Line %d: semantic error - invalid type for array range\n", root->child[j+1]->child[0]->child[0]->line_no);
        }
      }
      else{
        (curr->type).isStatic = 1;
        (curr->type).begin = (root->child[j+1]->child[0]->child[0]->value).num_value;
      }

      if((root->child[j+1]->child[0]->child[1]->val).value.t_val == ID){
        (curr->type).isStatic = 0;
        (curr->type).end = -1;
        (curr->type).ends = root->child[j+1]->child[0]->child[1]->lexeme;
        lookup = returnIfPresentST(root->child[j+1]->child[0]->child[1]->lexeme, enterST, root->child[j+1]->child[0]->child[1]);
        if(lookup == NULL);
        else if((lookup->type).dtype != INTEGER){
          if(error_flag)
          printf("Line %d: semantic error - invalid type for array range\n", root->child[j+1]->child[0]->child[1]->line_no);
        }
      }
      else{
        (curr->type).end = (root->child[j+1]->child[0]->child[1]->value).num_value;
      }

      if((curr->type).isStatic && (curr->type).begin>=(curr->type).end){
          if(error_flag)
          printf("Line %d: semantic error - invalid range for array declaration\n", root->child[j+1]->child[0]->child[0]->line_no);
      }
    }
    else{
      (curr->type).isArray=0;
      (curr->type).isStatic=1;
      (curr->type).begin=-1;
      (curr->type).end=-1;
    }

    int temp_width = get_width(curr->type);
    if((curr->type).isArray)
      temp_width = 12;
    insertVal->type = curr->type;
    insertVal->scope[0] = root->child[j]->line_no;
    insertVal->scope[1] = enterST->endscope;
    insertVal->offset = enterST->curr_offset;
    insertVal->width = temp_width;
    enterST->curr_offset += temp_width;

    insert_stentry(enterST, curr->lexeme, insertVal);

    curr->next= NULL;

    if(prev!=NULL)
      prev->next = curr;
    else
      head=curr;
    
    prev=curr;
  }

  return head;
}

int get_width(TYPE_STRUCT temp){
  int width;

  switch(temp.dtype){
    case INTEGER: width = 2; break;
    case REAL:  width = 4; break;
    case BOOLEAN: width = 1; break;
    default: width = 0; break;
  }
  if(temp.isArray){
    if(temp.isStatic)
      width *= (temp.end - temp.begin + 1);
    else
      width = 0;
    width+=8;
  }

  return width;
}

int outOfRange(int search, int lower, int upper){
    if(search>=lower && search<=upper)
      return 0;
    return -1;    
}

STValue* returnIfPresentST(char* inputKey, SYMBOL_TABLE* stInput, tree_node* inputNode){

  STValue* find = NULL;
  SYMBOL_TABLE* st = stInput;
  while(st->parent!=NULL){
      find = get_stvalue(st, inputKey);
      if(find==NULL || outOfRange(inputNode->line_no, find->scope[0], find->scope[1])){
          st = st->parent;
      }
      else
        return find;
  }

  find = get_stvalue(st, inputKey);
  if(find==NULL || outOfRange(inputNode->line_no, find->scope[0], find->scope[1]));
  else
    return find;

  FTValue* search = get_ftvalue(ft, st->name);
  if(search!=NULL){
    st = search -> inputSymbolTable;
    if(st!=NULL){
      find = get_stvalue(st, inputKey);
      if(find==NULL || outOfRange(inputNode->line_no, find->scope[0], find->scope[1]));
      else
        return find;
    }
  }
  if(error_flag)
  printf("Line %d: semantic error - undefined reference to variable '%s'\n", inputNode->line_no, inputKey);

  return NULL;
}

void populateST(tree_node* root, SYMBOL_TABLE* curr_st){

  FTValue* newentry, *calledfunc;
  TYPE_STRUCT temp;
  STValue* newstentry;
  STValue* lookup;
  tree_node* idList;
  tree_node* temp_expr;
  SYMBOL_TABLE* tempCheck;

  if((root->val).tag==1){
    SYMBOL_TABLE* newST;
    switch((root->val).value.t_val){
      case SWITCH:
        newST = st_create(20 , "switch", curr_st);
        newST -> endscope = root->scope[1]; 
        newST -> curr_offset = curr_st -> curr_offset;
        root -> stptr = newST;
        addSTchild(curr_st,newST);
        //returnIfPresentST(root->child[0]->lexeme, curr_st, root->child[0]);
        
        populateST(root->child[1], newST);
        populateST(root->child[2], newST);
        curr_st->curr_offset = newST -> curr_offset;
        return; break;

      case FOR:
        newST = st_create(20 , "for", curr_st);
        newST -> endscope = root->scope[1]; 
        newST -> curr_offset = curr_st -> curr_offset;
        root -> stptr = newST;
        addSTchild(curr_st,newST);
        //returnIfPresentST(root->child[0]->lexeme, curr_st, root->child[0]);
        //loopvariable = (char**) malloc(sizeof(char*));
        //loopvariable[0] = (char*) malloc(sizeof(char)*25);
        //strcpy(loopvariable[0],root->child[0]->lexeme);
        populateST(root->child[2], newST);
        curr_st->curr_offset = newST -> curr_offset;
        //free(loopvariable[0]);
        //free(loopvariable);

        return; break;

      case WHILE:
        newST = st_create(20 , "while", curr_st);
        newST -> endscope = root->scope[1]; 
        newST -> curr_offset = curr_st -> curr_offset;
        root -> stptr = newST;
        addSTchild(curr_st,newST);
        //loopvariable = (char**) malloc(sizeof(char*));
        //loopvariable[0] = NULL;
        populateST(root->child[0], newST);
        //loop_flag = 0;
        populateST(root->child[1], newST);
        curr_st->curr_offset = newST -> curr_offset;

        //if(strcmp(loopvariable->lexeme,"$")!=0)
        //  printf("Line %d: semantic error - atleast one variable in the loop condition must be updated inside loop\n", root->scope[0]);
        return; break;
    }
  }

  switch((root->val).value.nt_val){
    
    case PROGRAM_NT: 
      ft = ft_create(20);

      for(int i=0;i<root->no_child;i++)
        populateST(root->child[i],NULL);
      return; break;
                      
    case MODULEDECLARATIONS: 

        if((root->child[0]->val).value.t_val==EPSILON)
          return;
        for(int i=0; i<root->no_child;i++){
          newentry = get_ftvalue(ft, root->child[i]->lexeme);
          if(newentry!=NULL){
            if(error_flag)
            printf("Line %d: semantic error - multiple declarations for module '%s'\n",root->child[i]->line_no,root->child[i]->lexeme);
            continue;
          }
          newentry = (FTValue*) malloc(sizeof(FTValue));
          newentry -> functionState = DECLARED;
          newentry -> flag = 0;
          newentry -> inputList = NULL;
          newentry -> outputList = NULL;
          (newentry -> type).dtype = MODULE;
          (newentry -> type).begin = -1;
          (newentry -> type).end = -1;
          newentry -> localSymbolTable = NULL;

          insert_FTEntry(ft, root->child[i]->lexeme, newentry);

        }
        
        return; break;

    case DRIVERMODULE:

        newentry = (FTValue*) malloc(sizeof(FTValue));

        newentry->functionState = DEFINED;
        newentry->flag = 0;
        newentry -> inputList = NULL;
        newentry -> outputList = NULL;
        (newentry -> type).dtype = MODULE;
        (newentry -> type).begin = root->child[0]->scope[0];
        (newentry -> type).end = root->child[0]->scope[1];
        newentry -> localSymbolTable =  st_create(20 , "driver", curr_st);
        newentry -> localSymbolTable -> endscope = (newentry -> type).end;
        newentry -> inputSymbolTable =  NULL;
        newentry -> outputEnd = 0;
        insert_FTEntry(ft, "driver", newentry);

        root->stptr = newentry -> localSymbolTable;
        populateST(root->child[0]->child[0], newentry->localSymbolTable);

        return; break;

    case MODULE_NT:

        newentry = get_ftvalue(ft, root->child[0]->lexeme);
        if(newentry!=NULL){
          if(newentry->functionState == DEFINED || newentry->functionState == DECANDDEF){
            if(error_flag)
            printf("Line %d: semantic error - multiple definations for module '%s'\n", root->child[0]->line_no,root->child[0]->lexeme);
            root->stptr = NULL;
            return;
          }

          newentry->functionState = DECANDDEF;
          (newentry -> type).begin = root->child[3]->scope[0];
          (newentry -> type).end = root->child[3]->scope[1];
          newentry -> localSymbolTable =  st_create(20 , root->child[0]->lexeme, curr_st);
          newentry -> localSymbolTable -> endscope = (newentry -> type).end;
          newentry -> inputSymbolTable =  st_create(20 , "inputList", NULL);
          newentry -> inputSymbolTable -> endscope = (newentry -> type).end;

          root->stptr = newentry -> localSymbolTable;

          newentry -> inputList = getList(root->child[1], newentry -> inputSymbolTable);
          newentry -> outputList = getList(root->child[2], newentry -> localSymbolTable);
          newentry -> outputEnd = newentry->localSymbolTable->curr_offset;
          populateST(root->child[3]->child[0], newentry->localSymbolTable);
        }
        else{
          newentry = (FTValue*) malloc(sizeof(FTValue));
          newentry->functionState = DEFINED;
          newentry->flag = 0;
          (newentry -> type).dtype = MODULE;
          (newentry -> type).begin = root->child[3]->scope[0];
          (newentry -> type).end = root->child[3]->scope[1];
          newentry -> localSymbolTable =  st_create(20 , root->child[0]->lexeme, curr_st);
          newentry -> localSymbolTable -> endscope = (newentry -> type).end;
          newentry -> inputSymbolTable =  st_create(20 , "inputList", NULL);
          newentry -> inputSymbolTable -> endscope = (newentry -> type).end;

          root->stptr = newentry -> localSymbolTable;

          newentry -> inputList = getList(root->child[1], newentry -> inputSymbolTable);
          newentry -> outputList = getList(root->child[2], newentry -> localSymbolTable);
          newentry -> outputEnd = newentry->localSymbolTable->curr_offset;
          insert_FTEntry(ft, root->child[0]->lexeme, newentry);

          populateST(root->child[3]->child[0], newentry->localSymbolTable);
        }

        return; break;

    case IOSTMT:

        switch((root->child[1]->val).value.t_val){
          case NUM:
          case RNUM:
          case TRUE:
          case FALSE:   return; break;

          case ARRAY:
                    returnIfPresentST(root->child[1]->child[0]->lexeme, curr_st, root->child[1]->child[0]); 
                    if((root->child[1]->child[1]->val).value.t_val == ID)
                      returnIfPresentST(root->child[1]->child[1]->lexeme, curr_st, root->child[1]->child[1]); 
                    return;  break;

          case ID: returnIfPresentST(root->child[1]->lexeme, curr_st, root->child[1]);
                   return; break;
          }

          return; break;

    case ASSIGNMENTSTMT: 
        return;  break;

    case DECLARESTMT:

      temp.dtype = (root->child[1]->val).value.t_val;
      if(temp.dtype == ARRAY){
        temp.isArray=1;
        temp.dtype = (root->child[1]->child[1]->val).value.t_val;
        if((root->child[1]->child[0]->child[0]->val).value.t_val == ID){
          temp.isStatic = 0;
          temp.begin = -1;
          temp.begins = root->child[1]->child[0]->child[0]->lexeme;
          lookup = returnIfPresentST(root->child[1]->child[0]->child[0]->lexeme, curr_st, root->child[1]->child[0]->child[0]);
          if(lookup == NULL);
          else if((lookup->type).dtype != INTEGER){
            if(error_flag)
            printf("Line %d: semantic error - invalid type for array range\n", root->child[1]->child[0]->child[0]->line_no);
          }
        }
        else{
          temp.isStatic = 1;
          temp.begin = (root->child[1]->child[0]->child[0]->value).num_value;
        }

        if((root->child[1]->child[0]->child[1]->val).value.t_val == ID){
          temp.isStatic = 0;
          temp.end = -1;
          temp.ends = root->child[1]->child[0]->child[1]->lexeme;
          lookup = returnIfPresentST(root->child[1]->child[0]->child[1]->lexeme, curr_st, root->child[1]->child[0]->child[1]);
          if(lookup == NULL);
          else if((lookup->type).dtype != INTEGER){
            if(error_flag)
            printf("Line %d: semantic error - invalid type for array range\n", root->child[1]->child[0]->child[1]->line_no);
          }
        }
        else{
          temp.end = (root->child[1]->child[0]->child[1]->value).num_value;
        }

        if(temp.isStatic && temp.begin>=temp.end){
            if(error_flag)
            printf("Line %d: semantic error - invalid range for array declaration\n", root->child[1]->child[0]->child[0]->line_no);
        }
      }
      else{
        temp.isArray=0;
        temp.isStatic=1;
        temp.begin=-1;
        temp.end=-1;
      }

      int temp_width = get_width(temp);

      idList = root->child[0];
      for(int i=0; i<idList->no_child;i++){

        newstentry = get_stvalue(curr_st, idList->child[i]->lexeme);

        if(newstentry!=NULL){
            if(error_flag)
            printf("Line %d: semantic error - multiple declarations for variable '%s' in same scope\n", idList->child[i]->line_no,idList->child[i]->lexeme);
            continue;
        }

        //if(strcmp(curr_st->name,"for")==0 && strcmp(idList->child[i]->lexeme,loopvariable->lexeme)==0){
        //  printf("Line %d: semantic error - loop variable in 'for' cannot be redeclared inside the loop\n", idList->child[i]->line_no);
        //  return;
        //}
        newstentry = (STValue*)malloc(sizeof(STValue));
        newstentry->type = temp;
        newstentry->scope[0] = idList->child[i]->line_no;
        newstentry->scope[1] = curr_st->endscope;
        newstentry->offset = curr_st->curr_offset;
        newstentry->width = temp_width;
        curr_st->curr_offset += temp_width;
        insert_stentry(curr_st, idList->child[i]->lexeme, newstentry);
      }
      
      return; break;

    case MODULEREUSESTMT:

      if(strcmp(root->child[1]->lexeme, curr_st->name)==0){
        if(error_flag)
        printf("Line %d: semantic error - ERPLAG language does not support recursion\n", root->child[1]->line_no);
        return;
      }

      calledfunc = get_ftvalue(ft, root->child[1]->lexeme);
      if(calledfunc == NULL){
        if(error_flag)
        printf("Line %d: semantic error - undefined reference to module '%s'\n", root->child[1]->line_no, root->child[1]->lexeme);
        return;
      }

      if(calledfunc->flag==0 && calledfunc->functionState == DECANDDEF){
        if(error_flag)
        printf("Line %d: semantic error - redundant declaration and defination for module '%s' before use in '%s' module\n", root->child[1]->line_no, root->child[1]->lexeme, curr_st->name);
      }
      
      calledfunc->flag = 1;

      return; break;

    case CASESTMT:
        for(int i=1;i<root->no_child;i+=2)
          populateST(root->child[i],curr_st);
        return; break;

    case ARMORBOOL:

    case EXPRESSION:
        /*temp_expr = root->child[0];

        while(temp_expr->no_leftchild==1){
          if((temp_expr->childLeft[0]->val).value.t_val == ID)
            returnIfPresentST(temp_expr->childLeft[0]->lexeme, curr_st, temp_expr->childLeft[0]);
          else if((temp_expr->childLeft[0]->val).value.t_val == ARRAY)
            returnIfPresentST(temp_expr->childLeft[0]->child[0]->lexeme, curr_st, temp_expr->childLeft[0]->child[0]);
          
          temp_expr=temp_expr->child[0];
        }
    
        
        if((temp_expr->val).value.t_val == ID)
        returnIfPresentST(temp_expr->lexeme, curr_st, temp_expr);
        else if((temp_expr->val).value.t_val == ARRAY)
        returnIfPresentST(temp_expr->child[0]->lexeme, curr_st, temp_expr->child[0]);*/

        return; break;


    default:
        if((root->child[0]->val).value.t_val==EPSILON)
          return;

        for(int i=0;i<root->no_child;i++)
          populateST(root->child[i], curr_st);

        return; break;

  }
}