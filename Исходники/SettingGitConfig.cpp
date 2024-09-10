BOOL IsAdmin()
{
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	PSID AdministratorsGroup;
	// Initialize SID.
	if (!AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &AdministratorsGroup))
		return false;

	// Check whether the token is present in admin group.
	BOOL IsInAdminGroup = FALSE;
	if (!CheckTokenMembership(NULL, AdministratorsGroup, &IsInAdminGroup))
		IsInAdminGroup = FALSE;

	// Free SID and return.
	FreeSid(AdministratorsGroup);
	return IsInAdminGroup;
}