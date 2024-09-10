static WINUSERAPI HANDLE WINAPI LoadImageUW(HINSTANCE hInst, LPCSTR lpszName, UINT uType,
        int cxDesired, int cyDesired, UINT fuLoad)
{
    if ((DWORD_PTR)lpszName < 0x10000)
    {
        // lpszName is a resource ID.
        return LoadImageW(hInst, (LPCWSTR)lpszName, uType, cxDesired, cyDesired, fuLoad);
    }

    // lpszName is a string. Convert it from UTF-8 to UTF-16.
    wchar_t *lpszwName = w32u_UTF8toUTF16(lpszName);
    HANDLE hRet = LoadImageW(hInst, lpszwName, uType, cxDesired, cyDesired, fuLoad);
    free(lpszwName);
    return hRet;
}