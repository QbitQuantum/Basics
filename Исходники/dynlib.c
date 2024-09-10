void *ILDynLibraryGetSymbol(void *handle, const char *symbol)
{
	void *value = dlsym(handle, (char *)symbol);
	const char *error = dlerror();
	char *newName;
	if(error == 0)
	{
		return value;
	}
	newName = (char *)ILMalloc(strlen(symbol) + 2);
	if(newName)
	{
		/* Try again with '_' prepended to the name in case
		   we are running on a system with a busted "dlsym" */
		newName[0] = '_';
		strcpy(newName + 1, symbol);
		value = dlsym(handle, newName);
		error = dlerror();
		if(error == 0)
		{
			ILFree(newName);
			return value;
		}
		ILFree(newName);
	}
#ifdef IL_DYNLIB_DEBUG
	fprintf(stderr, "%s: %s\n", symbol, error);
#endif
	return 0;
}