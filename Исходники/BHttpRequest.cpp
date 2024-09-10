CBHttpRequest::CBHttpRequest(void) :
    m_hConnection(NULL),
    m_hFile(NULL),
    m_nReadyState(0),
    m_dwDataAvailable(0),
    m_uulTotalBytes(0),
    m_dwStatus(0),
    m_eventComplete(TRUE),
    m_dwReqID(0),
    m_dwFlags(INTERNET_FLAG_RELOAD | INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS)
{
    if(m_hSession == NULL)
    {
        DWORD dataSize;
        HKEY hKey;
        LONG result;

        dataSize = sizeof(strUserAgent);
        result = ::RegOpenKeyEx(HKEY_CURRENT_USER,
                                "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings",
                                0, KEY_QUERY_VALUE, &hKey);

        if(result == ERROR_SUCCESS)
        {
            result = ::RegQueryValueEx(hKey, "User Agent", NULL, NULL,(LPBYTE) strUserAgent, &dataSize);
            RegCloseKey(hKey);
        }

        m_hSession = InternetOpen(strUserAgent, PRE_CONFIG_INTERNET_ACCESS, NULL, NULL, INTERNET_FLAG_ASYNC);

        InternetSetStatusCallback(m_hSession, (INTERNET_STATUS_CALLBACK)&staticStatusCallback);
    }
}