BOOL My_FatalExit()
{
	int ExitCode=NULL;
	
	DWORD error_Real = 0;
	DWORD error_Intercepted = 0;
	__try{
	disableInterception();
	FatalExit (ExitCode);
	error_Real = GetLastError();
	enableInterception();
	FatalExit (ExitCode);
	error_Intercepted = GetLastError();
	}__except(puts("in filter"), 1){puts("exception caught");}
	return (error_Real == error_Intercepted);
}