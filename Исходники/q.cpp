/********************************
	Obtains the SeDebugPrivilege privilege to access other process memory.
	
	return Value
		ERROR_SUCCESS : no error
		ERROR_ACCESS_DENIED : cannot obtain the SeDebugPrivilege privilege
********************************/
DWORD elevate_access_rights()
{
	TOKEN_PRIVILEGES priv;
	HANDLE n1;
	LUID luid;
	if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &n1))
	{
		#ifdef DEBUG
			printf("[!] elevate_access_rights :: OpenProcessToken() failed\n");
		#endif
		return ERROR_ACCESS_DENIED;
	}
	if(!LookupPrivilegeValueA(NULL, "SeDebugPrivilege", &luid))
	{
		#ifdef DEBUG
			printf("[!] elevate_access_rights :: LookupPrivilegeValueA() failed\n");
		#endif
		return ERROR_ACCESS_DENIED;
	}
	priv.PrivilegeCount=1;
	priv.Privileges[0].Luid=luid;
	priv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if(!AdjustTokenPrivileges(n1, FALSE, &priv, sizeof(priv), NULL, NULL))
	{
		#ifdef DEBUG
			printf("[!] elevate_access_rights :: AdjustTokenPrivileges() failed\n");
		#endif
		return ERROR_ACCESS_DENIED;
	}
	
	CloseHandle(n1);
	return ERROR_SUCCESS;
}