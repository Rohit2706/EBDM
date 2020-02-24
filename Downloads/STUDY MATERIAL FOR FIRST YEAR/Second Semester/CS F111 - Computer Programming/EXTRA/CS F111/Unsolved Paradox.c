#include<stdio.h>
void swap(int x,int y);
int main()
{
int a=100;
int b=200;
printf("Before a is %d \n",a);
printf("Before b is %d \n",b);
swap(&a,&b);
printf("After a is %d \n",a);
printf("After b is %d \n",b);
return 0;
}