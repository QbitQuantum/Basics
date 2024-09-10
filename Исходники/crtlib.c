BOOL __cdecl
__CRTDLL_INIT(
        HANDLE  hDllHandle,
        DWORD   dwReason,
        LPVOID  lpreserved
        )
{
        BOOL term_all = FALSE;

        if ( dwReason == DLL_PROCESS_ATTACH ) {
            if ( !_heap_init() )    /* initialize heap */
                /*
                 * The heap cannot be initialized, return failure to the
                 * loader.
                 */
                return FALSE;

            if(!_mtinit())          /* initialize multi-thread */
            {
                /*
                 * If the DLL load is going to fail, we must clean up
                 * all resources that have already been allocated.
                 */
                _heap_term();       /* heap is now invalid! */

                return FALSE;       /* fail DLL load on failure */
            }

            if (_ioinit() < 0)
            {
                _mtterm();          /* free TLS index, call _mtdeletelocks() */
                _heap_term();       /* heap is now invalid! */
                return FALSE;       /* fail DLL load on failure */
            }

            _wcmdln = GetCommandLineW();

#if !defined(_CRT_APP) || defined(_KERNELX)
            _aenvptr = (char *)__crtGetEnvironmentStringsA();
            _acmdln = GetCommandLineA();
#else /* !defined(_CRT_APP) || defined(_KERNELX) */
            // We cannot call GetCommandLineA in the App CRT:
            if (!__copy_to_char(_wcmdln, &_acmdln))
            {
                _acmdln = NULL;
            }
#endif /* !defined(_CRT_APP) || defined(_KERNELX) */

#if !defined(_CRT_APP) || defined(_KERNELX)
#ifdef _MBCS
            /*
             * Initialize multibyte ctype table. Always done since it is
             * needed for processing the environment strings.
             */
            __initmbctable();
#endif  /* _MBCS */

            if (_setenvp() < 0 ||   /* get environ info */
                _cinit(FALSE) != 0)  /* do C data initialize */
            {
                term_all = TRUE;
            }
#else  /* !defined(_CRT_APP) || defined(_KERNELX) */
            if (_cinit(FALSE) != 0)  /* do C data initialize */
            {
                term_all = TRUE;
            }
#endif  /* !defined(_CRT_APP) || defined(_KERNELX) */

            if (term_all)
            {
#if defined(_CRT_APP) && !defined(_KERNELX)
                _free_crt(_acmdln);
                _acmdln = NULL;
#endif
                _ioterm();          /* shut down lowio */
                _mtterm();          /* free TLS index, call _mtdeletelocks() */
                _heap_term();       /* heap is now invalid! */
                return FALSE;       /* fail DLL load on failure */
            }

            /*
             * Increment flag indicating process attach notification
             * has been received.
             */
            proc_attached++;

        }
        else if ( dwReason == DLL_PROCESS_DETACH ) {
            /*
             * if a client process is detaching, make sure minimal
             * runtime termination is performed and clean up our
             * 'locks' (i.e., delete critical sections).
             */
            if ( proc_attached > 0 ) {
                proc_attached--;
                __try {

                    /*
                     * Any basic clean-up done here may also need
                     * to be done below if Process Attach is partly
                     * processed and then a failure is encountered.
                     */

                    if ( _C_Termination_Done == FALSE )
                        _cexit();

                    __crtdll_callstaticterminators();

                    /* Free all allocated CRT memory */
                    __freeCrtMemory();

#ifdef _DEBUG
                    /* Dump all memory leaks */
                    if (_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) & _CRTDBG_LEAK_CHECK_DF)
                    {
                        _CrtSetDumpClient(NULL);
                        _CrtDumpMemoryLeaks();
                    }
#endif  /* _DEBUG */

                    /*
                     * What remains is to clean up the system resources we have
                     * used (handles, critical sections, memory,...,etc.). This
                     * needs to be done if the whole process is NOT terminating.
                     */

                    /* If dwReason is DLL_PROCESS_DETACH, lpreserved is NULL
                     * if FreeLibrary has been called or the DLL load failed
                     * and non-NULL if the process is terminating.
                     */
                    if ( lpreserved == NULL )
                    {
#if defined(_CRT_APP) && !defined(_KERNELX)
                        _free_crt(_acmdln);
                        _acmdln = NULL;
#endif
                        /*
                         * The process is NOT terminating so we must clean up...
                         */
                        _ioterm();

                        /* free TLS index, call _mtdeletelocks() */
                        _mtterm();

                        /* This should be the last thing the C run-time does */
                        _heap_term();   /* heap is now invalid! */
                    }

                }
                __finally {
                    /* we shouldn't really have to care about this, because
                       letting an exception escape from DllMain(DLL_PROCESS_DETACH) should
                       result in process termination. Unfortunately, Windows up to Win7 as of now
                       just silently swallows the exception.

                       I have considered all kinds of tricks, but decided to leave it up to OS
                       folks to fix this.

                       For the time being just remove our FLS callback during phase 2 unwind
                       that would otherwise be left pointing to unmapped address space.
                       */
                     if ( lpreserved == NULL && __flsindex != FLS_OUT_OF_INDEXES )
                         _mtterm();
                }
            }
            else
                /* no prior process attach, just return */
                return FALSE;