BOOL My_GetStartupInfoW()
{
	LPSTARTUPINFOW lpStartupInfo=NULL;
	
	DWORD error_Real = 0;
	DWORD error_Intercepted = 0;
	__try{
	disableInterception();
	GetStartupInfoW (lpStartupInfo);
	error_Real = GetLastError();
	enableInterception();
	GetStartupInfoW (lpStartupInfo);
	error_Intercepted = GetLastError();
	}__except(puts("in filter"), 1){puts("exception caught");}
	return (error_Real == error_Intercepted);
}