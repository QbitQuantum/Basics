DWORD WINAPI SendProc(LPVOID data) {
    DWORD dataSize = 0;
    DWORD bytesDownloaded = 0;
    LPSTR outBuffer;
    BOOL  result = FALSE;
    HINTERNET session = NULL,connection = NULL,request = NULL;

    std::wstring *wurl = (std::wstring*)data;
    if( wurl == NULL ) {
        return result;
    }
    session = WinHttpOpen(GA_HOST.c_str(),
                          WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                          WINHTTP_NO_PROXY_NAME,
                          WINHTTP_NO_PROXY_BYPASS, 0 );

    if( session )
        connection = WinHttpConnect( session, GA_HOST.c_str(),
                                     INTERNET_DEFAULT_HTTP_PORT, 0 );

    if( connection )
        request = WinHttpOpenRequest( connection, L"GET", wurl->c_str(),
                                      NULL, WINHTTP_NO_REFERER,
                                      WINHTTP_DEFAULT_ACCEPT_TYPES,
                                      0 );

    if( request )
        result = WinHttpSendRequest( request,
                                     WINHTTP_NO_ADDITIONAL_HEADERS, 0,
                                     WINHTTP_NO_REQUEST_DATA, 0,
                                     0, 0 );
    //DWORD n = GetLastError();
    if( result )
        result = WinHttpReceiveResponse( request, NULL );

    if( result ) {
        do {
            dataSize = 0;
            if( !WinHttpQueryDataAvailable( request, &dataSize ) )
                return FALSE;

            outBuffer = new char[dataSize+1];
            if( !outBuffer ) {
                return false;
            } else {
                ZeroMemory( outBuffer, dataSize+1 );
                if( !WinHttpReadData( request, (LPVOID)outBuffer, dataSize, &bytesDownloaded ) ) {
                    delete []outBuffer;
                    return false;
                }
                // TODO: if you care about the response, please handle it here...
                //
                delete[] outBuffer;
            }
        } while( dataSize > 0 );
    }
    // clean up
    if( request ) WinHttpCloseHandle( request );
    if( connection ) WinHttpCloseHandle( connection );
    if( session ) WinHttpCloseHandle( session );

    delete wurl;
    return result;

}