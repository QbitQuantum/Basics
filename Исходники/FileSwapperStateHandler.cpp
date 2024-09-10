bool IsWriteableByCurrentUser(const LPWSTR path)
{
	bool isWriteable = false;
	DWORD result;
	SECURITY_INFORMATION secInfo = OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION;
	PSECURITY_DESCRIPTOR secDesc;
	PSID owner;
	result = GetNamedSecurityInfo(path, SE_FILE_OBJECT, secInfo,
		&owner, NULL, NULL, NULL, &secDesc);
	if (result == ERROR_SUCCESS)
	{
		HANDLE hToken;
		DWORD dwAccessDesired = GENERIC_WRITE;
		PRIVILEGE_SET PrivilegeSet;
		DWORD dwPrivSetSize = sizeof(PRIVILEGE_SET);
		DWORD dwAccessAllowed;
		BOOL fAccessGranted = FALSE;

		GENERIC_MAPPING mapping = { 0xFFFFFFFF };
		mapping.GenericRead = FILE_GENERIC_READ;
		mapping.GenericWrite = FILE_GENERIC_WRITE;
		mapping.GenericExecute = FILE_GENERIC_EXECUTE;
		mapping.GenericAll = FILE_ALL_ACCESS;

		::MapGenericMask(&dwAccessDesired, &mapping);

		if (::OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken))
		{
			HANDLE hImpersonatedToken = NULL;
			if (::DuplicateToken(hToken, SecurityImpersonation, &hImpersonatedToken)) {
				if (AccessCheck(secDesc, hImpersonatedToken, dwAccessDesired, &mapping,
					&PrivilegeSet, &dwPrivSetSize, &dwAccessAllowed, &fAccessGranted))
				{
					isWriteable = (dwAccessAllowed & FILE_GENERIC_WRITE) != 0;
				}
				::CloseHandle(hImpersonatedToken);
			}
			::CloseHandle(hToken);
		}
		::LocalFree(secDesc);
	}

	return isWriteable;
}