int main()
{
	char p1[10]="12345abcd";
	char q1[10]="12345efgh";
	char p2[11]="12345\0abcd";
	char q2[11]="12345\0efgh";
	printf("%d\n",Strncmp(p1,q1,5));
	printf("%d\n",Strncmp(p1,q1,9));
	printf("%d\n",Strncmp(q1,p1,9));
	printf("%d\n",Strncmp(p2,q2,9));
	
	return 0;
}