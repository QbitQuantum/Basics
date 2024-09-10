int OS_Print(BOOL cond, const char* string, ...)
{
	WCHAR message[OS_BUFFER_SIZE];
	WCHAR wstring[OS_BUFFER_SIZE];
	va_list ptr;
	int iRequiredSize = 0;
	
	if (!cond) 
		return 0;

	// Find out required string size (if you don't have that info)
	iRequiredSize = ::MultiByteToWideChar(CP_ACP, NULL, string, -1, NULL, 0);

	if (iRequiredSize > OS_BUFFER_SIZE)
		iRequiredSize = OS_BUFFER_SIZE;

	// Do the string conversion
	::MultiByteToWideChar(CP_ACP, NULL, string , -1, wstring, iRequiredSize);
    
    va_start(ptr,string);
	vswprintf(message, wstring, ptr);
    va_end(ptr);

	RETAILMSG(1, (message));
	return 1;
}