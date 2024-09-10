nsresult
XPCOMGlueLoad(const char *aXpcomFile, GetFrozenFunctionsFunc *func)
{
    wchar_t xpcomFile[MAXPATHLEN];
    MultiByteToWideChar(CP_UTF8, 0, aXpcomFile,-1,
                        xpcomFile, MAXPATHLEN);
   
    
    if (xpcomFile[0] == '.' && xpcomFile[1] == '\0') {
        wcscpy(xpcomFile, LXPCOM_DLL);
    }
    else {
        wchar_t xpcomDir[MAXPATHLEN];
        
        if (ns_isRelPath(xpcomFile))
        {
            _wfullpath(xpcomDir, xpcomFile, sizeof(xpcomDir)/sizeof(wchar_t));
        } 
        else 
        {
            wcscpy(xpcomDir, xpcomFile);
        }
        wchar_t *lastSlash = ns_wcspbrk(xpcomDir, L"/\\");
        if (lastSlash) {
            *lastSlash = '\0';
            char xpcomDir_narrow[MAXPATHLEN];
            WideCharToMultiByte(CP_UTF8, 0, xpcomDir,-1,
                                xpcomDir_narrow, MAX_PATH, NULL, NULL);

            XPCOMGlueLoadDependentLibs(xpcomDir_narrow, ReadDependentCB);
            
            _snwprintf(lastSlash, MAXPATHLEN - wcslen(xpcomDir), L"\\" LXUL_DLL);
            sXULLibrary =
                LoadLibraryExW(xpcomDir, NULL, MOZ_LOADLIBRARY_FLAGS);

            if (!sXULLibrary) 
            {
                DWORD err = GetLastError();
#ifdef DEBUG
                LPVOID lpMsgBuf;
                FormatMessage(
                              FORMAT_MESSAGE_ALLOCATE_BUFFER |
                              FORMAT_MESSAGE_FROM_SYSTEM |
                              FORMAT_MESSAGE_IGNORE_INSERTS,
                              NULL,
                              GetLastError(),
                              MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                              (LPTSTR) &lpMsgBuf,
                              0,
                              NULL
                              );
                wprintf(L"Error loading %s: %s\n", xpcomDir, lpMsgBuf);
                LocalFree(lpMsgBuf);
#endif //DEBUG
                return (err == ERROR_NOT_ENOUGH_MEMORY || err == ERROR_OUTOFMEMORY)
                    ? NS_ERROR_OUT_OF_MEMORY : NS_ERROR_FAILURE;
            }
        }
    }
    HINSTANCE h =
        LoadLibraryExW(xpcomFile, NULL, MOZ_LOADLIBRARY_FLAGS);

    if (!h) 
    {
        DWORD err = GetLastError();
#ifdef DEBUG
        LPVOID lpMsgBuf;
        FormatMessage(
                      FORMAT_MESSAGE_ALLOCATE_BUFFER |
                      FORMAT_MESSAGE_FROM_SYSTEM |
                      FORMAT_MESSAGE_IGNORE_INSERTS,
                      NULL,
                      err,
                      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                      (LPTSTR) &lpMsgBuf,
                      0,
                      NULL
                      );
        wprintf(L"Error loading %s: %s\n", xpcomFile, lpMsgBuf);
        LocalFree(lpMsgBuf);
#endif        
        return (err == ERROR_NOT_ENOUGH_MEMORY || err == ERROR_OUTOFMEMORY)
            ? NS_ERROR_OUT_OF_MEMORY : NS_ERROR_FAILURE;
    }

    AppendDependentLib(h);

    GetFrozenFunctionsFunc sym =
        (GetFrozenFunctionsFunc) GetProcAddress(h, "NS_GetFrozenFunctions");

    if (!sym) { // No symbol found.
        XPCOMGlueUnload();
        return NS_ERROR_NOT_AVAILABLE;
    }

    *func = sym;

    return NS_OK;
}