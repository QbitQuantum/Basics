HWND GetMainWindow( DWORD dwOwnerPID ) 
{ 
	HWND hWnd = 0; 
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE; 
	THREADENTRY32 te32; 

	// Take a snapshot of all running threads  
	hThreadSnap = CreateToolhelp32Snapshot( TH32CS_SNAPTHREAD, 0 ); 
	if( hThreadSnap == INVALID_HANDLE_VALUE ) 
		return( 0 ); 

	// Fill in the size of the structure before using it. 
	te32.dwSize = sizeof(THREADENTRY32 ); 

	// Retrieve information about the first thread,
	// and exit if unsuccessful
	if( !Thread32First( hThreadSnap, &te32 ) ) 
	{
		CloseHandle( hThreadSnap );     // Must clean up the snapshot object!
		return( 0 );
	}

	// Now walk the thread list of the system,
	// and display information about each thread
	// associated with the specified process
	do 
	{ 
		if( te32.th32OwnerProcessID == dwOwnerPID )
		{

			EnumThreadWindows(te32.th32ThreadID, EnumProc, (LPARAM)&hWnd); 
			if(hWnd) break;

		}
	} while( Thread32Next(hThreadSnap, &te32 ) ); 

	//  Don't forget to clean up the snapshot object.
	CloseHandle( hThreadSnap );
	return( hWnd );
}