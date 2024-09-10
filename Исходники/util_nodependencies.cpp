//------------------------------------------------------------------------------
// Returns TRUE if we are running on a 64-bit OS in WoW, FALSE otherwise.
BOOL RunningInWow64()
{
#ifdef PLATFORM_UNIX
    return FALSE;
#else
    static int s_Wow64Process;

    if (s_Wow64Process == 0)
    {
        BOOL fWow64Process = FALSE;

        if (!IsWow64Process(GetCurrentProcess(), &fWow64Process))
            fWow64Process = FALSE;

        s_Wow64Process = fWow64Process ? 1 : -1;
    }

    return (s_Wow64Process == 1) ? TRUE : FALSE;
#endif
}