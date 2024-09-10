static void do_startup( void )
{
#else
static BOOL WINAPI _RawDllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved )
{
    (void)hinstDLL; /* avoid warnings */
    (void)lpvReserved; /* avoid warnings */

    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            {
#endif

#if OSL_DEBUG_LEVEL < 2
                /* Suppress file error messages from system like "Floppy A: not inserted" */
                SetErrorMode( SEM_NOOPENFILEERRORBOX | SEM_FAILCRITICALERRORS );
#endif

                /* initialize global mutex */
                g_Mutex = osl_createMutex();

                /* initialize "current directory" mutex */
                g_CurrentDirectoryMutex = osl_createMutex();

                g_dwTLSTextEncodingIndex = TlsAlloc();
                InitializeCriticalSection( &g_ThreadKeyListCS );

                //We disable floating point exceptions. This is the usual state at program startup
                //but on Windows 98 and ME this is not always the case.
                _control87(_MCW_EM, _MCW_EM);
#ifdef __MINGW32__
        atexit(do_cleanup);
}

void do_cleanup( void )
{
#else
                break;
            }

        case DLL_PROCESS_DETACH:
#endif

            WSACleanup( );

            TlsFree( g_dwTLSTextEncodingIndex );
            DeleteCriticalSection( &g_ThreadKeyListCS );

            osl_destroyMutex( g_Mutex );

            osl_destroyMutex( g_CurrentDirectoryMutex );

#ifndef __MINGW32__

            /*

            On a product build memory management finalization might
            cause a crash without assertion (assertions off) if heap is
            corrupted. But a crash report won't help here because at
            this point all other threads have been terminated and only
            ntdll is on the stack. No chance to find the reason for the
            corrupted heap if so.

            So annoying the user with a crash report is completely useless.

            */

#ifndef DBG_UTIL
            __try
#endif
            {
                /* cleanup locale hashtable */
                rtl_locale_fini();

                /* finalize memory management */
                rtl_memory_fini();
                rtl_cache_fini();
                rtl_arena_fini();
            }
#ifndef DBG_UTIL
            __except( EXCEPTION_EXECUTE_HANDLER )
            {
            }
#endif
            break;
    }

    return TRUE;
#endif
}