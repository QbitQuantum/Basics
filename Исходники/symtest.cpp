int __cdecl main(void)
{
    printf("symtest.exe: Starting.\n");
    fflush(stdout);

    //////////////////////////////////////////////////////// Get the functions.
    //
    HMODULE hDbgHelp = LoadLibraryA("dbghelp.dll");
    if (hDbgHelp == NULL) {
        printf("Couldn't load dbghelp.dll");
        return 1;
    }

    pfImagehlpApiVersionEx
        = (PF_ImagehlpApiVersionEx)GetProcAddress(hDbgHelp,
                                                  "ImagehlpApiVersionEx");
    pfSymInitialize
        = (PF_SymInitialize)GetProcAddress(hDbgHelp, "SymInitialize");
    pfSymSetOptions
        = (PF_SymSetOptions)GetProcAddress(hDbgHelp, "SymSetOptions");
    pfSymGetOptions
        = (PF_SymGetOptions)GetProcAddress(hDbgHelp, "SymGetOptions");
    pfSymLoadModule64
        = (PF_SymLoadModule64)GetProcAddress(hDbgHelp, "SymLoadModule64");
    pfSymGetModuleInfo64
        = (PF_SymGetModuleInfo64)GetProcAddress(hDbgHelp, "SymGetModuleInfo64");
    pfSymFromName
        = (PF_SymFromName)GetProcAddress(hDbgHelp, "SymFromName");
    pfSymRegisterCallback64
        = (PF_SymRegisterCallback64)GetProcAddress(hDbgHelp, "SymRegisterCallback64");
    pfSymEnumerateModules64
        = (PF_SymEnumerateModules64)GetProcAddress(hDbgHelp, "SymEnumerateModules64");
    pfSymEnumSymbols
        = (PF_SymEnumSymbols)GetProcAddress(hDbgHelp, "SymEnumSymbols");

    //////////////////////////////////////////////////////////////////////////////
    //
    HANDLE hProcess = GetCurrentProcess();

    API_VERSION av;
    ZeroMemory(&av, sizeof(av));
    av.MajorVersion = API_VERSION_NUMBER;

    pfImagehlpApiVersionEx(&av);
    printf("  Version: %d.%d (%d)\n",
                  av.MajorVersion,
                  av.MinorVersion,
                  API_VERSION_NUMBER);

    if (!pfSymInitialize(hProcess, NULL, FALSE)) {
        printf("SymInitialize failed: %d\n", GetLastError());
        return 1;
    }

#if (_MSC_VER > 1299)
    pfSymRegisterCallback64(hProcess, CallbackFunction, NULL);
#endif

    DWORD dw = pfSymGetOptions();
    printf("GetOptions = %08x\n", dw);
    dw &= ~(SYMOPT_CASE_INSENSITIVE |
            SYMOPT_UNDNAME |
            SYMOPT_DEFERRED_LOADS |
            0);
    dw |= (
#if defined(SYMOPT_EXACT_SYMBOLS)
           SYMOPT_EXACT_SYMBOLS |
#endif
#if defined(SYMOPT_DEBUG)
           SYMOPT_DEBUG |
#endif
#if defined(SYMOPT_NO_UNQUALIFIED_LOADS)
           SYMOPT_NO_UNQUALIFIED_LOADS |
#endif
#if defined(SYMOPT_FAIL_CRITICAL_ERRORS)
           SYMOPT_FAIL_CRITICAL_ERRORS |
#endif
#if defined(SYMOPT_INCLUDE_32BIT_MODULES)
           SYMOPT_INCLUDE_32BIT_MODULES |
#endif
           0);
    printf("SetOptions = %08x\n", dw);
    pfSymSetOptions(dw);

    /////////////////////////////////////////////// First, try GetProcAddress.
    //
    PCHAR pszFile = "target.dll";
    HMODULE hModule = LoadLibraryA(pszFile);
    if (hModule == NULL) {
        printf("LoadLibraryA(%s) failed: %d\n", pszFile, GetLastError());
        return 2;
    }

    ////////////////////////////////////////////////////// Then try ImageHelp.
    //
#if (_MSC_VER > 1299)

    //CHAR szFull[MAX_PATH];
    //GetModuleFileNameA(hModule, szFull, sizeof(szFull));
    printf("SymLoadModule64(%s) will be called.\n", pszFile /*szFull*/);
    DWORD64 loaded = pfSymLoadModule64(hProcess, NULL,
                                       (PCHAR)pszFile/*szFull*/, NULL,
                                       (DWORD64)hModule, 0);
    if (loaded == 0) {
        printf("SymLoadModule64(%p) failed: %d\n", hProcess, GetLastError());
        printf("\n");
    }
    else {
        printf("SymLoadModule64(%p) succeeded: 0x%p\n", hProcess, (PVOID)loaded);
    }

    CHAR szModName[512];

    printf("Modules:\n");
// The first parameter of PSYM_ENUMMODULES_CALLBACK64 changed from PSTR to PCSTR
// between Windows 2003 and Windows 7. Cast here to work with either.
    pfSymEnumerateModules64(hProcess, (PSYM_ENUMMODULES_CALLBACK64)SymEnumerateCallback, NULL);
    printf("\n");

    IMAGEHLP_MODULE64 modinfo;
    ZeroMemory(&modinfo, sizeof(modinfo));
    modinfo.SizeOfStruct = 512/*sizeof(modinfo)*/;
    if (!pfSymGetModuleInfo64(hProcess, (DWORD64)hModule, &modinfo)) {
        printf("SymGetModuleInfo64(%p, %p) [64] failed: %d\n",
                      hProcess, hModule, GetLastError());
    }
    else {
        printf("SymGetModuleInfo64(%p, %p) [64] succeeded: %d\n",
                      hProcess, hModule, GetLastError());
        StringCchCopyA(szModName, ARRAYSIZE(szModName), modinfo.ModuleName);
        StringCchCatA(szModName, ARRAYSIZE(szModName), "!");

        printf("NumSyms:         %d\n", modinfo.NumSyms);
        printf("SymType:         %d\n", modinfo.SymType);
        printf("ModuleName:      %s\n", modinfo.ModuleName);
        printf("ImageName:       %s\n", modinfo.ImageName);
        printf("LoadedImageName: %s\n", modinfo.LoadedImageName);
    }

    printf("\n");
    fflush(stdout);

    printf("DLLs:\n");
    for (hModule = NULL; (hModule = DetourEnumerateModules(hModule)) != NULL;) {
        CHAR szName[MAX_PATH];
        GetModuleFileNameA(hModule, szName, sizeof(szName));
        printf("  %p: %s\n", hModule, szName);
    }

    if (pfSymEnumSymbols == NULL) {
        printf("Couldn't find SymEnumSymbols.\n");
    }
    else {
        printf("===Enum===\n");
        SetLastError(0);
        nSymbolCount = 0;
        if (!pfSymEnumSymbols(hProcess, (DWORD64)hModule, NULL, SymEnumerateSymbols, NULL)) {
            printf("SymEnumSymbols() failed: %d\n",
                          GetLastError());
        }
    }

    // Look for specific symbols.
    struct CFullSymbol : SYMBOL_INFO {
        CHAR szRestOfName[MAX_SYM_NAME];
    } symbol;
    CHAR szFullName[512];

    // Look for Target
    StringCchCopyA(szFullName, ARRAYSIZE(szFullName), szModName);
    StringCchCatA(szFullName, ARRAYSIZE(szFullName), "Target");
    printf("Symbol: [%s]\n", szFullName);

    ZeroMemory(&symbol, sizeof(symbol));
    symbol.SizeOfStruct = sizeof(SYMBOL_INFO);
#ifdef DBHLPAPI
    symbol.MaxNameLen = MAX_SYM_NAME;
#else
    symbol.MaxNameLength = MAX_SYM_NAME;
#endif

    SetLastError(0);
    if (!pfSymFromName(hProcess, szFullName, &symbol)) {
        printf("--SymFromName(%s) failed: %d\n", szFullName, GetLastError());
    }
    if (symbol.Address != 0) {
        printf("--SymFromName(%s) succeeded\n", szFullName);
    }

    printf("%s => %p\n\n", szFullName, (PBYTE)symbol.Address);

    // Look for Hidden
    StringCchCopyA(szFullName, ARRAYSIZE(szFullName), szModName);
    StringCchCatA(szFullName, ARRAYSIZE(szFullName), "Hidden");
    printf("Symbol: [%s]\n", szFullName);

    ZeroMemory(&symbol, sizeof(symbol));
    symbol.SizeOfStruct = sizeof(SYMBOL_INFO);
#ifdef DBHLPAPI
    symbol.MaxNameLen = MAX_SYM_NAME;
#else
    symbol.MaxNameLength = MAX_SYM_NAME;
#endif

    SetLastError(0);
    if (!pfSymFromName(hProcess, szFullName, &symbol)) {
        printf("--SymFromName(%s) failed: %d\n", szFullName, GetLastError());
    }
    if (symbol.Address != 0) {
        printf("--SymFromName(%s) succeeded\n", szFullName);
    }

    printf("%s => %p\n\n", szFullName, (PBYTE)symbol.Address);
#endif

    // We call Target once to insure it is loaded.
    Target(0);
    return 0;
}