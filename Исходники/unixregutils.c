DWORD
VmDirRegConfigGetValue(
    PVMDIR_CONFIG_CONNECTION_HANDLE pCfgHandle,
    PCSTR  pszSubKey,
    PCSTR  pszKeyName,
    DWORD  valueType,
    PBYTE  pRetValue,
    PDWORD pRetValueLen
    )
{
    DWORD dwError = 0;

    dwError = RegGetValueA(
#ifndef _WIN32
                pCfgHandle->hConnection,
#endif
                pCfgHandle->hKey,
                pszSubKey,
                pszKeyName,
                valueType,
                NULL,
                (PVOID) pRetValue,
                pRetValueLen);
    BAIL_ON_VMDIR_ERROR_NO_LINE(dwError);

error:
    if (dwError)
    {
        *pRetValueLen = 0;
    }

    return dwError;
}