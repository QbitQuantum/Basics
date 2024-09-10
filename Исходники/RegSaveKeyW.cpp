BOOL My_RegSaveKeyW()
{
	HKEY hKey=NULL;
	LPCWSTR lpFile=NULL;
	LPSECURITY_ATTRIBUTES lpSecurityAttributes=NULL;
	LONG returnVal_Real = NULL;
	LONG returnVal_Intercepted = NULL;

	DWORD error_Real = 0;
	DWORD error_Intercepted = 0;
	disableInterception();
	returnVal_Real = RegSaveKeyW (hKey,lpFile,lpSecurityAttributes);
	error_Real = GetLastError();
	enableInterception();
	returnVal_Intercepted = RegSaveKeyW (hKey,lpFile,lpSecurityAttributes);
	error_Intercepted = GetLastError();
	return ((returnVal_Real == returnVal_Intercepted) && (error_Real == error_Intercepted));
}