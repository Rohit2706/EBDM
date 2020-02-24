#include<stdio.h>
int main()
{
char grade;
printf("The grade is as follows \n");
scanf("%c",&grade);
switch(grade)
{
case 'A':
printf("Your grade is A");
break;
case 'B':
printf("Your grade is B");
break;
case 'C':
printf("Your grade is C");
break;
default:
printf("INVALID GRADE");
}
printf("The above is your grade for the previous test");
return 0;
}