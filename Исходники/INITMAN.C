int readline(char *str,int n,int handle)
{
	int  count=0,succ=0;
	char c;

	while (Fread(handle,1,&c)==1)
	{
		if (c==13)
		{
			succ=1;
			break;
		}
		else
		{
			if (c!=10)
			{
				str[count++]=c;
				if (count>=n) break;
			}
		}
	}

	str[count]=0;

	return((count) || (succ));
}