enum ILibFileDir_Type ILibFileDir_GetType(char* directory)
{
#if defined(WIN32) || defined(_WIN32_WCE)
	DWORD _si;
	int dirLen,dirSize;
	#if defined(_WIN32_WCE)
		wchar_t *tempChar;
		int tempCharLength;
	#endif

	dirLen = (int) strlen(directory);
	dirSize = dirLen+1;

#if defined(_WIN32_WCE)
	tempCharLength = MultiByteToWideChar(CP_UTF8,0,directory,-1,NULL,0);
	tempChar = (wchar_t*)malloc(sizeof(wchar_t)*tempCharLength);
	MultiByteToWideChar(CP_UTF8,0,directory,-1,tempChar,tempCharLength);
	_si = GetFileAttributes(tempChar);
#else
	_si = GetFileAttributes(directory);
#endif
	
	if (_si == 0xFFFFFFFF)
	{
		return ILibFileDir_Type_NOT_FOUND_ERROR;
	}

	if ((_si & FILE_ATTRIBUTE_DIRECTORY) == 0)
	{
		return ILibFileDir_Type_FILE;
	}
	else 
	{
		return ILibFileDir_Type_DIRECTORY;
	}
#else
	struct stat _si;

	int dirLen,dirSize;
	char *fullpath;
	int pathExists;
	enum ILibFileDir_Type retVal = ILibFileDir_Type_NOT_FOUND_ERROR;

	dirLen = (int) strlen(directory);
	dirSize = dirLen+1;
	fullpath = (char*) malloc(dirSize);

	pathExists = stat (directory, &_si);

	if (pathExists != -1)
	{
		if ((_si.st_mode & S_IFDIR) == S_IFDIR)
		{
			retVal = ILibFileDir_Type_DIRECTORY;
		}
		else
		{
			retVal = ILibFileDir_Type_FILE;
		}
	}
	return retVal;
#endif
}