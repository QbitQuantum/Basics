BOOL My_GetDriveTypeA()
{
	LPCSTR lpRootPathName=NULL;
	UINT returnVal_Real = NULL;
	UINT returnVal_Intercepted = NULL;

	DWORD error_Real = 0;
	DWORD error_Intercepted = 0;
	__try{
	disableInterception();
	returnVal_Real = GetDriveTypeA (lpRootPathName);
	error_Real = GetLastError();
	enableInterception();
	returnVal_Intercepted = GetDriveTypeA (lpRootPathName);
	error_Intercepted = GetLastError();
	}__except(puts("in filter"), 1){puts("exception caught");}
	return ((returnVal_Real == returnVal_Intercepted) && (error_Real == error_Intercepted));
}