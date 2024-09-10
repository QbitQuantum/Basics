/*
 *  Dll Main function
 */
BOOL WINAPI DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    TRACE("%p,%x,%p\n", hinstDLL, fdwReason, lpvReserved);

    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hinstDLL);
            /* Try to load low-level library */
            if (load_functions() != 0)
		return FALSE;  /* error */
            break;
        case DLL_PROCESS_DETACH:
            if (lpvReserved) break;
            if (ctapi_handle) wine_dlclose(ctapi_handle, NULL, 0);
            break;
    }

    return TRUE;
}