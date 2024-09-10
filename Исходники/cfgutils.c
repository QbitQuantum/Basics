static
DWORD
VmwDeployDisableAfdListener(
    void
    )
{
    DWORD dwError = 0;
    HANDLE hConnection = NULL;
    HKEY   hRootKey = NULL;
    HKEY   hParamKey = NULL;
    DWORD  dwValue = 0;

    dwError = RegOpenServer(&hConnection);
    BAIL_ON_DEPLOY_ERROR(dwError);

    dwError = RegOpenKeyExA(
                    hConnection,
                    NULL,
                    "HKEY_THIS_MACHINE",
                    0,
                    KEY_READ,
                    &hRootKey);
    BAIL_ON_DEPLOY_ERROR(dwError);

    dwError = RegOpenKeyExA(
                    hConnection,
                    hRootKey,
                    "Services\\vmafd\\Parameters",
                    0,
                    KEY_SET_VALUE,
                    &hParamKey);
    BAIL_ON_DEPLOY_ERROR(dwError);

    dwError = RegSetValueExA(
                    hConnection,
                    hParamKey,
                    "EnableDCERPC",
                    0,
                    REG_DWORD,
                    (PBYTE)&dwValue,
                    sizeof(dwValue));
     BAIL_ON_DEPLOY_ERROR(dwError);

cleanup:

    if (hConnection)
    {
        if (hParamKey)
        {
            RegCloseKey(hConnection, hParamKey);
        }
        if (hRootKey)
        {
            RegCloseKey(hConnection, hRootKey);
        }

        RegCloseServer(hConnection);
    }

    return dwError;

error:

    goto cleanup;
}