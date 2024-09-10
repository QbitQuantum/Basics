USHORT SERVICES_grant_privilege(const TEXT* account, pfnSvcError err_handler, const WCHAR* privilege)
{
/***************************************************
 *
 * S E R V I C E _ g r a n t _ l o g o n _ r i g h t
 *
 ***************************************************
 *
 * Functional description
 *  Grants the "Log on as a service" right to account.
 *  This is a Windows NT, 2000, XP, 2003 security thing.
 *  To run a service under an account other than LocalSystem, the account
 *  must have this right. To succeed granting the right, the current user
 *  must be an Administrator.
 *  Returns FB_SUCCESS when actually granted the right.
 *  Returns FB_LOGON_SRVC_RIGHT_ALREADY_DEFINED if right was already granted
 *  to the user.
 *  Returns FB_FAILURE on any error.
 *
 *  OM - AUG 2003 - Initial implementation
 *  OM - SEP 2003 - Control flow revision, no functional change
 *
 ***************************************************/

	LSA_OBJECT_ATTRIBUTES ObjectAttributes;
	LSA_HANDLE PolicyHandle;

	// Open the policy on the local machine.
	ZeroMemory(&ObjectAttributes, sizeof(ObjectAttributes));
	NTSTATUS lsaErr = LsaOpenPolicy(NULL, &ObjectAttributes,
		POLICY_CREATE_ACCOUNT | POLICY_LOOKUP_NAMES, &PolicyHandle);
	if (lsaErr != (NTSTATUS) 0)
		return (*err_handler)(LsaNtStatusToWinError(lsaErr), "LsaOpenPolicy", NULL);

	// Obtain the SID of the user/group.
	// First, dummy call to LookupAccountName to get the required buffer sizes.
	DWORD cbSid;
	DWORD cchDomain;
	cbSid = cchDomain = 0;
	SID_NAME_USE peUse;
	LookupAccountName(NULL, account, NULL, &cbSid, NULL, &cchDomain, &peUse);
	PSID pSid = (PSID) LocalAlloc(LMEM_ZEROINIT, cbSid);
	if (pSid == 0)
	{
		DWORD err = GetLastError();
		LsaClose(PolicyHandle);
		return (*err_handler)(err, "LocalAlloc(Sid)", NULL);
	}
	TEXT* pDomain = (LPTSTR) LocalAlloc(LMEM_ZEROINIT, cchDomain);
	if (pDomain == 0)
	{
		DWORD err = GetLastError();
		LsaClose(PolicyHandle);
		LocalFree(pSid);
		return (*err_handler)(err, "LocalAlloc(Domain)", NULL);
	}
	// Now, really obtain the SID of the user/group.
	if (LookupAccountName(NULL, account, pSid, &cbSid, pDomain, &cchDomain, &peUse) == 0)
	{
		DWORD err = GetLastError();
		LsaClose(PolicyHandle);
		LocalFree(pSid);
		LocalFree(pDomain);
		return (*err_handler)(err, "LookupAccountName", NULL);
	}

	PLSA_UNICODE_STRING UserRights;
	ULONG CountOfRights = 0;
	NTSTATUS ntStatus = LsaEnumerateAccountRights(PolicyHandle, pSid, &UserRights, &CountOfRights);
	if (ntStatus == (NTSTATUS) 0xC0000034L) //STATUS_OBJECT_NAME_NOT_FOUND
		CountOfRights = 0;
	// Check if the seServiceLogonRight is already granted
	ULONG i;
	for (i = 0; i < CountOfRights; i++)
	{
		if (wcscmp(UserRights[i].Buffer, privilege) == 0)
			break;
	}
	LsaFreeMemory(UserRights); // Don't leak
	LSA_UNICODE_STRING PrivilegeString;
	if (CountOfRights == 0 || i == CountOfRights)
	{
		// Grant the SeServiceLogonRight to users represented by pSid.
		const int string_buff_size = 100;
		WCHAR tempStr[string_buff_size];
		wcsncpy(tempStr, privilege, string_buff_size - 1);
		tempStr[string_buff_size - 1] = 0;

		PrivilegeString.Buffer = tempStr;
		PrivilegeString.Length = wcslen(tempStr) * sizeof(WCHAR);
		PrivilegeString.MaximumLength = sizeof(tempStr);
		if ((lsaErr = LsaAddAccountRights(PolicyHandle, pSid, &PrivilegeString, 1)) != (NTSTATUS) 0)
		{
			LsaClose(PolicyHandle);
			LocalFree(pSid);
			LocalFree(pDomain);
			return (*err_handler)(LsaNtStatusToWinError(lsaErr), "LsaAddAccountRights", NULL);
		}
	}
	else
	{
		LsaClose(PolicyHandle);
		LocalFree(pSid);
		LocalFree(pDomain);
		return FB_PRIVILEGE_ALREADY_GRANTED;
	}

	LsaClose(PolicyHandle);
	LocalFree(pSid);
	LocalFree(pDomain);

	return FB_SUCCESS;
}