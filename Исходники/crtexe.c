int
__tmainCRTStartup(
    void
) {
#ifdef _WINMAIN_
    _TUCHAR* lpszCommandLine;
    STARTUPINFO StartupInfo;
    BOOL inDoubleQuote = FALSE;

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
     * Guard the initialization code and the call to user's main, or
     * WinMain, function in a __try/__except statement.
     */

    __try {
        /*
         * There is a possiblity that the module where this object is
         * linked into is a mixed module. In all the cases we gurantee that
         * native initialization will occur before managed initialization.
         * Also in anycase this code should never be called when some other
         * code is initializing native code, that's why we exit in that case.
         *
         * Do runtime startup initializers.
         *
         * Note: the only possible entry we'll be executing here is for
         * __lconv_init, pulled in from charmax.obj only if the EXE was
         * compiled with -J.  All other .CRT$XI* initializers are only
         * run as part of the CRT itself, and so for the CRT DLL model
         * are not found in the EXE.  For that reason, we call _initterm,
         * not _initterm_e, because __lconv_init will never return failure,
         * and _initterm_e is not exported from the CRT DLL.
         *
         * Note further that, when using the CRT DLL, executing the
         * .CRT$XI* initializers is only done for an EXE, not for a DLL
         * using the CRT DLL.  That is to make sure the -J setting for
         * the EXE is not overriden by that of any DLL.
         */
        void* lock_free = 0;
        void* fiberid = ((PNT_TIB)NtCurrentTeb())->StackBase;
        int nested = FALSE;

        while ((lock_free = InterlockedCompareExchangePointer((volatile PVOID*)&__native_startup_lock, fiberid, 0)) != 0) {
            if (lock_free == fiberid) {
                nested = TRUE;
                break;
            }

            /* some other thread is running native startup/shutdown during a cctor/domain unload.
                Should only happen if this DLL was built using the Everett-compat loader lock fix in vcclrit.h
            */
            /* wait for the other thread to complete init before we return */
            Sleep(1000);
        }

        if (__native_startup_state == __initializing) {
            _amsg_exit(_RT_CRT_INIT_CONFLICT);
        } else if (__native_startup_state == __uninitialized) {
            __native_startup_state = __initializing;
#ifndef _SYSCRT

            if (_initterm_e(__xi_a, __xi_z) != 0) {
                return 255;
            }

#else  /* _SYSCRT */
            _initterm((_PVFV*)(void*)__xi_a, (_PVFV*)(void*)__xi_z);
#endif  /* _SYSCRT */
        } else {
            has_cctor = 1;
        }

        /*
        * do C++ constructors (initializers) specific to this EXE
        */
        if (__native_startup_state == __initializing) {
            _initterm(__xc_a, __xc_z);
            __native_startup_state = __initialized;
        }

        _ASSERTE(__native_startup_state == __initialized);

        if (!nested) {
            /* For X86, the definition of InterlockedExchangePointer wrongly causes warning C4312 */
#pragma warning(push)
#pragma warning(disable:4312)
            InterlockedExchangePointer((volatile PVOID*)&__native_startup_lock, 0);
#pragma warning(pop)
        }

        /*
         * If we have any dynamically initialized __declspec(thread)
         * variables, then invoke their initialization for the primary
         * thread used to start the process, by calling __dyn_tls_init
         * through a callback defined in tlsdyn.obj.
         */
        if (__dyn_tls_init_callback != NULL &&
                _IsNonwritableInCurrentImage((PBYTE)&__dyn_tls_init_callback)) {
            __dyn_tls_init_callback(NULL, DLL_THREAD_ATTACH, NULL);
        }

        /* Enable buffer count checking if linking against static lib */
        _CrtSetCheckCount(TRUE);
#ifdef _WINMAIN_
        /*
         * Skip past program name (first token in command line).
         * Check for and handle quoted program name.
         */
#ifdef WPRFLAG

        /* OS may not support "W" flavors */
        if (_wcmdln == NULL) {
            return 255;
        }

        lpszCommandLine = (wchar_t*)_wcmdln;
#else  /* WPRFLAG */
        lpszCommandLine = (unsigned char*)_acmdln;
#endif  /* WPRFLAG */

        while (*lpszCommandLine > SPACECHAR ||
                (*lpszCommandLine && inDoubleQuote)) {
            /*
             * Flip the count from 1 to 0 or 0 to 1 if current character
             * is DOUBLEQUOTE
             */
            if (*lpszCommandLine == DQUOTECHAR) {
                inDoubleQuote = !inDoubleQuote;
            }

#ifdef _MBCS

            if (_ismbblead(*lpszCommandLine)) {
                if (lpszCommandLine) {
                    lpszCommandLine++;
                }
            }

#endif  /* _MBCS */
            ++lpszCommandLine;
        }

        /*
         * Skip past any white space preceeding the second token.
         */
        while (*lpszCommandLine && (*lpszCommandLine <= SPACECHAR)) {
            lpszCommandLine++;
        }

#ifdef WPRFLAG
        mainret = wWinMain(
#else  /* WPRFLAG */
        mainret = WinMain(
#endif  /* WPRFLAG */
                      (HINSTANCE)&__ImageBase,
                      NULL,
                      lpszCommandLine,
                      StartupInfo.dwFlags & STARTF_USESHOWWINDOW
                      ? StartupInfo.wShowWindow
                      : SW_SHOWDEFAULT
                  );
#else  /* _WINMAIN_ */
#ifdef WPRFLAG
        __winitenv = envp;
        mainret = wmain(argc, argv, envp);
#else  /* WPRFLAG */
        __initenv = envp;
        mainret = main(argc, argv, envp);
#endif  /* WPRFLAG */
#endif  /* _WINMAIN_ */

        /*
         * Note that if the exe is managed app, we don't really need to
         * call exit or _c_exit. .cctor should be able to take care of
         * this.
         */
        if (!managedapp)
            exit(mainret);
        if (has_cctor == 0)
            _cexit();
    } __except (_XcptFilter(GetExceptionCode(), GetExceptionInformation())) {
        /*
         * Should never reach here
         */
        mainret = GetExceptionCode();

        /*
         * Note that if the exe is managed app, we don't really need to
         * call exit or _c_exit. .cctor should be able to take care of
         * this.
         */
        if (!managedapp) {
            _exit(mainret);
        }

        if (has_cctor == 0) {
            _cexit();
        }
    } /* end of try - except */

    return mainret;
}