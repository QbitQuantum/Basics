__inline DWORD WINAPI OrpcBreakpointFilter(
	LPEXCEPTION_POINTERS lpExcptPtr,
	BOOL *lpAeDebugAttached )									\
{
	BOOL fAeDebugAttached = FALSE;
	DWORD dwRet;
																
	if ( lpExcptPtr->ExceptionRecord->ExceptionCode == EXCEPTION_ORPC_DEBUG )	
	{
		if  ( UnhandledExceptionFilter(lpExcptPtr) == EXCEPTION_CONTINUE_SEARCH )
		{
			// It is important that we don't return EXCEPTION_CONTINUE_SEARCH.
			// This is because there might an handler up the stack which could
			// handle this exception. Just set the flag indicating that a
			// debugger is now attached.
			
			fAeDebugAttached = TRUE;
		}
		dwRet = EXCEPTION_EXECUTE_HANDLER;
	}
	else
	{
		// Not one of our exceptions.
		dwRet = EXCEPTION_CONTINUE_SEARCH;
	}

	if ( lpAeDebugAttached != NULL )
		(*lpAeDebugAttached) = fAeDebugAttached;
	
	return dwRet;	
}