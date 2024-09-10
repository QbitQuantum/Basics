BOOL My_RegGetKeySecurity()
{
	HKEY hKey=NULL;
	SECURITY_INFORMATION SecurityInformation=NULL;
	PSECURITY_DESCRIPTOR pSecurityDescriptor=NULL;
	LPDWORD lpcbSecurityDescriptor=NULL;
	LONG returnVal_Real = NULL;
	LONG returnVal_Intercepted = NULL;

	DWORD error_Real = 0;
	DWORD error_Intercepted = 0;
	__try{
	disableInterception();
	returnVal_Real = RegGetKeySecurity (hKey,SecurityInformation,pSecurityDescriptor,lpcbSecurityDescriptor);
	error_Real = GetLastError();
	enableInterception();
	returnVal_Intercepted = RegGetKeySecurity (hKey,SecurityInformation,pSecurityDescriptor,lpcbSecurityDescriptor);
	error_Intercepted = GetLastError();
	}__except(puts("in filter"), 1){puts("exception caught");}
	return ((returnVal_Real == returnVal_Intercepted) && (error_Real == error_Intercepted));
}