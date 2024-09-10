/*----------------------------------------------------------------------
|       NPT_HttpProxySelector::GetSystemDefault
+---------------------------------------------------------------------*/
NPT_HttpProxySelector*
NPT_HttpProxySelector::GetSystemDefault()
{
    NPT_AutoLock lock(NPT_Win32HttpLock);

    if (NPT_Win32HttpHandle == INVALID_HANDLE_VALUE) {
        WINHTTP_CURRENT_USER_IE_PROXY_CONFIG config;
        BOOL result = WinHttpGetIEProxyConfigForCurrentUser(&config);
    }

    return NULL;
}