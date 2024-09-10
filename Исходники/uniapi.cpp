//--------------------------------------------------------------
BOOL WINAPI W_IsUnicodeSystem()
{
    static BOOL g_fWAPI = -2;
    if (-2 == g_fWAPI)
    {
        OSVERSIONINFOA osvi;
        osvi.dwOSVersionInfoSize = sizeof(osvi);
        GetVersionExA(&osvi);
        g_fWAPI = (VER_PLATFORM_WIN32_NT == osvi.dwPlatformId);
    }
    return g_fWAPI;
}