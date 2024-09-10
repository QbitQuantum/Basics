LONG SetRegAccess (HKEY hKey, LPCTSTR lpSubKey,
		   PSECURITY_DESCRIPTOR SecDesc, PHKEY phKey)
{
	//
	// Grant requested access
	//
	if (RegSetKeySecurity (*phKey, DACL_SECURITY_INFORMATION, SecDesc) 
					!= ERROR_SUCCESS)
		return FALSE;

	//
	// Re-open the key if requested
	//
	if (! hKey) return TRUE;

	RegCloseKey (*phKey);
	return (RegOpenKey (hKey, lpSubKey, phKey) == ERROR_SUCCESS);
}