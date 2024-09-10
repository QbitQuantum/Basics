static void
hookAllModules(void)
{
    HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
    if (hModuleSnap == INVALID_HANDLE_VALUE) {
        return;
    }

    MODULEENTRY32 me32;
    me32.dwSize = sizeof me32;

    if (VERBOSITY > 0) {
        static bool first = true;
        if (first) {
            if (Module32First(hModuleSnap, &me32)) {
                debugPrintf("  modules:\n");
                do  {
                    debugPrintf("     %s\n", me32.szExePath);
                } while (Module32Next(hModuleSnap, &me32));
            }
            first = false;
        }
    }

    if (Module32First(hModuleSnap, &me32)) {
        do  {
            hookModule(me32.hModule, me32.szExePath);
        } while (Module32Next(hModuleSnap, &me32));
    }

    CloseHandle(hModuleSnap);
}