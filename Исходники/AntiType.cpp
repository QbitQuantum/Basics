BOOL IsUserAdmin(VOID) 
{
	BOOL						b;
	PSID						AdministratorsGroup; 
	SID_IDENTIFIER_AUTHORITY	NtAuthority = SECURITY_NT_AUTHORITY;
	HMODULE						hModule;
	PCheckTokenMembership		func;
	
	b = AllocateAndInitializeSid(&NtAuthority,
									2,
									SECURITY_BUILTIN_DOMAIN_RID,
									DOMAIN_ALIAS_RID_ADMINS,
									0, 0, 0, 0, 0, 0,
									&AdministratorsGroup); 
	if(b)
	{
		b = FALSE;
		hModule = GetModuleHandle("advapi32.dll");
		func = (PCheckTokenMembership)GetProcAddress(hModule,"CheckTokenMembership");
		if( func != NULL) 
	    {
			func( NULL, AdministratorsGroup, &b);		     
		} 
		FreeSid(AdministratorsGroup); 
	}else
	{
		if( GetLastError() == ERROR_CALL_NOT_IMPLEMENTED )
		{
			//win9x
			b = TRUE;
		}
	}

	return(b);
}