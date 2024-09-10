int main()
{
 printf("%d",p);
 int num1, num2, mod;
 printf("\nEnter two integers\n");
 scanf("%d%d",&num1,&num2);
 printf("\nThe result of division is %d\n", DIV(num1,num2));
 mod = MOD(num1,num2);
 printf("\nThe result of modulus is %d\n", mod);
 
}