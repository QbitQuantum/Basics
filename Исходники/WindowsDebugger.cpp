BOOL WindowsDebugger::windowsdebugger_token_privilege( 
	char * lpszPrivilegeName, BOOL bFlag )
{
	LUID sLuid;
	TOKEN_PRIVILEGES sTokenPrivileges;
	HANDLE hToken;

	if( OpenProcessToken( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, 
		&hToken ) == FALSE ) {
			WinError::winerror_print_last_error( __FUNCTION__ );
			return FALSE;
	}

	if( LookupPrivilegeValueA( NULL, lpszPrivilegeName, &sLuid ) 
		== FALSE ) {
			dprintflvl( 2, "Privilege lookup error" );
			CloseHandle( hToken );
			return FALSE;
	}

	sTokenPrivileges.PrivilegeCount = 1;
	sTokenPrivileges.Privileges[0].Luid = sLuid;
	sTokenPrivileges.Privileges[0].Attributes = bFlag ? 
		SE_PRIVILEGE_ENABLED : NULL;

	if( AdjustTokenPrivileges( (HANDLE)hToken, FALSE, 
		(PTOKEN_PRIVILEGES)&sTokenPrivileges, 
		(DWORD)sizeof( sTokenPrivileges ), (PTOKEN_PRIVILEGES)NULL, 
		(PDWORD)NULL ) == FALSE ) {
			CloseHandle( hToken );
			WinError::winerror_print_last_error( __FUNCTION__ );
			dprintflvl( 2, "Error adjusting token" );
			return FALSE;
	}

	CloseHandle( hToken );
	return TRUE;
}