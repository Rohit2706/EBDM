//Group No. 7
//ANIRUDH GOYAL 2017A7PS0031P
//ANISHKUMAR SS 2017A7PS0069P
//ROHIT JAIN 2017A7PS0122P
//ADITYA SAXENA 2017A7PS0166P

// This implements array of linked lsts to store the grammar

#include "parserDef.h"

// Function Definations

// To create a linked list
linkedList* createLinkedList(){
    linkedList* lhsNode=(linkedList* )malloc(sizeof(linkedList));
    return lhsNode;
}

// To add first node
void addLhs(linkedList* inpLinkedList, Symbol inpData, int inpTag){
    node* lhs=(node*)malloc(sizeof(node));
    lhs->data=inpData;
    lhs->tag=inpTag;
    lhs->next=NULL;
    lhs->prev=NULL;
    inpLinkedList->head=lhs;
    inpLinkedList->tail=lhs;
}

// To add nodes at the tail
void addRhs(linkedList* inpLinkedList, Symbol inpData, int inpTag){
    node* rhs=(node*)malloc(sizeof(node));
    rhs->data=inpData;
    rhs->tag=inpTag;
    rhs->next=NULL;
    rhs->prev=inpLinkedList->tail;
    inpLinkedList->tail->next=rhs;
    inpLinkedList->tail=rhs;

}

// To read grammar from the file into the data structure
void readIntoArr(FILE* grammarRules, linkedList* grammar[]){
    
    char line[1000]={'#'};
    char token[50];
    int flag=0;
    int currRow=0;
    int beg=0;
    int end=0;
    
    while(fgets(line,sizeof(line),grammarRules) != NULL){
        beg=0;
        end=0;
        while(line[end]!='\0' || line[end]!='\n'){
            if(line[end]==' ' || line[end]=='\0' || line[end]=='\n'){
                char* insert=(char*)malloc((end-beg+1)*sizeof(char));
                int i;
                for(i=beg;i<end;i++)
                    insert[i-beg]=line[i];
                insert[i-beg] = '\0';    
                tagged_union T = mapping_get_value(ht_symbols,insert);
                if(flag==0){
                    addLhs(grammar[currRow], T.value,T.tag);
                    flag=1;
                }
                else
                    addRhs(grammar[currRow], T.value,T.tag);
                
                end++;
                beg=end;
                
                if(line[end]=='\0' || line[end]=='\n')
                    break;
            }
            else
                end++;
        }
        currRow++;
        flag=0;
    }
}