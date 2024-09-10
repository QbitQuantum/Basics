/*
 * Process a "/recurse" option.
 */
static void recurseOption(char *arg)
{
	char * dirPrefix = NULL;
	int i=0;
	if((arg==NULL) || (arg[0])=='\0')
	{
		return;
	}

	dirPrefix = ILCalloc(strlen(arg)+1,sizeof(char));

	while(((*arg)!='\0') && ((*arg)!='*'))
	{
		dirPrefix[i++]=*arg;
		arg++;
	}

	if(*dirPrefix == '\0')
	{
		// /recurse:*.cs starts from current dir
		dirPrefix[0]='.';
	}

	recurseAndAddFiles(dirPrefix,arg);

//cleanup:
	if(dirPrefix)
	{
		ILFree(dirPrefix);
	}
}