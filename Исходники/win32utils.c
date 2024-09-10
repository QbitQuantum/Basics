gboolean
isadmin_win32()
{
	BOOL bRet;
	PACL pACL;
	DWORD dwLen, dwStatus;
	PSID psidAdmin;
	HANDLE hTok, hItok;
	PRIVILEGE_SET ps;
	PSECURITY_DESCRIPTOR psdAdmin;

	GENERIC_MAPPING gmap = {ACCESS_READ, ACCESS_WRITE, 0, ACCESS_READ | ACCESS_WRITE};
	SID_IDENTIFIER_AUTHORITY SSidAuth = {SECURITY_NT_AUTHORITY};

	if (!OpenThreadToken(GetCurrentThread(), TOKEN_DUPLICATE | TOKEN_QUERY, TRUE, &hTok)) {
		if (GetLastError() != ERROR_NO_TOKEN)
			return FALSE;
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_DUPLICATE | TOKEN_QUERY, &hTok))
			return FALSE;
	}

	if (!DuplicateToken(hTok, SecurityImpersonation, &hItok))
		return FALSE;

	if (!AllocateAndInitializeSid(&SSidAuth, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &psidAdmin))
		return FALSE;

	if (!(psdAdmin = LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH)))
		return FALSE;

	if (!InitializeSecurityDescriptor(psdAdmin, SECURITY_DESCRIPTOR_REVISION))
		return FALSE;

	dwLen = sizeof(ACL) + sizeof(ACCESS_ALLOWED_ACE) + GetLengthSid(psidAdmin) - sizeof(DWORD);
	if (!(pACL = (PACL)LocalAlloc(LPTR, dwLen)))
		return FALSE;

	if (!InitializeAcl(pACL, dwLen, ACL_REVISION2))
		return FALSE;

	if (!AddAccessAllowedAce(pACL, ACL_REVISION2, ACCESS_READ | ACCESS_WRITE, psidAdmin))
		return FALSE;

	if (!SetSecurityDescriptorDacl(psdAdmin, TRUE, pACL, FALSE))
		return FALSE;

	SetSecurityDescriptorGroup(psdAdmin, psidAdmin, FALSE);
	SetSecurityDescriptorOwner(psdAdmin, psidAdmin, FALSE);

	if (!IsValidSecurityDescriptor(psdAdmin))
		return FALSE;

	dwLen = sizeof(PRIVILEGE_SET);
	if (!AccessCheck(psdAdmin, hItok, ACCESS_READ, &gmap, &ps, &dwLen, &dwStatus, &bRet)) {
		bRet = FALSE;
		g_print("ERROR: %lu\n", GetLastError());
	}

	if (pACL) LocalFree(pACL);
 	if (psdAdmin) LocalFree(psdAdmin);
	if (psidAdmin) FreeSid(psidAdmin);
	if (hItok) CloseHandle(hItok);
	if (hTok) CloseHandle(hTok);

	return (gboolean)bRet;
}