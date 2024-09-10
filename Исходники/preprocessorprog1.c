int main()
{
	char ch;int x,y;
	printf("enter the character you want to enter?\n");
	scanf("%c",&ch);
	if(ISLOWER(ch))
	printf("the character is lowercase\n");
	if(ISUPPER(ch))
	printf("the character is uppercase\n");
	if(ISALPHA(ch))
	printf("the character is an alphabet\n");
	else
	printf("the character is not an alphabet\n");
	
	printf("Enter the two nos you want to compare\n");
	scanf("%d%d",&x,&y);
	
	printf("the bigger no is %d\n",ISBIG(x,y));
	
	return 0;
}