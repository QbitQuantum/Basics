LONG winfrip_confstore_RegSetValueEx(HKEY hKey, LPCSTR lpValueName, DWORD Reserved, DWORD dwType, CONST BYTE *lpData, DWORD cbData)
{
    WINFRIPP_CONFSTORE_DEBUG_ASSERT(hKey);
    WINFRIPP_CONFSTORE_DEBUG_ASSERT(lpValueName);
    WINFRIPP_CONFSTORE_DEBUG_ASSERT(lpData);
    WINFRIPP_CONFSTORE_DEBUG_ASSERT(cbData > 0);

    /*
     * XXX document
     */
    switch (winfrip_confstore_backend_get()) {
    default:
	WINFRIPP_CONFSTORE_DEBUG_FAIL();
	return ERROR_INVALID_FUNCTION;

    case WINFRIP_GENERAL_STORE_BACKEND_REGISTRY:
	return RegSetValueExA(hKey, lpValueName, Reserved, dwType, lpData, cbData);

    case WINFRIP_GENERAL_STORE_BACKEND_EPHEMERAL:
    case WINFRIP_GENERAL_STORE_BACKEND_FILE:
	/* TODO implement */
	return ERROR_INVALID_FUNCTION;
    }
}