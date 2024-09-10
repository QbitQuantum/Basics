BOOL My_RegConnectRegistryW()
{
	LPCWSTR lpMachineName=NULL;
	HKEY hKey=NULL;
	PHKEY phkResult=NULL;
	LONG returnVal_Real = NULL;
	LONG returnVal_Intercepted = NULL;

	DWORD error_Real = 0;
	DWORD error_Intercepted = 0;
	__try{
	disableInterception();
	returnVal_Real = RegConnectRegistryW (lpMachineName,hKey,phkResult);
	error_Real = GetLastError();
	enableInterception();
	returnVal_Intercepted = RegConnectRegistryW (lpMachineName,hKey,phkResult);
	error_Intercepted = GetLastError();
	}__except(puts("in filter"), 1){puts("exception caught");}
	return ((returnVal_Real == returnVal_Intercepted) && (error_Real == error_Intercepted));
}