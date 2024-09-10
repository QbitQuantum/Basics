BOOL ImpersonateAndCheckAccess(PCtxtHandle phContext, 
							   PSECURITY_DESCRIPTOR psdSD, 
							   PDWORD pdwAccessGranted) {
	HANDLE hToken = NULL;
	
	// AccessCheck() variables
	DWORD           dwAccessDesired = MAXIMUM_ALLOWED;
	PRIVILEGE_SET   PrivilegeSet;
	DWORD           dwPrivSetSize = sizeof(PRIVILEGE_SET);
	BOOL            fAccessGranted = FALSE;
	GENERIC_MAPPING GenericMapping = { vncGenericRead, vncGenericWrite, 
									   vncGenericExecute, vncGenericAll };
	
	// This only does something if we want to use generic access
	// rights, like GENERIC_ALL, in our call to AccessCheck().
	MapGenericMask(&dwAccessDesired, &GenericMapping);
	
	// AccessCheck() requires an impersonation token.
	if ((fn._ImpersonateSecurityContext(phContext) == SEC_E_OK)
		&& OpenThreadToken(GetCurrentThread(), TOKEN_QUERY, TRUE, &hToken)
		&& AccessCheck(psdSD, hToken, dwAccessDesired, &GenericMapping,
		&PrivilegeSet, &dwPrivSetSize, pdwAccessGranted, &fAccessGranted)) {
		// Restrict access to relevant rights only
		fAccessGranted = AreAnyAccessesGranted(*pdwAccessGranted, ViewOnly | Interact);
	}
	
	// End impersonation
	fn._RevertSecurityContext(phContext);
	
	// Close handles
	if (hToken)
		CloseHandle(hToken);
	
	return fAccessGranted;
}