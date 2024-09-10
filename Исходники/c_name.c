CName CNameCreateUnary(const char *oper, CName arg, int prec)
{
	CName result;
	result.name = (char *)ILMalloc(strlen(oper) + strlen(arg.name) + 4);
	if(!(result.name))
	{
		CCOutOfMemory();
	}
	if(prec > arg.prec)
	{
		strcpy(result.name, oper);
		strcat(result.name, " (");
		strcat(result.name, arg.name);
		strcat(result.name, ")");
	}
	else
	{
		strcpy(result.name, oper);
		strcat(result.name, " ");
		strcat(result.name, arg.name);
	}
	ILFree(arg.name);
	result.prec = prec;
	return result;
}