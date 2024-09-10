DWORD64 WINAPI
MgwSymLoadModuleExW(HANDLE hProcess,
                    HANDLE hFile,
                    PCWSTR ImageName,
                    PCWSTR ModuleName,
                    DWORD64 BaseOfDll,
                    DWORD DllSize,
                    PMODLOAD_DATA Data,
                    DWORD Flags)
{
    DWORD dwRet;

    dwRet = SymLoadModuleExW(hProcess, hFile, ImageName, ModuleName, BaseOfDll, DllSize, Data, Flags);

    if (BaseOfDll) {
        char ImageNameBuf[MAX_PATH];
        PCSTR ImageNameA;

        if (ImageName) {
            WideCharToMultiByte(CP_ACP, 0, ImageName, -1, ImageNameBuf, _countof(ImageNameBuf), NULL, NULL);
            ImageNameA = ImageNameBuf;
        } else {
            ImageNameA = NULL;
        }

        mgwhelp_module_lookup(hProcess, hFile, ImageNameA, BaseOfDll);
    }

    return dwRet;
}