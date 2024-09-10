extern "C" BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReserved)
{
    if(fdwReason == DLL_PROCESS_ATTACH)
        DisableThreadLibraryCalls(hinstDll);

    if(fdwReason == DLL_PROCESS_DETACH && lpvReserved == NULL)
        u_cleanup();

    return TRUE;
}