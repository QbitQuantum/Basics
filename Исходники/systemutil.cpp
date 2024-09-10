BOOL SetConnectionProxy( char * proxyAdressStr , char * connNameStr = NULL)
{
    INTERNET_PER_CONN_OPTION_LIST conn_options;
    BOOL    bReturn;
    DWORD   dwBufferSize = sizeof(conn_options);
    conn_options.dwSize = dwBufferSize;
    conn_options.pszConnection = (TCHAR*)connNameStr;//NULL == LAN

    conn_options.dwOptionCount = 3;
    conn_options.pOptions = new INTERNET_PER_CONN_OPTION[3];

    if(!conn_options.pOptions)
        return FALSE;

    conn_options.pOptions[0].dwOption = INTERNET_PER_CONN_FLAGS;
    conn_options.pOptions[0].Value.dwValue = PROXY_TYPE_DIRECT|PROXY_TYPE_PROXY;

    conn_options.pOptions[1].dwOption = INTERNET_PER_CONN_PROXY_SERVER;
    conn_options.pOptions[1].Value.pszValue = (TCHAR*)proxyAdressStr;
    conn_options.pOptions[2].dwOption = INTERNET_PER_CONN_PROXY_BYPASS;
    conn_options.pOptions[2].Value.pszValue = (TCHAR*)"<local>";

    bReturn = InternetSetOptionA(NULL,INTERNET_OPTION_PER_CONNECTION_OPTION, &conn_options, dwBufferSize);

    delete [] conn_options.pOptions;

    InternetSetOptionA(NULL, INTERNET_OPTION_SETTINGS_CHANGED, NULL, 0);
    InternetSetOption(NULL, INTERNET_OPTION_REFRESH , NULL, 0);
    return bReturn;
}