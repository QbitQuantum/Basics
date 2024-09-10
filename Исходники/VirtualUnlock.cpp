BOOL My_VirtualUnlock()
{
	LPVOID lpAddress=NULL;
	SIZE_T dwSize=NULL;
	BOOL returnVal_Real = NULL;
	BOOL returnVal_Intercepted = NULL;

	DWORD error_Real = 0;
	DWORD error_Intercepted = 0;
	__try{
	disableInterception();
	returnVal_Real = VirtualUnlock (lpAddress,dwSize);
	error_Real = GetLastError();
	enableInterception();
	returnVal_Intercepted = VirtualUnlock (lpAddress,dwSize);
	error_Intercepted = GetLastError();
	}__except(puts("in filter"), 1){puts("exception caught");}
	return ((returnVal_Real == returnVal_Intercepted) && (error_Real == error_Intercepted));
}