void bin( char*string )  
{
	char a[17];
	char str[8];
	char nstr[6];
	int i,j;
	int num;
	int cas;

	if(strlen(string) == 4) cas = 8; //0x00
	if(strlen(string) == 6) cas = 16; //0x0000

	if( string[0] != '0' && string[1] != 'x') return;

	num = strtol(string,NULL,16) ;
	
	i = num;
	memset(a,0,17);

	while (num != 0) 
	{
		memset(str,0,8);
		sprintf (str,"%d",num % 2); 
		num = num /2;
		strcat(a,str);
		
	}
	
	if( i == 0)
	{
		memset(a,'0',cas);
	}
	
	else
	{
		if(strlen(a) < cas)
		{
			for(j = strlen(a); j < cas; j++)
			{
				a[j] = '0';
				//printf("oh yeah ");
			}
		}
	}
	
	printf("%s\n",strrev(a) );
	//printf("%s\n", a);
}