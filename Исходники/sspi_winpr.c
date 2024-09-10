SECURITY_STATUS SEC_ENTRY winpr_ImportSecurityContextA(SEC_CHAR* pszPackage, PSecBuffer pPackedContext, HANDLE pToken, PCtxtHandle phContext)
{
	char* Name = NULL;
	SECURITY_STATUS status;
	SecurityFunctionTableA* table;

	Name = (char*) sspi_SecureHandleGetUpperPointer(phContext);

	if (!Name)
		return SEC_E_SECPKG_NOT_FOUND;

	table = sspi_GetSecurityFunctionTableAByNameA(Name);

	if (!table)
		return SEC_E_SECPKG_NOT_FOUND;

	if (!table->ImportSecurityContextA)
		return SEC_E_UNSUPPORTED_FUNCTION;

	status = table->ImportSecurityContextA(pszPackage, pPackedContext, pToken, phContext);

	return status;
}