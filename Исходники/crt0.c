int
__tmainCRTStartup(
    void
) {
    unsigned int osplatform = 0;
    unsigned int winver = 0;
    unsigned int winmajor = 0;
    unsigned int winminor = 0;
    unsigned int osver = 0;
    int initret;
    int mainret = 0;
    OSVERSIONINFOA* posvi;
    int managedapp;
#ifdef _WINMAIN_
    _TUCHAR* lpszCommandLine;
    STARTUPINFO StartupInfo;

    __try {
        /*
        Note: MSDN specifically notes that GetStartupInfo returns no error, and throws unspecified SEH if it fails, so
        the very general exception handler below is appropriate
        */
        GetStartupInfo(&StartupInfo);
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        return 255;
    }

#endif  /* _WINMAIN_ */
    /*
     * Dynamically allocate the OSVERSIONINFOA buffer, so we avoid
     * triggering the /GS buffer overrun detection.  That can't be
     * used here, since the guard cookie isn't available until we
     * initialize it from here!
     */
    posvi = (OSVERSIONINFOA*)HeapAlloc(GetProcessHeap(), 0, sizeof(OSVERSIONINFOA));

    if (!posvi) {
        fast_error_exit(_RT_HEAP);
        return 255;
    }

    /*
     * Get the full Win32 version
     */
    posvi->dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);

    if (!GetVersionExA(posvi)) {
        HeapFree(GetProcessHeap(), 0, posvi);
        return 255;
    }

    osplatform = posvi->dwPlatformId;
    winmajor = posvi->dwMajorVersion;
    winminor = posvi->dwMinorVersion;
    /*
     * The somewhat bizarre calculations of _osver and _winver are
     * required for backward compatibility (used to use GetVersion)
     */
    osver = (posvi->dwBuildNumber) & 0x07fff;
    HeapFree(GetProcessHeap(), 0, posvi);

    if (osplatform != VER_PLATFORM_WIN32_NT) {
        osver |= 0x08000;
    }

    winver = (winmajor << 8) + winminor;
    _set_osplatform(osplatform);
    _set_winver(winver);
    _set_winmajor(winmajor);
    _set_winminor(winminor);
    _set_osver(osver);
    /*
     * Determine if this is a managed application
     */
    managedapp = check_managed_app();

    if (!_heap_init(1)) {               /* initialize heap */
        fast_error_exit(_RT_HEAPINIT);    /* write message and die */
    }

    if (!_mtinit()) {                   /* initialize multi-thread */
        fast_error_exit(_RT_THREAD);    /* write message and die */
    }

    /* Enable buffer count checking if linking against static lib */
    _CrtSetCheckCount(TRUE);
    /*
     * Initialize the Runtime Checks stuff
     */
#ifdef _RTC
    _RTC_Initialize();
#endif  /* _RTC */
    /*
     * Guard the remainder of the initialization code and the call
     * to user's main, or WinMain, function in a __try/__except
     * statement.
     */

    __try {
        if (_ioinit() < 0) {            /* initialize lowio */
            _amsg_exit(_RT_LOWIOINIT);
        }

        /* get wide cmd line info */
        _tcmdln = (_TSCHAR*)GetCommandLineT();
        /* get wide environ info */
        _tenvptr = (_TSCHAR*)GetEnvironmentStringsT();

        if (_tsetargv() < 0) {
            _amsg_exit(_RT_SPACEARG);
        }

        if (_tsetenvp() < 0) {
            _amsg_exit(_RT_SPACEENV);
        }

        initret = _cinit(TRUE);                  /* do C data initialize */

        if (initret != 0) {
            _amsg_exit(initret);
        }

#ifdef _WINMAIN_
        lpszCommandLine = _twincmdln();
        mainret = _tWinMain((HINSTANCE)&__ImageBase,
                            NULL,
                            lpszCommandLine,
                            StartupInfo.dwFlags & STARTF_USESHOWWINDOW
                            ? StartupInfo.wShowWindow
                            : SW_SHOWDEFAULT
                           );
#else  /* _WINMAIN_ */
        _tinitenv = _tenviron;
        mainret = _tmain(__argc, _targv, _tenviron);
#endif  /* _WINMAIN_ */

        if (!managedapp) {
            exit(mainret);
        }

        _cexit();
    } __except (_XcptFilter(GetExceptionCode(), GetExceptionInformation())) {
        /*
         * Should never reach here
         */
        mainret = GetExceptionCode();

        if (!managedapp) {
            _exit(mainret);
        }

        _c_exit();
    } /* end of try - except */

    return mainret;
}