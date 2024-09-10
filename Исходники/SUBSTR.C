void main()
{
	char str[20],sub_str[20],rep[20];
	int len,sub_len,i,pos;
	clrscr();
	printf("\n\tEnter the string  :  ");
	scanf("%[^\n]",str);
	printf("\n\tEnter the starting position of the substring	: ");
	scanf("%d",&pos);
	printf("\n\tEnter the length of the string	:  ");
	scanf("%d",&sub_len);
	str_sub(str,sub_str,pos,sub_len);
	printf("\n\tSub String is	:  ");
		printf("%s",sub_str);
	printf("\n\tEnter the string to be replaced : ");
	flushall();
	scanf("%[^\n]",rep);
	replace(str,rep,pos,sub_len);
	printf("\n\nAfter replacing string : %s",str);
	getch();
}