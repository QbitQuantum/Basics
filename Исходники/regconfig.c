static
DWORD
VmDirRegConfigGetDword(
    PVMDIR_CONFIG_CONNECTION_HANDLE pCfgHandle,
    PCSTR  pszSubKey,
    PCSTR  pszKeyName,
    PDWORD pdwValue
    )
{
    DWORD dwError =0;
    DWORD dwValue = 0;
    DWORD dwValueSize = sizeof(dwValue);

    dwError = RegGetValueA(
#ifndef _WIN32
                pCfgHandle->hConnection,
#endif
                pCfgHandle->hKey,
                pszSubKey,
                pszKeyName,
                RRF_RT_REG_DWORD,
                NULL,
                (PVOID)&dwValue,
                &dwValueSize);
    BAIL_ON_VMDIR_ERROR(dwError);

    *pdwValue = dwValue;

cleanup:

    return dwError;

error:

    *pdwValue = 0;

    goto cleanup;
}