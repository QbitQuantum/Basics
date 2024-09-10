int dirdcl(void) /* with error recovery */
{
	int type;
	int nflag = 0;

	if (tokentype == '(')  /* ( dcl )*/
	{
		if (dcl() == -1)
			return -1;
		if (tokentype != ')')
		{
			printf("error missing )\n");
			return -1;
		}
	}
	else if (tokentype == NAME)
	{
		/* printf("token type 'name' received\n"); */
		strcpy(name, token);
	}
	else
	{
		printf("error: expected name of (dcl)\n");
		return -1;
	}
	while ((type=gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat(out, " function returning");
		else
		{
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}

	return 0;
}