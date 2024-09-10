BOOL
WINAPI
DllMain(PVOID hinstDll, ULONG dwReason, PVOID reserved)
{
    OSVERSIONINFOW osvi;
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        /* initialize version info */
        TRACE("Process Attach\n");
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);
        GetVersionExW( &osvi );
        _winver     = (osvi.dwMajorVersion << 8) | osvi.dwMinorVersion;
        _winmajor   = osvi.dwMajorVersion;
        _winminor   = osvi.dwMinorVersion;
        _osplatform = osvi.dwPlatformId;
        _osver      = osvi.dwBuildNumber;

        /* create tls stuff */
        if (!msvcrt_init_tls())
          return FALSE;

        if (BlockEnvToEnvironA() < 0)
            return FALSE;

        if (BlockEnvToEnvironW() < 0)
        {
            FreeEnvironment(_environ);
            return FALSE;
        }

        _acmdln = _strdup(GetCommandLineA());
        _wcmdln = _wcsdup(GetCommandLineW());

        /* Initialization of the WINE code */
        msvcrt_init_mt_locks();
        //msvcrt_init_math();
        msvcrt_init_io();
        //msvcrt_init_console();
        //msvcrt_init_args();
        //msvcrt_init_signals();
        TRACE("Attach done\n");
        break;

    case DLL_THREAD_ATTACH:
        //msvcrt_get_thread_data creates data when first called
        break;

    case DLL_THREAD_DETACH:
        msvcrt_free_tls_mem();
        break;

    case DLL_PROCESS_DETACH:
        TRACE("Detach\n");
        /* Deinit of the WINE code */
        msvcrt_free_io();
        if (reserved) break;
        msvcrt_free_mt_locks();
        //msvcrt_free_console();
        //msvcrt_free_args();
        //msvcrt_free_signals();
        msvcrt_free_tls_mem();
        if (!msvcrt_free_tls())
          return FALSE;
        if(global_locale)
          MSVCRT__free_locale(global_locale);

        if (__winitenv && __winitenv != _wenviron)
            FreeEnvironment((char**)__winitenv);
        if (_wenviron)
            FreeEnvironment((char**)_wenviron);

        if (__initenv && __initenv != _environ)
            FreeEnvironment(__initenv);
        if (_environ)
            FreeEnvironment(_environ);

        TRACE("Detach done\n");
        break;
    }

    return TRUE;
}