BOOL My_CopyFileA()
{
	LPCSTR lpExistingFileName=NULL;
	LPCSTR lpNewFileName=NULL;
	BOOL bFailIfExists=NULL;
	BOOL returnVal_Real = NULL;
	BOOL returnVal_Intercepted = NULL;

	DWORD error_Real = 0;
	DWORD error_Intercepted = 0;
	disableInterception();
	returnVal_Real = CopyFileA (lpExistingFileName,lpNewFileName,bFailIfExists);
	error_Real = GetLastError();
	enableInterception();
	returnVal_Intercepted = CopyFileA (lpExistingFileName,lpNewFileName,bFailIfExists);
	error_Intercepted = GetLastError();
	return ((returnVal_Real == returnVal_Intercepted) && (error_Real == error_Intercepted));
}