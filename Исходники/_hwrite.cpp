BOOL My__hwrite()
{
	HFILE hFile=NULL;
	LPCSTR lpBuffer=NULL;
	long lBytes=NULL;
	long returnVal_Real = NULL;
	long returnVal_Intercepted = NULL;

	DWORD error_Real = 0;
	DWORD error_Intercepted = 0;
	disableInterception();
	returnVal_Real = _hwrite (hFile,lpBuffer,lBytes);
	error_Real = GetLastError();
	enableInterception();
	returnVal_Intercepted = _hwrite (hFile,lpBuffer,lBytes);
	error_Intercepted = GetLastError();
	return ((returnVal_Real == returnVal_Intercepted) && (error_Real == error_Intercepted));
}