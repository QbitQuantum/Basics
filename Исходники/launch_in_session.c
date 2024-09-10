static HANDLE
make_token_from_pid(DWORD winLogonPid)
{
	HANDLE hProcess;
	HANDLE hTokenOrig;
	LUID debugPriv;
	TOKEN_PRIVILEGES tp = {0};
	HANDLE hTokenDup;

	hProcess = OpenProcess(MAXIMUM_ALLOWED, FALSE, winLogonPid);
	if (hProcess == NULL) {
		// failed
		return NULL;
	}

	if (!OpenProcessToken(hProcess,
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY | TOKEN_DUPLICATE |
			TOKEN_ASSIGN_PRIMARY | TOKEN_ADJUST_SESSIONID |
			TOKEN_READ | TOKEN_WRITE,
			&hTokenOrig))
	{
		// failed
		return NULL;
	}

	if (!DuplicateTokenEx(hTokenOrig,
		MAXIMUM_ALLOWED,
		NULL,
		SecurityIdentification, /* impersonation level */
		TokenPrimary,           /* token type */
		&hTokenDup
		))
	{
		// failed
		return FALSE;
	}

	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &debugPriv))
	{
		// failed
		return NULL;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = debugPriv;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	/* adjust token privilege */
	SetTokenInformation(hTokenDup,
		TokenSessionId, (void*) 1, sizeof(DWORD));

	if (!AdjustTokenPrivileges(hTokenDup, FALSE, &tp, sizeof(TOKEN_PRIVILEGES),
		(TOKEN_PRIVILEGES*) NULL,
		NULL))
	{
		// failed
		return NULL;
	}

	CloseHandle(hProcess);
	CloseHandle(hTokenOrig);

	return hTokenDup;
}