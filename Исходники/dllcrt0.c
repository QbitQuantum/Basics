BOOL WINAPI _CRT_INIT(
    HANDLE  hDllHandle,
    DWORD   dwReason,
    LPVOID  lpreserved
) {
    unsigned int osplatform = 0;
    unsigned int winver = 0;
    unsigned int winmajor = 0;
    unsigned int winminor = 0;
    unsigned int osver = 0;

    /*
     * Start-up code only gets executed when the process is initialized
     */

    if (dwReason == DLL_PROCESS_ATTACH) {
        /*
         * Dynamically allocate the OSVERSIONINFOA buffer, so we avoid
         * triggering the /GS buffer overrun detection.  That can't be
         * used here, since the guard cookie isn't available until we
         * initialize it from here!
         */
        OSVERSIONINFOA* posvi =
            (OSVERSIONINFOA*)HeapAlloc(GetProcessHeap(), 0, sizeof(OSVERSIONINFOA));

        if (!posvi) {
            return FALSE;
        }

        /*
         * Get the full Win32 version
         */
        posvi->dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);

        if (!GetVersionExA(posvi)) {
            HeapFree(GetProcessHeap(), 0, posvi);
            return FALSE;
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

        if (!_heap_init(1)) {   /* initialize heap */
            return FALSE;    /* fail to load DLL */
        }

        if (!_mtinit()) {       /* initialize multi-thread */
            _heap_term();       /* heap is now invalid! */
            return FALSE;       /* fail to load DLL */
        }

        /*
         * Initialize the Runtime Checks stuff
         */
#ifdef _RTC
        _RTC_Initialize();
#endif  /* _RTC */
        _acmdln = (char*)GetCommandLineA();
        _aenvptr = (char*)__crtGetEnvironmentStringsA();

        if (_ioinit() < 0) {    /* initialize lowio */
            _mtterm();          /* free TLS index, call _mtdeletelocks() */
            _heap_term();       /* heap is now invalid! */
            return FALSE;       /* fail to load DLL */
        }

        if (_setargv() < 0 ||   /* get cmd line info */
                _setenvp() < 0 ||   /* get environ info */
                _cinit(FALSE) != 0) { /* do C data initialize, but don't init floating point */
            _ioterm();          /* shut down lowio */
            _mtterm();          /* free TLS index, call _mtdeletelocks() */
            _heap_term();       /* heap is now invalid! */
            return FALSE;       /* fail to load DLL */
        }

        /* Enable buffer count checking if linking against static lib */
        _CrtSetCheckCount(TRUE);
        /*
         * increment flag to indicate process attach notification
         * has been received
         */
        __proc_attached++;
    } else if (dwReason == DLL_PROCESS_DETACH) {
        if (__proc_attached > 0) {
            __proc_attached--;

            /*
             * Any basic clean-up code that goes here must be duplicated
             * below in _DllMainCRTStartup for the case where the user's
             * DllMain() routine fails on a Process Attach notification.
             * This does not include calling user C++ destructors, etc.
             */

            if (_C_Termination_Done == FALSE) {
                _cexit();
            }

#ifdef _DEBUG

            /* Dump all memory leaks */
            if (_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) & _CRTDBG_LEAK_CHECK_DF) {
                _CrtDumpMemoryLeaks();
            }

#endif  /* _DEBUG */
            /*
             * What remains is to clean up the system resources we have
             * used (handles, critical sections, memory,...,etc.). This
             * needs to be done if the whole process is NOT terminating.
             */
#ifndef _DEBUG

            if (lpreserved == NULL) {
#endif  /* _DEBUG */
                /*
                 * The process is NOT terminating so we must clean up...
                 */
                /* Shut down lowio */
                _ioterm();
                _mtterm();
                /* This should be the last thing the C run-time does */
                _heap_term();   /* heap is now invalid! */
#ifndef _DEBUG
            }

#endif  /* _DEBUG */
        } else
            /* no prior process attach, just return */
        {
            return FALSE;
        }
    } else if (dwReason == DLL_THREAD_ATTACH) {
        _ptiddata ptd;
        /* Initialize FlsGetValue function pointer */
        __set_flsgetvalue();

        if (((ptd = _calloc_crt(1, sizeof(struct _tiddata))) != NULL)) {
            if (FLS_SETVALUE(__flsindex, (LPVOID)ptd)) {
                /*
                 * Initialize of per-thread data
                 */
                _initptd(ptd, NULL);
                ptd->_tid = GetCurrentThreadId();
                ptd->_thandle = (uintptr_t)(-1);
            } else {
                _free_crt(ptd);
                return FALSE;
            }
        } else {
            return FALSE;
        }
    } else if (dwReason == DLL_THREAD_DETACH) {
        _freeptd(NULL);         /* free up per-thread CRT data */
    }

    return TRUE ;
}