/*
 * Create a restricted token and execute the specified process with it.
 *
 * Returns restricted token on success and 0 on failure.
 *
 * On NT4, or any other system not containing the required functions, will
 * NOT execute anything.
 */
HANDLE
CreateRestrictedProcess(char *cmd, PROCESS_INFORMATION *processInfo, const char *progname)
{
	BOOL		b;
	STARTUPINFO si;
	HANDLE		origToken;
	HANDLE		restrictedToken;
	SID_IDENTIFIER_AUTHORITY NtAuthority = {SECURITY_NT_AUTHORITY};
	SID_AND_ATTRIBUTES dropSids[2];
	__CreateRestrictedToken _CreateRestrictedToken = NULL;
	HANDLE		Advapi32Handle;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	Advapi32Handle = LoadLibrary("ADVAPI32.DLL");
	if (Advapi32Handle != NULL)
	{
		_CreateRestrictedToken = (__CreateRestrictedToken) GetProcAddress(Advapi32Handle, "CreateRestrictedToken");
	}

	if (_CreateRestrictedToken == NULL)
	{
		fprintf(stderr, _("%s: WARNING: cannot create restricted tokens on this platform\n"), progname);
		if (Advapi32Handle != NULL)
			FreeLibrary(Advapi32Handle);
		return 0;
	}

	/* Open the current token to use as a base for the restricted one */
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &origToken))
	{
		fprintf(stderr, _("%s: could not open process token: error code %lu\n"), progname, GetLastError());
		return 0;
	}

	/* Allocate list of SIDs to remove */
	ZeroMemory(&dropSids, sizeof(dropSids));
	if (!AllocateAndInitializeSid(&NtAuthority, 2,
		 SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0,
								  0, &dropSids[0].Sid) ||
		!AllocateAndInitializeSid(&NtAuthority, 2,
	SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_POWER_USERS, 0, 0, 0, 0, 0,
								  0, &dropSids[1].Sid))
	{
		fprintf(stderr, _("%s: could not allocate SIDs: error code %lu\n"),
				progname, GetLastError());
		return 0;
	}

	b = _CreateRestrictedToken(origToken,
							   DISABLE_MAX_PRIVILEGE,
							   sizeof(dropSids) / sizeof(dropSids[0]),
							   dropSids,
							   0, NULL,
							   0, NULL,
							   &restrictedToken);

	FreeSid(dropSids[1].Sid);
	FreeSid(dropSids[0].Sid);
	CloseHandle(origToken);
	FreeLibrary(Advapi32Handle);

	if (!b)
	{
		fprintf(stderr, _("%s: could not create restricted token: error code %lu\n"),
				progname, GetLastError());
		return 0;
	}

#ifndef __CYGWIN__
	AddUserToTokenDacl(restrictedToken);
#endif

	if (!CreateProcessAsUser(restrictedToken,
							 NULL,
							 cmd,
							 NULL,
							 NULL,
							 TRUE,
							 CREATE_SUSPENDED,
							 NULL,
							 NULL,
							 &si,
							 processInfo))

	{
		fprintf(stderr, _("%s: could not start process for command \"%s\": error code %lu\n"), progname, cmd, GetLastError());
		return 0;
	}

	ResumeThread(processInfo->hThread);
	return restrictedToken;
}