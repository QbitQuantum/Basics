bool WinRegKey::QueryInfo(LPDWORD lpcSubkeys)
{
#if defined(MEDIASDK_USE_REGISTRY) || (!defined(MEDIASDK_UWP_LOADER) && !defined(MEDIASDK_UWP_PROCTABLE))
    LONG lRes;

    lRes = RegQueryInfoKeyW(m_hKey, NULL, 0, 0, lpcSubkeys, 0, 0, 0, 0, 0, 0, 0);
    if (ERROR_SUCCESS != lRes) {
        TRACE_WINREG_ERROR("RegQueryInfoKeyW()==0x%x\n", lRes);
        return false;
    }
    return true;
#else
    return false;
#endif

} //bool QueryInfo(LPDWORD lpcSubkeys);