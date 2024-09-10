//
// Install our DLL in Lightroom's address space
//
bool CLightroom::LoadDll()
{
	bool isSuccess = false;

	// Bail out right away if the DLL is already loaded
	if( getRemoteDllBase() && pRemoteDllBase != 0 )
		return calculateRemoteEntryPoint();

	// Build an absolute path to LrMouseWheel.dll
	size_t cchPath = wcslen( wszPath );
	WCHAR wszFullPath[ MAX_PATH * 2 ];
	wcsncpy_s( wszFullPath, wszPath, cchPath + 1 );
	if( cchPath > 0 )
		wcsncat_s( wszFullPath, L"\\", 1 );
	wcsncat_s( wszFullPath, wszLrMouseWheelDll, _TRUNCATE );

	// Copy the filename into the remote process
	DWORD cbDllFilename = ( wcslen( wszFullPath ) + 1 ) * sizeof( WCHAR );
	LPVOID pRemoteDllFilename = VirtualAllocEx( hProcess, NULL, cbDllFilename, MEM_COMMIT, PAGE_READWRITE );
	if( WriteProcessMemory( hProcess, pRemoteDllFilename, wszFullPath, cbDllFilename, NULL ) )
	{
		// Cause the DLL to be loaded into the remote process
		PTHREAD_START_ROUTINE pEntryPoint = ( PTHREAD_START_ROUTINE )GetProcAddress( GetModuleHandleW( L"kernel32.dll" ), "LoadLibraryW" );
		HANDLE hRemoteThread = CreateRemoteThread( hProcess, NULL, 0, pEntryPoint, pRemoteDllFilename, 0, NULL );
		if( hRemoteThread )
		{
			WaitForSingleObject( hRemoteThread, INFINITE );

			// Find out where the DLL was loaded
			isSuccess = ( GetExitCodeThread( hRemoteThread, &pRemoteDllBase ) != 0 ) && pRemoteDllBase != 0;

			// Clean up
			CloseHandle( hRemoteThread );
		}
	}

	VirtualFreeEx( hProcess, pRemoteDllFilename, 0, MEM_RELEASE );

	return isSuccess && calculateRemoteEntryPoint();
}