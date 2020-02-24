
/****************************************
 Implement the following three functions
 1) LINK InsertTwoNodesAfterPos(LINK start, university u1, university u2, int pos);
 2) void Sort(university * univ, int size);
 3) float Compute_Avg_Rank(LINK start);

 Please read the comments inside the functions for details regarding their purpose.
 You have to upload only the three function implementations in the appropriate boxes on uploading site.

 The following is a utility function given to you that can be used for testing.
 void print(LINK start);
 Note:
1) You have to upload only the three functions implementations in the appropriate boxes on uploading site.
2) You are not suppose to modify any of the structure and typedefinitions given in the question.
3) You can assume all user inputs (where ever applicable) are valid and correct.
 ****************************************/

#include <stdio.h>
#include <string.h>

struct university;
typedef enum {TIER_I, TIER_II, TIER_III} tier_type;
typedef struct {
	char uname[35];
	int rank;
	tier_type tier;
} university;

struct node;
typedef struct node NODE;
typedef NODE * LINK;
struct node {
	university univ;
	LINK next;
};

/* Function Prototype Declarations */
LINK InsertTwoNodesAfterPos(LINK start, university u1, university u2, int pos);
void Sort(university * univ, int size);
float Compute_Avg_Rank(LINK start);

LINK InsertTwoNodesAfterPos(LINK start, university u1, university u2, int pos)
{
    /*  This function inserts two new nodes in the list whose first node is pointed by start in such a way that AFTER INSERTION the new nodes corresponding to university u1 and u2 are at positions pos+1 and pos+2 respectively.  Finally the function should return the address of the first node of the modified list. However if the nodes cannot be inserted at specified position, it should simply return the unmodified list. You can assume that pos is always a nonnegative integer. [Example: If the list has 5 nodes and pos is 5, the new nodes will be inserted at positions 6 and 7. If the list has 8 items and pos has a value of 10, the two nodes cannot be inserted.]  MAX_MARKS 30      This function will have some partial marking. */

    /* Marking Scheme
    //Allocating Memory for 2 nodes (3M)
     //Assigning members of 2 nodes (3M)
       //Computing Length of list (6M)
       //If pos>length, return as it is (2M)
       // Inserting when pos=0 (6M)
        // Traverse & Insert when pos!=0 (8M)
        // Returning modified list (2M)
        */

}

void Sort(university * univ, int size)
{
    /* This function takes array of type university and size (number of university)  as input arguments.
     The function sorts the array based on the tier_type, in the order: TIER_I, followed by TIER_II and then followed by TIER_III.  MAX_MARKS 12.5 This function has binary grading (either 0 or 12.5M) */

    /* Following is the driver file used to test this function.
    void print_univ(university u[], int size)
{
    for(int i=0; i< size;i++)
    {
        printf("\t %s ", u[i].uname);
    }
    printf("\n");

}
int main()
{

    university u[4];
    strcpy(u[0].uname, "1");
    u[0].rank = 9;
    u[0].tier = TIER_III;

    Sort(u,1);
    print_univ(u,1);

    strcpy(u[1].uname, "2");
    u[1].rank = 4;
    u[1].tier = TIER_I;

    Sort(u,2);
    print_univ(u,2);

    strcpy(u[2].uname, "3");
    u[2].rank = 29;
    u[2].tier = TIER_II;

    Sort(u,3);
    print_univ(u,3);

    strcpy(u[3].uname, "4");
    u[3].rank = 22;
    u[3].tier = TIER_I;

    Sort(u,4);
    print_univ(u,4);

    //BINARY MARK 0 or 12.5 M
    /*Output should be

     1
     2 1
     2 3 1
     2 4 3 1

     */

    return 0;
*/
}


}


float Compute_Avg_Rank(LINK start)
{
    /* This function takes a pointer to first node of the linked list as an argument.  The function computes and returns the average rank of TIER_I universities. Assume there is at_least one TIER_I university in the linked list.
MAX_MARKS 10  This function has binary grading (0 or 10). */

/* Following is the driver file used to check this function.
int main()
{
        university u1, u2, u3, u4;
        strcpy(u1.uname, "1");
        u1.rank = 9;
        u1.tier = TIER_I;

        strcpy(u2.uname, "2");
        u2.rank = 9;
        u2.tier = TIER_II;

        strcpy(u3.uname, "3");
        u3.rank = 9;
        u3.tier = TIER_III;

        strcpy(u4.uname, "4");
        u4.rank = 10;
        u4.tier = TIER_I;



        LINK n1, n2, n3, n4;
        n1 = (LINK) malloc(sizeof(NODE));
        n1->univ = u1;
        n2 = (LINK) malloc(sizeof(NODE));
        n2->univ = u2;
        n3 = (LINK) malloc(sizeof(NODE));
        n3->univ = u3;
        n4 = (LINK) malloc(sizeof(NODE));
        n4->univ = u4;

        n1->next = n2;
        n2->next = n3;
        n3->next = n4;
        n4->next = NULL;

        float avg = Compute_Avg_Rank(n1);
        printf(" %f ", avg);

        //Binary Marking 0 or 10M

        //Output should be 9.500000

        return 0;

}
*/

}

/* This is just a utility function that you can use for testing */
void print(LINK start)
{
    LINK tmp = start;
    while(tmp!= NULL)
    {
        printf("%s ", tmp->univ.uname);
        tmp=tmp->next;
    }
}

int main(void) {
    /* You can test your implementations from here*/


    return 0;
}
