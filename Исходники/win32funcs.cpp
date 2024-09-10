	bool ShutdownSystem( bool safe )
	{
		HANDLE hToken; 
		TOKEN_PRIVILEGES tkp; 

		if( !OpenProcessToken( GetCurrentProcess(), 
					TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) ) 
		{
			return false;
		}

		LookupPrivilegeValue( NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid ); 

		tkp.PrivilegeCount = 1;  
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 

		AdjustTokenPrivileges( hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0 ); 

		if( GetLastError() != ERROR_SUCCESS ) 
		{
			return false;
		}

		UINT nFlags = safe ? EWX_SHUTDOWN : EWX_SHUTDOWN | EWX_FORCE;

		if( !ExitWindowsEx( nFlags, 0 ) )
		{
			return false;
		}

		return true;
	}