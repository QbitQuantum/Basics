// DllMain is needed to get the module handle for registration.
EXTERN_C BOOL WINAPI DllMain(_In_ HINSTANCE hInstance,
                             _In_ ULONG ulReason,
                             _In_opt_ LPVOID pvReserved)
{
    MI_UNREFERENCED_PARAMETER(pvReserved);

    if (DLL_PROCESS_ATTACH == ulReason)
    {
        DisableThreadLibraryCalls(hInstance);
        g_hModule = hInstance;
    }
    else if (DLL_PROCESS_DETACH == ulReason)
    {
        if(g_hHelper)
        {
            FreeLibrary(g_hHelper);
        }
    }
    return TRUE;
}