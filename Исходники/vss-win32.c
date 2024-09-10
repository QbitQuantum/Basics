/* Check whether this OS version supports VSS providers */
static bool vss_check_os_version(void)
{
    OSVERSIONINFO OSver;

    OSver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&OSver);
    if ((OSver.dwMajorVersion == 5 && OSver.dwMinorVersion >= 2) ||
       OSver.dwMajorVersion > 5) {
        BOOL wow64 = false;
#ifndef _WIN64
        /* Provider doesn't work under WOW64 (32bit agent on 64bit OS) */
        if (!IsWow64Process(GetCurrentProcess(), &wow64)) {
            fprintf(stderr, "failed to IsWow64Process (Error: %lx\n)\n",
                    GetLastError());
            return false;
        }
        if (wow64) {
            fprintf(stderr, "Warning: Running under WOW64\n");
        }
#endif
        return !wow64;
    }
    return false;
}