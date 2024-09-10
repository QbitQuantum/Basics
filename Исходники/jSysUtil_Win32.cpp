JBoolean
JUserIsAdmin()
{
	HANDLE tokenHandle;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &tokenHandle))
		{
		return kJFalse;
		}

	DWORD returnLength;
	GetTokenInformation(tokenHandle, TokenGroups, NULL, 0, &returnLength);
	if (returnLength > 65535)
		{
		CloseHandle(tokenHandle);
		return kJFalse;
		}

	TOKEN_GROUPS* groupList = (TOKEN_GROUPS*) malloc(returnLength);
	if (groupList == NULL)
		{
		CloseHandle(tokenHandle);
		return kJFalse;
		}

	if (!GetTokenInformation(tokenHandle, TokenGroups,
							 groupList, returnLength, &returnLength))
		{
		CloseHandle(tokenHandle);
		free(groupList);
		return kJFalse;
		}
	CloseHandle(tokenHandle);

	SID_IDENTIFIER_AUTHORITY siaNtAuth = SECURITY_NT_AUTHORITY;
	PSID adminSid;
	if (!AllocateAndInitializeSid(&siaNtAuth, 2, SECURITY_BUILTIN_DOMAIN_RID,
								  DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0,
								  &adminSid))
		{
		free(groupList);
		return kJFalse;
		}

	JBoolean found = kJFalse;
	for (DWORD i = 0; i < groupList->GroupCount; i++)
		{
		if (EqualSid(adminSid, groupList->Groups[i].Sid))
			{
			found = kJTrue;
			break;
			}
		}

	FreeSid(adminSid);
	free(groupList);

	return found;
}