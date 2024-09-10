unsigned long SetPrivilege(
				HANDLE hToken,         
				LPCTSTR lpszPrivilege,
				BOOL bEnablePrivilege
				) 
{
	TOKEN_PRIVILEGES tp;
	LUID luid;

	if ( !LookupPrivilegeValueA( 
		NULL,  
		lpszPrivilege,
		&luid ) )
	{
		printf("LookupPrivilegeValue error: %u\n", GetLastError() ); 
		return 0; 
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	if (bEnablePrivilege)
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[0].Attributes = 0;

	if ( !AdjustTokenPrivileges(
		hToken, 
		0, 
		&tp, 
		sizeof(TOKEN_PRIVILEGES), 
		(PTOKEN_PRIVILEGES) NULL, 
		(PDWORD) NULL) )
	{ 
		printf("AdjustTokenPrivileges error: %u\n", GetLastError() ); 
		return 0; 
	} 

	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
	{
		printf("The token does not have the specified privilege. \n");
		return 0;
	} 

	return 1;
}