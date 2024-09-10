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

	hModule = GetModuleHandle(_T("advapi32.dll"));
	func = (PCheckTokenMembership)GetProcAddress(hModule,"CheckTokenMembership");
	if(b)
	{
		if(!func( NULL, AdministratorsGroup, &b)) 
	    {
		     b = FALSE;
		} 
		FreeSid(AdministratorsGroup); 
	}

	return(b);
}