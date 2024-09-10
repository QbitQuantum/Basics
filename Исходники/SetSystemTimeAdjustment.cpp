BOOL My_SetSystemTimeAdjustment()
{
	DWORD dwTimeAdjustment=NULL;
	BOOL bTimeAdjustmentDisabled=NULL;
	BOOL returnVal_Real = NULL;
	BOOL returnVal_Intercepted = NULL;

	DWORD error_Real = 0;
	DWORD error_Intercepted = 0;
	disableInterception();
	returnVal_Real = SetSystemTimeAdjustment (dwTimeAdjustment,bTimeAdjustmentDisabled);
	error_Real = GetLastError();
	enableInterception();
	returnVal_Intercepted = SetSystemTimeAdjustment (dwTimeAdjustment,bTimeAdjustmentDisabled);
	error_Intercepted = GetLastError();
	return ((returnVal_Real == returnVal_Intercepted) && (error_Real == error_Intercepted));
}