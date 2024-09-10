int inputAndStore(int input[])
{
	char in[1200];
	gets(in);
	strrev(in);
	//reverse(in);
	//input convertion into int array
	int i,len;
	for(i=0;in[i]!='\0';i++) input[i]=in[i]-'0';
	len=i;
	for(;i<1200;i++) input[i]=0;
	return len;//retuns the number of digits in input
	
}