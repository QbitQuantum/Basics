int WINAPI _tWinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPTSTR lpCmdLine,
  int nCmdShow
)
{
    int argc;
    TCHAR szMsg[RC_STRING_MAX_SIZE];

    LPTSTR *argv;
    LPTSTR lptCmdLine,lptDllName,lptFuncName,lptMsgBuffer;
    LPSTR lpFuncName,lpaCmdLine;
    LPWSTR lpwCmdLine;
    HMODULE hDll;
    DllWinMainW fnDllWinMainW;
    DllWinMainA fnDllWinMainA;
    HWND hWindow;
    int i;
    size_t nStrLen;

    ACTCTXW ActCtx = {sizeof(ACTCTX), ACTCTX_FLAG_RESOURCE_NAME_VALID};
    HANDLE hActCtx;
    ULONG_PTR cookie;
    BOOL bActivated;

    // Get command-line in argc-argv format
    argv = CommandLineToArgv(GetCommandLine(),&argc);

    // Skip all beginning arguments starting with a slash (/)
    for (i = 1; i < argc; i++)
        if (*argv[i] != _T('/')) break;

    // If no dll was specified, there is nothing to do
    if (i >= argc) {
        if (argv) free(argv);
        return 0;
    }

    lptDllName = argv[i++];

    // The next argument, which specifies the name of the dll function,
    // can either have a comma between it and the dll filename or a space.
    // Using a comma here is the preferred method
    if (i < argc)
        lptFuncName = argv[i++];
    else
        lptFuncName = _T("");

    // If no function name was specified, nothing needs to be done
    if (!*lptFuncName) {
        if (argv) free(argv);
        return 0;
    }

    // The rest of the arguments will be passed to dll function
    if (i < argc)
        lptCmdLine = argv[i];
    else
        lptCmdLine = _T("");

    ActCtx.lpSource = lptDllName;
    ActCtx.lpResourceName = (LPCWSTR)123;
    hActCtx = CreateActCtx(&ActCtx);
    bActivated = (hActCtx != INVALID_HANDLE_VALUE ? ActivateActCtx(hActCtx, &cookie) : FALSE);

    // Everything is all setup, so load the dll now
    hDll = LoadLibrary(lptDllName);
    if (hDll) {
        nStrLen = _tcslen(lptFuncName);
        // Make a non-unicode version of the function name,
        // since that is all GetProcAddress accepts
        lpFuncName = DuplicateToMultiByte(lptFuncName,nStrLen + 2);

#ifdef UNICODE
        lpFuncName[nStrLen] = 'W';
        lpFuncName[nStrLen+1] = 0;
        // Get address of unicode version of the dll function if it exists
        fnDllWinMainW = (DllWinMainW)GetProcAddress(hDll,lpFuncName);
        fnDllWinMainA = 0;
        if (!fnDllWinMainW) {
            // If no unicode function was found, get the address of the non-unicode function
            lpFuncName[nStrLen] = 'A';
            fnDllWinMainA = (DllWinMainA)GetProcAddress(hDll,lpFuncName);
            if (!fnDllWinMainA) {
                // If first non-unicode function was not found, get the address
                // of the other non-unicode function
                lpFuncName[nStrLen] = 0;
                fnDllWinMainA = (DllWinMainA)GetProcAddress(hDll,lpFuncName);
            }
        }
#else
        // Get address of non-unicode version of the dll function if it exists
        fnDllWinMainA = (DllWinMainA)GetProcAddress(hDll,lpFuncName);
        fnDllWinMainW = 0;
        if (!fnDllWinMainA) {
            // If first non-unicode function was not found, get the address
            // of the other non-unicode function
            lpFuncName[nStrLen] = 'A';
            lpFuncName[nStrLen+1] = 0;
            fnDllWinMainA = (DllWinMainA)GetProcAddress(hDll,lpFuncName);
            if (!fnDllWinMainA) {
                // If non-unicode function was not found, get the address of the unicode function
                lpFuncName[nStrLen] = 'W';
                fnDllWinMainW = (DllWinMainW)GetProcAddress(hDll,lpFuncName);
            }
        }
#endif

        free(lpFuncName);

        if (!RegisterBlankClass(hInstance, hPrevInstance))
        {
            FreeLibrary(hDll);
            if (bActivated)
                DeactivateActCtx(0, cookie);
            return 0;
        }
        // Create a window so we can pass a window handle to
        // the dll function; this is required
        hWindow = CreateWindowEx(0,rundll32_wclass,rundll32_wtitle,0,CW_USEDEFAULT,0,CW_USEDEFAULT,0,0,0,hInstance,0);

        if (fnDllWinMainW) {
            // Convert the command-line string to unicode and call the dll function
            lpwCmdLine = ConvertToWideChar(lptCmdLine);
            fnDllWinMainW(hWindow,hInstance,lpwCmdLine,nCmdShow);
            FreeConvertedWideChar(lpwCmdLine);
        }
        else if (fnDllWinMainA) {
            // Convert the command-line string to ansi and call the dll function
            lpaCmdLine = ConvertToMultiByte(lptCmdLine);
            fnDllWinMainA(hWindow,hInstance,lpaCmdLine,nCmdShow);
            FreeConvertedMultiByte(lpaCmdLine);
        }
        else {
            // The specified dll function was not found; display an error message
            GetModuleTitle();
            LoadString( GetModuleHandle(NULL), IDS_MissingEntry, (LPTSTR) szMsg,RC_STRING_MAX_SIZE);

            lptMsgBuffer = (LPTSTR)malloc((_tcslen(szMsg) - 4 + _tcslen(lptFuncName) + _tcslen(lptDllName) + 1) * sizeof(TCHAR));
            _stprintf(lptMsgBuffer,szMsg,lptFuncName,lptDllName);
            MessageBox(0,lptMsgBuffer,ModuleTitle,MB_ICONERROR);
            free(lptMsgBuffer);
        }

        DestroyWindow(hWindow);
        UnregisterClass(rundll32_wclass,hInstance);

        // The dll function has finished executing, so unload it
        FreeLibrary(hDll);
    }
    else {
        // The dll could not be loaded; display an error message
        GetModuleTitle();
        LoadString( GetModuleHandle(NULL), IDS_DllNotLoaded, (LPTSTR) szMsg,RC_STRING_MAX_SIZE);

        lptMsgBuffer = (LPTSTR)malloc((_tcslen(szMsg) - 2 + _tcslen(lptDllName) + 1) * sizeof(TCHAR));
        _stprintf(lptMsgBuffer,szMsg,lptDllName);

        MessageBox(0,lptMsgBuffer,ModuleTitle,MB_ICONERROR);
        free(lptMsgBuffer);
    }

    if (bActivated)
        DeactivateActCtx(0, cookie);

    if (argv) free(argv);
    return 0; /* rundll32 always returns 0! */
}