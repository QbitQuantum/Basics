/*	Converts a long number to string. then prints it in the given position using PrintXY function.	*/
VOID NPrintXY(ULONG64 Num,INT x,INT y){
	INT i;
	WCHAR	Text[LONGEST_64BIT_NUM];
	for(i=0;Num>0;++i,Num/=10)
		Text[i] = Num%10 + '0';
	if(i==0)
		Text[i++]='0';
	Text[i]='\0';
	wcsrev(Text);
	PrintXY(Text,x,y);
}