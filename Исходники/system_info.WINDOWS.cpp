BOOL SystemHandleInformation::GetFileName( HANDLE h, MyString& str, DWORD processId )
{
	BOOL ret= FALSE;
	HANDLE hThread = NULL;
	GetFileNameThreadParam tp;
	HANDLE handle;
	HANDLE hRemoteProcess = NULL;
	BOOL remote = processId != GetCurrentProcessId();
	
	if ( !NtDllStatus )
		return FALSE;

	if ( remote )
	{
		// Open process
		hRemoteProcess = OpenProcess( processId );
		
		if ( hRemoteProcess == NULL )
			return FALSE;

		// Duplicate handle
		handle = DuplicateHandle( hRemoteProcess, h );
	}
	else
		handle = h;

	tp.hFile = handle;
	tp.pName = &str;
	tp.rc = 0;

	// tj:2012 is it really necessary to create a thread to call NtQueryInformationFile??"
	// Let's start the thread to get the file name
	hThread = (HANDLE)_beginthread( GetFileNameThread, 0, &tp );

	if ( hThread == NULL )
	{
		ret = FALSE;
		goto cleanup;
	}

	// Wait for finishing the thread
	if ( WaitForSingleObject( hThread, 100 ) == WAIT_TIMEOUT )
	{	
		// Access denied
		// Terminate the thread
		#pragma warning(suppress: 6258) // Using TerminateThread does not allow proper thread clean up
		TerminateThread( hThread, 0 );

		str = "";

		ret = TRUE;
	}
	else
		ret = ( tp.rc == 0 );

cleanup:

	if ( remote )
	{
		if ( hRemoteProcess != NULL )
			CloseHandle( hRemoteProcess );

		if ( handle != NULL )
			CloseHandle( handle );
	}
		
	return ret;
}