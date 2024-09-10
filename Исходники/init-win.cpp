/**
 * Initializes the global variables related to windows version.
 */
static void rtR3InitWindowsVersion(void)
{
    Assert(g_hModNtDll != NULL);

    /*
     * ASSUMES OSVERSIONINFOEX starts with the exact same layout as OSVERSIONINFO (safe).
     */
    AssertCompileMembersSameSizeAndOffset(OSVERSIONINFOEX, szCSDVersion, OSVERSIONINFO, szCSDVersion);
    AssertCompileMemberOffset(OSVERSIONINFOEX, wServicePackMajor, sizeof(OSVERSIONINFO));

    /*
     * Use the NT version of GetVersionExW so we don't get fooled by
     * compatability shims.
     */
    RT_ZERO(g_WinOsInfoEx);
    g_WinOsInfoEx.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);

    LONG (__stdcall *pfnRtlGetVersion)(OSVERSIONINFOEXW *);
    *(FARPROC *)&pfnRtlGetVersion = GetProcAddress(g_hModNtDll, "RtlGetVersion");
    LONG rcNt = -1;
    if (pfnRtlGetVersion)
        rcNt = pfnRtlGetVersion(&g_WinOsInfoEx);
    if (rcNt != 0)
    {
        /*
         * Couldn't find it or it failed, try the windows version of the API.
         */
        RT_ZERO(g_WinOsInfoEx);
        g_WinOsInfoEx.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);
        if (!GetVersionExW((POSVERSIONINFOW)&g_WinOsInfoEx))
        {
            /*
             * If that didn't work either, just get the basic version bits.
             */
            RT_ZERO(g_WinOsInfoEx);
            g_WinOsInfoEx.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);
            if (GetVersionExW((POSVERSIONINFOW)&g_WinOsInfoEx))
                Assert(g_WinOsInfoEx.dwPlatformId != VER_PLATFORM_WIN32_NT || g_WinOsInfoEx.dwMajorVersion < 5);
            else
            {
                AssertBreakpoint();
                RT_ZERO(g_WinOsInfoEx);
            }
        }
    }

    if (g_WinOsInfoEx.dwOSVersionInfoSize)
        g_enmWinVer = rtR3InitWinSimplifiedVersion(&g_WinOsInfoEx);
}