/**
 * @name _HandleConfigureLPTPortCommandOK
 *
 * Writes the value for "TransmissionRetryTimeout" to the registry. Checks for granted SERVER_ACCESS_ADMINISTER access.
 * Actually the opposite of _HandleGetTransmissionRetryTimeout, but name kept for compatibility.
 *
 * @param pXcv
 * Pointer to the LOCALMON_XCV structure of the currently opened Xcv port.
 *
 * @param pInputData
 * Pointer to a Unicode string containing the value to be written to the registry.
 *
 * @param pcbOutputNeeded
 * Pointer to a DWORD that will be zeroed on return.
 *
 * @return
 * An error code indicating success or failure.
 */
static DWORD
_HandleConfigureLPTPortCommandOK(PLOCALMON_XCV pXcv, PBYTE pInputData, PDWORD pcbOutputNeeded)
{
    DWORD cbBuffer;
    DWORD dwErrorCode;
    HKEY hKey = NULL;
    HKEY hToken = NULL;

    // Sanity checks
    if (!pXcv || !pInputData || !pcbOutputNeeded)
    {
        dwErrorCode = ERROR_INVALID_PARAMETER;
        goto Cleanup;
    }

    *pcbOutputNeeded = 0;

    // This action can only happen at SERVER_ACCESS_ADMINISTER access level.
    if (!(pXcv->GrantedAccess & SERVER_ACCESS_ADMINISTER))
    {
        dwErrorCode = ERROR_ACCESS_DENIED;
        goto Cleanup;
    }

    // Switch to the SYSTEM context for modifying the registry.
    hToken = RevertToPrinterSelf();
    if (!hToken)
    {
        dwErrorCode = GetLastError();
        ERR("RevertToPrinterSelf failed with error %lu!\n", dwErrorCode);
        goto Cleanup;
    }

    // Open the key where our value is stored.
    dwErrorCode = (DWORD)RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Windows", 0, KEY_SET_VALUE, &hKey);
    if (dwErrorCode != ERROR_SUCCESS)
    {
        ERR("RegOpenKeyExW failed with status %lu!\n", dwErrorCode);
        goto Cleanup;
    }

    // We don't use cbInputData here, because the buffer pInputData could be bigger than the data it contains.
    cbBuffer = (wcslen((PWSTR)pInputData) + 1) * sizeof(WCHAR);

    // Write the value to the registry.
    dwErrorCode = (DWORD)RegSetValueExW(hKey, L"TransmissionRetryTimeout", 0, REG_SZ, pInputData, cbBuffer);
    if (dwErrorCode != ERROR_SUCCESS)
    {
        ERR("RegSetValueExW failed with status %lu!\n", dwErrorCode);
        goto Cleanup;
    }

Cleanup:
    if (hKey)
        RegCloseKey(hKey);

    if (hToken)
        ImpersonatePrinterClient(hToken);

    return dwErrorCode;
}