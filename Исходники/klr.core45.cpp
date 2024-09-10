HMODULE LoadCoreClr()
{
    errno_t errno = 0;

    TCHAR szCoreClrDirectory[MAX_PATH];
    DWORD dwCoreClrDirectory = GetEnvironmentVariableW(L"CORECLR_DIR", szCoreClrDirectory, MAX_PATH);
    HMODULE hCoreCLRModule = nullptr;

    if (dwCoreClrDirectory != 0)
    {
        WCHAR wszClrPath[MAX_PATH];
        wszClrPath[0] = L'\0';

        errno = wcscpy_s(wszClrPath, _countof(wszClrPath), szCoreClrDirectory);
        CHECK_RETURN_VALUE_FAIL_EXIT_VIA_FINISHED(errno);

        if (wszClrPath[wcslen(wszClrPath) - 1] != L'\\')
        {
            errno = wcscat_s(wszClrPath, _countof(wszClrPath), L"\\");
            CHECK_RETURN_VALUE_FAIL_EXIT_VIA_FINISHED(errno);
        }

        errno = wcscat_s(wszClrPath, _countof(wszClrPath), L"coreclr.dll");
        CHECK_RETURN_VALUE_FAIL_EXIT_VIA_FINISHED(errno);

        // Add the core clr directory to the list of dll search paths
        AddDllDirectory(szCoreClrDirectory);

        // Modify the default dll flags so that dependencies can be found in this path
        SetDefaultDllDirectories(LOAD_LIBRARY_SEARCH_DEFAULT_DIRS | LOAD_LIBRARY_SEARCH_USER_DIRS);

        // Continue loading as usual
        hCoreCLRModule = ::LoadLibraryExW(wszClrPath, NULL, 0);
    }

    if (hCoreCLRModule == nullptr)
    {
        // This is used when developing
#if AMD64
        hCoreCLRModule = ::LoadLibraryExW(L"..\\..\\..\\artifacts\\build\\ProjectK\\Runtime\\amd64\\coreclr.dll", NULL, 0);
#else
        hCoreCLRModule = ::LoadLibraryExW(L"..\\..\\..\\artifacts\\build\\ProjectK\\Runtime\\x86\\coreclr.dll", NULL, 0);
#endif
    }

    if (hCoreCLRModule == nullptr)
    {
        // Try the relative location based in install

        hCoreCLRModule = ::LoadLibraryExW(L"coreclr.dll", NULL, 0);
    }

Finished:
    return hCoreCLRModule;
}