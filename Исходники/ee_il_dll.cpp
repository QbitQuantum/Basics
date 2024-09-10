    DLLEXPORT // For Win32 PAL LoadLibrary emulation
#endif
    BOOL WINAPI
    DllMain(HANDLE hInstance, DWORD dwReason, LPVOID pvReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        g_hInst = (HINSTANCE)hInstance;
        DisableThreadLibraryCalls((HINSTANCE)hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        // From MSDN: If fdwReason is DLL_PROCESS_DETACH, lpvReserved is NULL if FreeLibrary has
        // been called or the DLL load failed and non-NULL if the process is terminating.
        bool processIsTerminating = (pvReserved != nullptr);
        jitShutdown(processIsTerminating);
    }

    return TRUE;
}