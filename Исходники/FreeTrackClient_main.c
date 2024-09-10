BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    TRACE("(0x%p, %d, %p)\n", hinstDLL, fdwReason, lpvReserved);

    switch (fdwReason)
    {
        case DLL_WINE_PREATTACH:
            return TRUE;
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hinstDLL);
            dbg_flag = get_dbg_flag('w');
            dbg_report("Attach request\n");
            break;
        case DLL_PROCESS_DETACH:
            linuxtrack_shutdown();
            break;
    }

    return TRUE;
}