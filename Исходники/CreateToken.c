//
//	Create a primary access token for specified user account
//
HANDLE CreateToken(LPCTSTR szUserName)
{
	SID_IDENTIFIER_AUTHORITY	nt   = SECURITY_NT_AUTHORITY;
	SECURITY_QUALITY_OF_SERVICE	sqos = { sizeof(sqos), SecurityAnonymous, SECURITY_STATIC_TRACKING, FALSE };

	HANDLE				hToken;
	PSID				sid;
	TOKEN_USER			user;

	LUID				authid	= SYSTEM_LUID;
	OBJECT_ATTRIBUTES	oa		= { sizeof(oa), 0, 0, 0, 0, &sqos };
	TOKEN_SOURCE		source	= {{'*', '*', 'A', 'N', 'O', 'N', '*', '*'}, {0, 0}};
	HANDLE				hToken2 = 0;
	PTOKEN_STATISTICS	stats;

	PVOID				tokarr[5];
	int					i;
	DWORD				status;

	// Get address of Nt/ZwCreateToken from NTDLL.DLL
	ZwCreateToken         = (PVOID)GetProcAddress(GetModuleHandle("ntdll.dll"), "ZwCreateToken");
	RtlNtStatusToDosError = (PVOID)GetProcAddress(GetModuleHandle("ntdll.dll"), "RtlNtStatusToDosError");

	if(ZwCreateToken == 0 || RtlNtStatusToDosError == 0)
		return 0;

	// Must have SeCreateToken privilege
	if(!EnablePrivilege(SE_CREATE_TOKEN_NAME, TRUE)){
		DBG("EnablePrivilege failed\n");
	}
	

	// Use an existing process token as our basic for a new token
	if(!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_QUERY_SOURCE, &hToken))
		return 0;
	
	// Convert username to a SID
	if((sid = GetUserSid(szUserName)) == 0)
	{
		CloseHandle(hToken);
		return 0;
	}

	user.User.Attributes	= 0;
	user.User.Sid			= sid;

	if(!AllocateLocallyUniqueId(&source.SourceIdentifier))
	{
		free(sid);
		CloseHandle(hToken);
		return 0;
	}

	if(!GetTokenInfo(hToken, TokenStatistics, &stats))
	{
		free(sid);
		CloseHandle(hToken);
		return 0;
	}
	

	//
	//	Undocumented ZwCreateToken service: will not work for us
	//  under WIN2003, will need to do this from WINLOGON process in future?
	//
	status = ZwCreateToken(&hToken2, TOKEN_ALL_ACCESS, &oa, TokenPrimary,
		(PLUID)&authid, 
		(PLARGE_INTEGER)&stats->ExpirationTime,
		&user,
		(PTOKEN_GROUPS)			GetTokenInfo(hToken, TokenGroups,		&tokarr[0]),
		(PTOKEN_PRIVILEGES)		GetTokenInfo(hToken, TokenPrivileges,	&tokarr[1]),
		(PTOKEN_OWNER)			GetTokenInfo(hToken, TokenOwner,		&tokarr[2]),
		(PTOKEN_PRIMARY_GROUP)	GetTokenInfo(hToken, TokenPrimaryGroup, &tokarr[3]),
		(PTOKEN_DEFAULT_DACL)	GetTokenInfo(hToken, TokenDefaultDacl,	&tokarr[4]),
		&source);

	for(i = 0; i < 5; i++)
		free(tokarr[i]);

	free(stats);
	free(sid);

	CloseHandle(hToken);

	SetLastError(RtlNtStatusToDosError(status));

	return hToken2;
}