// asummes p<len
void String::Insert(char *s,int p)
{
	int la=strlen(s);
	if (Length+la+1>Max) ReAlloc(Length+la+1);
	memmove(Str+p+la,Str+p,Length-p+1);
	strncpy(Str+p,s,la);
	Length+=la;
}