int DebuggerInitialize( LPCSTR pszBOINCLocation, LPCSTR pszSymbolStore, BOOL bProxyEnabled, LPCSTR pszProxyServer )
{
    if (g_bInitialized != FALSE)
        return 0;

    // Get a real handle to the current process and store it for future use.
    DuplicateHandle(
        GetCurrentProcess(),
        GetCurrentProcess(),
        GetCurrentProcess(), 
        &g_hProcess, 
        0,
        false,
        DUPLICATE_SAME_ACCESS
    );

    // Detect which version of Windows we are running on.
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx((OSVERSIONINFO*)&osvi);

    // For the most part the dbghelp.dll does the right stuff, but there are
    // conditions where things go off into never never land.  Most of the
    // time the error comes back ERROR_MOD_NOT_FOUND.  Most of the info
    // out on the net describes conditions in which dbghelp.dll is trying
    // to dynamically load another module such as symsrv.dll and fails to
    // find it.  Preloading the module only seems to work on some machines.
    // On Windows XP or better a new API has been introduced called
    // SetDllDirectory which will inject a path into the search order
    // that is before the System and Windows directories which is what we
    // want.
    if ((VER_PLATFORM_WIN32_NT == osvi.dwPlatformId) &&
        ((6 >= osvi.dwMajorVersion) ||                                  // == Vista, Win2008, +
         (5 == osvi.dwMajorVersion) && (0 != osvi.dwMinorVersion)))     // == Win XP, Win2003
    {
        HMODULE hKernel32 = LoadLibraryA("kernel32.dll");
        if (hKernel32) {
            pSDD = (tSDD)GetProcAddress( hKernel32, "SetDllDirectoryA" );
            if (!pSDD(pszBOINCLocation)) {
                fprintf(stderr, "SetDllDirectory(): GetLastError = %lu\n", gle);
            }
            FreeLibrary(hKernel32);
            hKernel32 = NULL;
            pSDD = NULL;
        }
    }


    if (!DebuggerLoadLibrary(&g_hDbgHelpDll, pszBOINCLocation, "dbghelp.dll")) {
        g_bInitialized = FALSE;
        return 1;
    }

    DebuggerLoadLibrary(&g_hSymSrvDll,  pszBOINCLocation, "symsrv.dll");
    DebuggerLoadLibrary(&g_hSrcSrvDll,  pszBOINCLocation, "srcsrv.dll");
    DebuggerLoadLibrary(&g_hVersionDll, pszBOINCLocation, "version.dll");

    if (g_hSymSrvDll) {
        pSSSO = (tSSSO)GetProcAddress(g_hSymSrvDll, "SymbolServerSetOptions");
        if (pSSSO) {
            if (!pSSSO(SSRVOPT_TRACE, (ULONG64)TRUE)) {
                fprintf(stderr, "SymbolServerSetOptions(): Register Trace Failed, GetLastError = %lu\n", gle);
            }
            if (!pSSSO(SSRVOPT_CALLBACK, (ULONG64)SymbolServerCallbackProc64)) {
                fprintf(stderr, "SymbolServerSetOptions(): Register Callback Failed, GetLastError = %lu\n", gle);
            }
            if (!pSSSO(SSRVOPT_UNATTENDED, (ULONG64)TRUE)) {
                fprintf(stderr, "SymbolServerSetOptions(): Register Unattended Failed, GetLastError = %lu\n", gle);
            }
            if (bProxyEnabled) {
                if (!pSSSO(SSRVOPT_PROXY, (ULONG64)pszProxyServer)) {
                    fprintf(stderr, "SymbolServerSetOptions(): Register Proxy Failed, GetLastError = %lu\n", gle);
                }
            } else {
                if (!pSSSO(SSRVOPT_PROXY, (ULONG64)NULL)) {
                    fprintf(stderr, "SymbolServerSetOptions(): Register Proxy Failed, GetLastError = %lu\n", gle);
                }
            }
        }
    }


    if (g_hVersionDll) {
        pGFVIS = (tGFVIS)GetProcAddress(g_hVersionDll, "GetFileVersionInfoSizeA");
        pGFVI = (tGFVI)GetProcAddress(g_hVersionDll, "GetFileVersionInfoA");
        pVQV = (tVQV)GetProcAddress(g_hVersionDll, "VerQueryValueA");
    }

    pIAV = (tIAV) GetProcAddress( g_hDbgHelpDll, "ImagehlpApiVersion" );
    pSC = (tSC) GetProcAddress( g_hDbgHelpDll, "SymCleanup" );
    pSEM = (tSEM) GetProcAddress( g_hDbgHelpDll, "SymEnumerateModules64" );
    pSFTA = (tSFTA) GetProcAddress( g_hDbgHelpDll, "SymFunctionTableAccess64" );
    pSGLFA = (tSGLFA) GetProcAddress( g_hDbgHelpDll, "SymGetLineFromAddr64" );
    pSGMB = (tSGMB) GetProcAddress( g_hDbgHelpDll, "SymGetModuleBase64" );
    pSGMI = (tSGMI) GetProcAddress( g_hDbgHelpDll, "SymGetModuleInfo64" );
    pSGO = (tSGO) GetProcAddress( g_hDbgHelpDll, "SymGetOptions" );
    pSGSP = (tSGSP) GetProcAddress( g_hDbgHelpDll, "SymGetSearchPath" );
    pSFA = (tSFA) GetProcAddress( g_hDbgHelpDll, "SymFromAddr" );
    pSI = (tSI) GetProcAddress( g_hDbgHelpDll, "SymInitialize" );
    pSRC = (tSRC) GetProcAddress( g_hDbgHelpDll, "SymRegisterCallback64" );
    pSSO = (tSSO) GetProcAddress( g_hDbgHelpDll, "SymSetOptions" );
    pSW = (tSW) GetProcAddress( g_hDbgHelpDll, "StackWalk64" );
    pUDSN = (tUDSN) GetProcAddress( g_hDbgHelpDll, "UnDecorateSymbolName" );
    pSLM = (tSLM) GetProcAddress( g_hDbgHelpDll, "SymLoadModuleEx" );

    if ( pIAV == NULL || pSC == NULL || pSEM == NULL || pSFTA == NULL ||
         pSGMB == NULL || pSGMI == NULL || pSGO == NULL || pSFA == NULL ||
         pSI == NULL || pSRC == NULL || pSSO == NULL || pSW == NULL ||
         pUDSN == NULL || pSLM == NULL )
    {
        if (!pIAV)   fprintf( stderr, "GetProcAddress(): ImagehlpApiVersion missing.\n" );
        if (!pSC)    fprintf( stderr, "GetProcAddress(): SymCleanup missing.\n" );
        if (!pSEM)   fprintf( stderr, "GetProcAddress(): SymEnumerateModules64 missing.\n" );
        if (!pSFTA)  fprintf( stderr, "GetProcAddress(): SymFunctionTableAccess64 missing.\n" );
        if (!pSGLFA) fprintf( stderr, "GetProcAddress(): SymGetLineFromAddr64 missing.\n" );
        if (!pSGMB)  fprintf( stderr, "GetProcAddress(): SymGetModuleBase64 missing.\n" );
        if (!pSGMI)  fprintf( stderr, "GetProcAddress(): SymGetModuleInfo64 missing.\n" );
        if (!pSGO)   fprintf( stderr, "GetProcAddress(): SymGetOptions missing.\n" );
        if (!pSGSP)  fprintf( stderr, "GetProcAddress(): SymGetSearchPath missing.\n" );
        if (!pSFA)   fprintf( stderr, "GetProcAddress(): SymFromAddr missing.\n" );
        if (!pSI)    fprintf( stderr, "GetProcAddress(): SymInitialize missing.\n" );
        if (!pSRC)   fprintf( stderr, "GetProcAddress(): SymRegisterCallback64 missing.\n" );
        if (!pSSO)   fprintf( stderr, "GetProcAddress(): SymSetOptions missing.\n" );
        if (!pSW)    fprintf( stderr, "GetProcAddress(): StackWalk64 missing.\n" );
        if (!pUDSN)  fprintf( stderr, "GetProcAddress(): UnDecorateSymbolName missing.\n" );
        if (!pSLM)   fprintf( stderr, "GetProcAddress(): SymLoadModuleEx missing.\n" );

        FreeLibrary( g_hDbgHelpDll );
        g_bInitialized = FALSE;
        return 1;
    }

    g_bInitialized = TRUE;

    InitializeCriticalSection(&g_csFileOpenClose);
    EnterCriticalSection(&g_csFileOpenClose);

    CHAR* tt;
    CHAR* p;
    DWORD symOptions; // symbol handler settings
    std::string strCurrentDirectory;
    std::string strExecutableDirectory;
    std::string strLocalSymbolStore;
    std::string strSymbolSearchPath;

    tt = (CHAR*) malloc(sizeof(CHAR) * TTBUFLEN); // Get the temporary buffer
    if (!tt) return 1;  // not enough memory...

    // build symbol search path from:
    strCurrentDirectory = "";
    strExecutableDirectory = "";
    strLocalSymbolStore = "";
    strSymbolSearchPath = "";

    // Detect Current Directory
    if ( GetCurrentDirectoryA( TTBUFLEN, tt ) ) {
        strCurrentDirectory = tt;
    }

    // Detect Executable Directory
    if ( GetModuleFileNameA( 0, tt, TTBUFLEN ) )
    {
        for ( p = tt + strlen( tt ) - 1; p >= tt; -- p )
        {
            // locate the rightmost path separator
            if ( *p == '\\' || *p == '/' || *p == ':' ) {
                break;
            }
        }

        // if we found one, p is pointing at it; if not, tt only contains
        // an exe name (no path), and p points before its first byte
        if ( p != tt ) // path sep found?
        {
            if ( *p == ':' )  { // we leave colons in place
                ++p;
            }

            *p = '\0'; // eliminate the exe name and last path sep
            strExecutableDirectory += tt;
        }
    }

    // Current Directory
    if (!strCurrentDirectory.empty()) {
        strSymbolSearchPath += strCurrentDirectory + std::string( ";" );
    }

    // Executable Directory
    if (!strExecutableDirectory.empty()) {
        strSymbolSearchPath += strExecutableDirectory + std::string( ";" );
    }

    // Environment Variable _NT_SYMBOL_PATH
    if ( GetEnvironmentVariableA( "_NT_SYMBOL_PATH", tt, TTBUFLEN ) ) {
        strSymbolSearchPath += tt + std::string( ";" );
    }

    // Environment Variable _NT_ALTERNATE_SYMBOL_PATH
    if ( GetEnvironmentVariableA( "_NT_ALT_SYMBOL_PATH", tt, TTBUFLEN ) ) {
        strSymbolSearchPath += tt + std::string( ";" );
    }

    // Depending on if we are a BOINC application or a project application
    // we'll need to store our symbol files in two different locations.
    //
    // BOINC:
    //   [DATADIR]\symbols
    // Project:
    //   [DATADIR]\projects\project_dir\symbols
    //
    if (!diagnostics_is_flag_set(BOINC_DIAG_BOINCAPPLICATION)) {
        strLocalSymbolStore += strCurrentDirectory + std::string("\\symbols");
    } else {
        strLocalSymbolStore += strExecutableDirectory + std::string("\\symbols");
    }

    // Microsoft Public Symbol Server
	if (!diagnostics_is_flag_set(BOINC_DIAG_BOINCAPPLICATION) || (0 < strlen(pszSymbolStore))) {
		if (std::string::npos == strSymbolSearchPath.find("http://msdl.microsoft.com/download/symbols")) {
			strSymbolSearchPath += 
				std::string( "srv*" ) + strLocalSymbolStore + 
				std::string( "*http://msdl.microsoft.com/download/symbols;" );
		}
	}

    // Project Symbol Server
	if (diagnostics_is_flag_set(BOINC_DIAG_BOINCAPPLICATION) && (0 < strlen(pszSymbolStore))) {
		if ((std::string::npos == strSymbolSearchPath.find(pszSymbolStore)) && (0 < strlen(pszSymbolStore))) {
			strSymbolSearchPath += 
				std::string( "srv*" ) + strLocalSymbolStore + std::string( "*" ) +
				std::string( pszSymbolStore ) + std::string( ";" );
		}
	}

    // BOINC Symbol Server
	if (!diagnostics_is_flag_set(BOINC_DIAG_BOINCAPPLICATION)) {
		if (std::string::npos == strSymbolSearchPath.find("http://boinc.berkeley.edu/symstore")) {
			strSymbolSearchPath += 
				std::string( "srv*" ) + strLocalSymbolStore + 
				std::string( "*http://boinc.berkeley.edu/symstore;" );
		}
	}

    if ( strSymbolSearchPath.size() > 0 ) // if we added anything, we have a trailing semicolon
        strSymbolSearchPath = strSymbolSearchPath.substr( 0, strSymbolSearchPath.size() - 1 );

    if (tt) {
        free( tt );
    }

    // Setting symbol options to the WinDbg defaults.
    symOptions = (DWORD)NULL;
    symOptions |= SYMOPT_CASE_INSENSITIVE;
    symOptions |= SYMOPT_LOAD_LINES;
    symOptions |= SYMOPT_OMAP_FIND_NEAREST;
    symOptions |= SYMOPT_FAIL_CRITICAL_ERRORS;
    symOptions |= SYMOPT_AUTO_PUBLICS;
    symOptions |= SYMOPT_NO_IMAGE_SEARCH;
    symOptions |= SYMOPT_DEBUG;
    symOptions |= SYMOPT_NO_PROMPTS;
    pSSO( symOptions ); // SymSetOptions()

    // init symbol handler stuff (SymInitialize())
    if (!pSI(g_hProcess, strSymbolSearchPath.c_str(), TRUE))
    {
        fprintf(stderr, "SymInitialize(): GetLastError = %lu\n", gle);
        return 1;
    }

    if (!pSRC(g_hProcess, SymRegisterCallbackProc64, (ULONG64)g_hProcess))
    {
        fprintf(stderr, "SymRegisterCallback64(): GetLastError = %lu\n", gle);
    }

    LeaveCriticalSection(&g_csFileOpenClose);
    return 0;
}