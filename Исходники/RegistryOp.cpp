BOOL RegistryOp::SaveKey(LPWSTR lpFileName)
{
	assert(m_hKey);
	assert(lpFileName);

	long lReturn = RegSaveKeyW(m_hKey, lpFileName, NULL);

	if (lReturn == ERROR_SUCCESS)
		return TRUE;
	DOLOG("RegSaveKeyW ERROR return:" + lReturn);
	return FALSE;
}