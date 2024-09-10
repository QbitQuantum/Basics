static DWORD GetConfigDWORD(LPCWSTR wzName, DWORD dwDefault)
{
    WRAPPER_CONTRACT;
    WCHAR wzValue[16];
    DWORD dwValue;

    if (PAL_FetchConfigurationString(TRUE, wzName, wzValue, sizeof(wzValue) / sizeof(WCHAR)))
    {
        LPWSTR pEnd;
        dwValue = wcstol(wzValue, &pEnd, 16);   // treat it has hex
        if (pEnd != wzValue)                    // success
            return dwValue;
    }

    return dwDefault;
}