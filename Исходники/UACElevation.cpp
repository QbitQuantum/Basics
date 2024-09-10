BOOL uac::Am_I_In_Admin_Group(BOOL bCheckAdminMode /*= FALSE*/)
{
	BOOL   fAdmin;
	HANDLE  hThread;
	TOKEN_GROUPS *ptg = NULL;
	DWORD  cbTokenGroups;
	DWORD  dwGroup;
	PSID   psidAdmin;
	SID_IDENTIFIER_AUTHORITY SystemSidAuthority = SECURITY_NT_AUTHORITY;
	if (!OpenThreadToken(GetCurrentThread(), TOKEN_QUERY, FALSE, &hThread))
	{
		if (GetLastError() == ERROR_NO_TOKEN)
		{
			if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY,
				&hThread))
				return (FALSE);
		}
		else
			return (FALSE);
	}
	if (GetTokenInformation(hThread, TokenGroups, NULL, 0, &cbTokenGroups))
		return (FALSE);
	if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		return (FALSE);
	if (!(ptg = (TOKEN_GROUPS*)_alloca(cbTokenGroups)))
		return (FALSE);
	if (!GetTokenInformation(hThread, TokenGroups, ptg, cbTokenGroups,
		&cbTokenGroups))
		return (FALSE);
	if (!AllocateAndInitializeSid(&SystemSidAuthority, 2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0, &psidAdmin))
		return (FALSE);
	fAdmin = FALSE;
	for (dwGroup = 0; dwGroup < ptg->GroupCount; dwGroup++)
	{
		if (EqualSid(ptg->Groups[dwGroup].Sid, psidAdmin))
		{
			if (bCheckAdminMode)
			{
				if ((ptg->Groups[dwGroup].Attributes) & SE_GROUP_ENABLED)
				{
					fAdmin = TRUE;
				}
			}
			else
			{
				fAdmin = TRUE;
			}
			break;
		}
	}
	FreeSid(psidAdmin);
	return (fAdmin);
}