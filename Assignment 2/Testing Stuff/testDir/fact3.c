#include<stdio.h>
int main()
{
int num;
do
{
printf("Enter a positive int: ");
scanf("%d", &num);
}
while(num<0);
int factorial = 1;
int i;
for (i = 1; i<=num; i++)
factorial = factorial*i;
printf("%d! = %d\n", num, factorial);
return 0;
}
