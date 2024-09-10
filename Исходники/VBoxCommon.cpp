UINT VBoxGetProperty(MSIHANDLE a_hModule, WCHAR *a_pwszName, WCHAR *a_pwszValue, DWORD a_dwSize)
{
    DWORD dwBuffer = 0;
    UINT uiRet = MsiGetPropertyW(a_hModule, a_pwszName, L"", &dwBuffer);
    if (uiRet == ERROR_MORE_DATA)
    {
        ++dwBuffer;     /* On output does not include terminating null, so add 1. */

        if (dwBuffer > a_dwSize)
            return ERROR_MORE_DATA;

        ZeroMemory(a_pwszValue, a_dwSize);
        uiRet = MsiGetPropertyW(a_hModule, a_pwszName, a_pwszValue, &dwBuffer);
    }
    return uiRet;
}