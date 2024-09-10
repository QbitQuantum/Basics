char* ModuleTCharToMbDup(const wchar_t* str)
{
	int   len = ModuleMbByteLen(str);
	char* mbstr = (char*) malloc((len + 1) * sizeof(char));
	if (mbstr)
	{
		wcsrtombs(mbstr, &str, len + 1, NULL);	
		return mbstr;
	}
	return NULL;
}