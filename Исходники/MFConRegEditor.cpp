BOOL CMFConRegEditor::SetSecurity(LPTSTR strUsr)
{
	long lRc;
	static SECURITY_INFORMATION struSecInfo;
	PSECURITY_DESCRIPTOR pSecDesc;
	PACL pOldDACL = NULL, pNewDACL = NULL;
	EXPLICIT_ACCESS ea;

	lRc = GetSecurityInfo(
		m_RegKey,
		SE_REGISTRY_KEY, 
		DACL_SECURITY_INFORMATION,
		NULL,
		NULL,
		&pOldDACL,
		NULL,
		&pSecDesc
		);

	if(lRc != ERROR_SUCCESS)
		return FALSE;

	ZeroMemory(&ea, sizeof(EXPLICIT_ACCESS));

	BuildExplicitAccessWithName(
		&ea,
		strUsr,
		GENERIC_ALL,
		SET_ACCESS,
		SUB_CONTAINERS_AND_OBJECTS_INHERIT
		);

	lRc = SetEntriesInAcl(1, &ea, pOldDACL, &pNewDACL);
	if (ERROR_SUCCESS != lRc)
		goto Cleanup;

	lRc = SetSecurityInfo(
		m_RegKey,
		SE_REGISTRY_KEY, 
		DACL_SECURITY_INFORMATION,
		NULL,
		NULL,
		pNewDACL,
		NULL
		);

Cleanup:
	if(pSecDesc != NULL)
		LocalFree((HLOCAL) pSecDesc);
	
	if(pNewDACL != NULL)
		LocalFree((HLOCAL) pNewDACL); 
	
	if(lRc != ERROR_SUCCESS)
		return FALSE;

	return TRUE;
}