int wmain()
{
    WCHAR desc[255];
    int (FAR STDAPICALLTYPE * GetUName)(WORD wCharCode, LPWSTR lpbuf);
    HINSTANCE hGetUName = LoadLibraryW(L"getuname.dll");
    //getUName GetUName;
    if (hGetUName != NULL)
    {
        (FARPROC&)GetUName = /*(getUName)*/GetProcAddress(hGetUName,"GetUName");
        if (GetUName == NULL)
        {
            FreeLibrary(hGetUName);
            return 1;
        }
    }
    wprintf(L"Please type a character:");
    WCHAR ch = getwchar();
    int res = GetUName(ch,desc);
    if (desc == NULL)
    {
        wprintf(L"Error %d",res);
        return 1;
    }
    wprintf(L"U+%04X: %s",ch,desc);
    wprintf(L"Press return to exit.");
    getwchar();
    return 0;
}