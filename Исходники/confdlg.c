/***********************************************************************
 * drvGetDefaultCommConfigW (SERIALUI.@)
 *
 * Used by Win9x KERNEL to get the default config for a COMM port
 * FIXME: uses the wrong registry key... should use a digit, not
 *        the comm port name.
 */
DWORD WINAPI drvGetDefaultCommConfigW(
	LPCWSTR lpszDevice, LPCOMMCONFIG lpCommConfig, LPDWORD lpdwSize)
{
    HKEY hKeyReg, hKeyPort;
    WCHAR szKeyName[100];
    DWORD r,dwSize,dwType;
    static const WCHAR fmt[] = {'%','s','\\','%','s',0 };

    TRACE("(%s, %p, %p) *lpdwSize: %u\n", debugstr_w(lpszDevice), lpCommConfig, lpdwSize, lpdwSize ? *lpdwSize : 0);

    if ((!lpszDevice) || (!lpCommConfig) || (!lpdwSize)) {
        return ERROR_INVALID_PARAMETER;
    }

    if (*lpdwSize < sizeof (COMMCONFIG)) {
        *lpdwSize = sizeof (COMMCONFIG);
        return ERROR_INSUFFICIENT_BUFFER;
    }

    /* only "com1" - "com9" is allowed */
    r = sizeof(comW) / sizeof(WCHAR);       /* len of "com\0" */
    lstrcpynW(szKeyName, lpszDevice, r);    /* simulate a lstrcmpnW */
    r--;

    if( lstrcmpiW(szKeyName, comW) ||
        (lpszDevice[r] < '1') || (lpszDevice[r] > '9') || lpszDevice[r+1]) {
        return ERROR_BADKEY;
    }

    *lpdwSize = sizeof (COMMCONFIG);
    memset(lpCommConfig, 0 , sizeof (COMMCONFIG));
    lpCommConfig->dwSize = sizeof (COMMCONFIG);
    lpCommConfig->wVersion = 1;
    lpCommConfig->dwProviderSubType = PST_RS232;

    r = RegConnectRegistryW(NULL, HKEY_LOCAL_MACHINE, &hKeyReg);
    if(r != ERROR_SUCCESS) return r;

    snprintfW(szKeyName, sizeof(szKeyName)/sizeof(WCHAR), fmt, lpszCommKey ,lpszDevice);
    r = RegOpenKeyW(hKeyReg, szKeyName, &hKeyPort);
    if(r == ERROR_SUCCESS)
    {
        dwSize = sizeof (DCB);
        dwType = 0;
        r = RegQueryValueExW( hKeyPort, lpszDCB, NULL,
                             &dwType, (LPBYTE)&lpCommConfig->dcb, &dwSize);

        RegCloseKey(hKeyPort);
        if ((r!=ERROR_SUCCESS) || (dwType != REG_BINARY) || (dwSize != sizeof(DCB))) {
            RegCloseKey(hKeyReg);
            return ERROR_INVALID_PARAMETER;
        }

    }
    else
    {
        /* FIXME: default to a hardcoded commconfig */
        lpCommConfig->dcb.DCBlength = sizeof(DCB);
        lpCommConfig->dcb.BaudRate = 9600;
        lpCommConfig->dcb.fBinary = TRUE;
        lpCommConfig->dcb.fParity = FALSE;
        lpCommConfig->dcb.ByteSize = 8;
        lpCommConfig->dcb.Parity = NOPARITY;
        lpCommConfig->dcb.StopBits = ONESTOPBIT;
        return ERROR_SUCCESS;
    }

    RegCloseKey(hKeyReg);

    return r;
}