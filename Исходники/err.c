void ERR_add_error_data(int num, ...)
	{
	va_list args;
	int i,n,s;
	char *str,*p,*a;

	s=64;
	str=Malloc(s+1);
	if (str == NULL) return;
	str[0]='\0';

	va_start(args, num);
	n=0;
	for (i=0; i<num; i++)
		{
		a=va_arg(args, char*);
		/* ignore NULLs, thanks to Bob Beck <*****@*****.**> */
		if (a != NULL)
			{
			n+=strlen(a);
			if (n > s)
				{
				s=n+20;
				p=Realloc(str,s+1);
				if (p == NULL)
					{
					Free(str);
					return;
					}
				else
					str=p;
				}
			strcat(str,a);
			}
		}
	ERR_set_error_data(str,ERR_TXT_MALLOCED|ERR_TXT_STRING);

	va_end(args);
	}