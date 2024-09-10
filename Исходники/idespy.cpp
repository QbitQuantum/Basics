extern "C" BOOL
APIENTRY DllMain(
    PVOID hModule,
    ULONG ulReason,
    PCONTEXT pctx
    )
{
	char pszBuffer[ 10 ], pszModuleName[ MAX_PATH ];
	BOOL fResult = TRUE;
	// DLL is instantiated.
  if ( ulReason == DLL_PROCESS_ATTACH )
	{
		GetModuleFileName( NULL, pszModuleName, sizeof( pszModuleName ) );
		if( strstr( _strupr( pszModuleName ), ATTACH_PROCESS_NAME ) ) 
		//if we are attaching to Visual C++ process
		{
			hDebug = _lcreat(	"d:\\debug.txt", 0 ); //temporary
			pszStatus[0] = '\0';

			DWORD nThreadID = GetCurrentThreadId();
			EnumThreadWindows( nThreadID, (WNDENUMPROC) EnumCbck, 0 );
			if( ghDeveloperStudioWnd )
			{
				wsprintf( pszBuffer, "%ld", (DWORD) ghDeveloperStudioWnd );
				ghEvent = OpenEvent( EVENT_MODIFY_STATE, TRUE, pszBuffer );
				if( ghEvent )
				{
					wsprintf( pszBuffer, "M%ld", (DWORD) ghDeveloperStudioWnd );
					ghMutex = OpenMutex( MUTEX_ALL_ACCESS, FALSE, pszBuffer );
					if( !ghMutex )
					{
						fResult = FALSE;
						CloseHandle( ghEvent );
					}
				}
				else
					fResult = FALSE;
			}
			else
				fResult = FALSE;
		}
		
  }
	else if ( ulReason == DLL_PROCESS_DETACH )
	{
		// If we got here and ghMutex is not NULL, it means that dll is unloading
		// from a process space of Visual C, and we can close a mutex handle
		if( ghMutex )
			CloseHandle( ghMutex );
	}

    return fResult;
}