BOOL HwDetourDetach( DWORD dwLineAddress, DWORD dwType )
{
	HANDLE hThreadSnap;
	THREADENTRY32 te32;

	static BOOL bExceptionHandlerUnSet = FALSE;

	if (bExceptionHandlerUnSet == FALSE)
	{
		RemoveVectoredExceptionHandler(g_hVectorHandle);
		bExceptionHandlerUnSet = !bExceptionHandlerUnSet;
	}

	hThreadSnap =  CreateToolhelp32Snapshot(  TH32CS_SNAPTHREAD, NULL  );
	if( hThreadSnap == INVALID_HANDLE_VALUE ) return  FALSE; 

	te32.dwSize = sizeof(  THREADENTRY32  ); 
	if(  Thread32First(  hThreadSnap, &te32 ) )
	{
		do
		{  
			if(  te32.th32OwnerProcessID != GetCurrentProcessId() || 
				 te32.th32ThreadID == GetCurrentThreadId() )
				continue;

			UninstDbgBreakfromThrd( te32.th32ThreadID,dwLineAddress, dwType);

		} while(  Thread32Next(  hThreadSnap, &te32 ) );
	}

	for(int i = 0; i < 4; i++)
	{
		if( dwLineAddress == g_ExceptionInfo[i].dwLineAddr)
		{
			g_ExceptionInfo[i].bIsFree = TRUE;
			break;
		}
	} 
	return TRUE;
}