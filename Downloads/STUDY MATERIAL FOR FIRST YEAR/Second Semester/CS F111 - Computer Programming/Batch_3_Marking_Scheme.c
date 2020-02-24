/****************************************************************************************************************
Implement the following three functions:
1) void Fill_Department_Details(department d[], int size)
2) int Count_Faculty(LINK list, char dname[])
3) LINK Insert_Node_In_Order(LINK d_list,department dp)
Please read the comments inside the functions for details regarding their functionality.
The following utility function is given to you that can be used for testing:
void Print_List(LINK list)
Note:
1) You have to upload only the three functions implementations in the appropriate boxes on uploading site.
2) You are not suppose to modify any of the structure and type definitions given in the question.
3) You can assume all user inputs (where ever applicable) are valid and correct.
**************************************************************************************************************** */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef enum {UG=1, PG=2}degree_offer;

typedef struct {
char dept_name[25];
int no_of_faculty;
degree_offer deg;
}department;

struct node;
typedef struct node NODE;
typedef NODE *LINK;
struct node{
department d;
LINK next;
};

void Fill_Department_Details(department d[], int n ) {
/* This function takes the details of departments d[] as user input. The function reads details of n (n>0) number of departments.
Read the details in the following order: department name, number of faculty, and degree offered. */

//Following is the driver used to test this function

/*
void Fill_Department_Details(department d[], int n );
int main() {
department d[2];
int i;
Fill_Department_Details(d,2);
for(i=0;i<2;i++)
printf("(%s %d %d)\n",d[i].dept_name, d[i].no_of_faculty, d[i].deg);

return 0;
}
*/



}

LINK Insert_Node_In_Order(LINK d_list,department dp) {
/* This function inserts details of department dp in the d_list such that
the departments which offer UG degree appear first before all the departments which offer PG degree.
Assume d_list points to the first node of the linked list which contains departments that offer UG followed by departments that offer PG (if the linked list is non empty). The function returns the modified d_list. This function will have partial marking.          MAX MARKS [30M]      */

// Memory allocation for new node: 3M
// Populating newnode fields: 3M
// Empty list condition check and insert new node:4M
// Newnode is inserted as first node for UG degree:8M
// Newnode is inserted as a last node in the list for PG degree: 10M
//Return the modified list: 2M

}

int Count_Faculty(LINK list, char dname[]) {
/* This function finds the total number of faculty members in the  department dname[] and returns it.
If the department dname[] doesn't exist in the list then function returns -1. There may be more than one node in the list corresponding to a dname[].
This function has binary grading (either 0 or 12.5)    MAXMARKS [12.5]        */

// Following is the driver file used to test this function
/*
int main() {
department d[3];
char dname[] = "MATHS";
LINK d_list = NULL;
department dept1,dept2, dept3, dept4;


strcpy(dept1.dept_name,"MATHS");
dept1.no_of_faculty = 10;
dept1.deg = PG;

strcpy(dept2.dept_name,"MATHS");
dept2.no_of_faculty = 20;
dept2.deg = UG;

strcpy(dept3.dept_name,"CIVIL");
dept3.no_of_faculty = 25;
dept3.deg = UG;

strcpy(dept4.dept_name,"MATHS");
dept4.no_of_faculty = 30;
dept4.deg = PG;

d_list = Insert_Node_In_Order(d_list,dept1);
d_list = Insert_Node_In_Order(d_list,dept2);
d_list = Insert_Node_In_Order(d_list,dept3);
d_list = Insert_Node_In_Order(d_list,dept4);

printf("Maths dept: %d\n",Count_Faculty(d_list, dname));
//Output: Maths dept : 60

char dname1[] = "Civil_dept";
printf("Civil dept: %d\n",Count_Faculty(d_list, dname1));
//Output: Civil dept : -1

return 0;
}
*/


}

void Print_List(LINK list) {
LINK t;
t = list;
while(t!= NULL) {
printf("(%s %d %d)-->",t->d.dept_name, t->d.no_of_faculty, t->d.deg);
t = t->next;
}
printf("NULL");
}

int main() {
/* Here you can declare appropriate variables, do initializations and function calls to test your function implementations */



return 0;
}
