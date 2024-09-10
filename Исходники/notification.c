static void test_async( void )
{
    HANDLE ses, con, req;
    DWORD size, status;
    BOOL ret;
    struct info info, *context = &info;
    char buffer[1024];

    info.test  = async_test;
    info.count = sizeof(async_test) / sizeof(async_test[0]);
    info.index = 0;
    info.wait = CreateEventW( NULL, FALSE, FALSE, NULL );

    ses = WinHttpOpen( user_agent, 0, NULL, NULL, WINHTTP_FLAG_ASYNC );
    ok(ses != NULL, "failed to open session %u\n", GetLastError());

    WinHttpSetStatusCallback( ses, check_notification, WINHTTP_CALLBACK_FLAG_ALL_NOTIFICATIONS, 0 );

    ret = WinHttpSetOption( ses, WINHTTP_OPTION_CONTEXT_VALUE, &context, sizeof(struct info *) );
    ok(ret, "failed to set context value %u\n", GetLastError());

    setup_test( &info, winhttp_connect, __LINE__ );
    con = WinHttpConnect( ses, test_winehq, 0, 0 );
    ok(con != NULL, "failed to open a connection %u\n", GetLastError());

    setup_test( &info, winhttp_open_request, __LINE__ );
    req = WinHttpOpenRequest( con, NULL, NULL, NULL, NULL, NULL, 0 );
    ok(req != NULL, "failed to open a request %u\n", GetLastError());

    setup_test( &info, winhttp_send_request, __LINE__ );
    ret = WinHttpSendRequest( req, NULL, 0, NULL, 0, 0, 0 );
    ok(ret, "failed to send request %u\n", GetLastError());

    WaitForSingleObject( info.wait, INFINITE );

    setup_test( &info, winhttp_receive_response, __LINE__ );
    ret = WinHttpReceiveResponse( req, NULL );
    ok(ret, "failed to receive response %u\n", GetLastError());

    WaitForSingleObject( info.wait, INFINITE );

    size = sizeof(status);
    ret = WinHttpQueryHeaders( req, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, NULL, &status, &size, NULL );
    ok(ret, "failed unexpectedly %u\n", GetLastError());
    ok(status == 200, "request failed unexpectedly %u\n", status);

    setup_test( &info, winhttp_query_data, __LINE__ );
    ret = WinHttpQueryDataAvailable( req, NULL );
    ok(ret, "failed to query data available %u\n", GetLastError());

    WaitForSingleObject( info.wait, INFINITE );

    setup_test( &info, winhttp_read_data, __LINE__ );
    ret = WinHttpReadData( req, buffer, sizeof(buffer), NULL );
    ok(ret, "failed to query data available %u\n", GetLastError());

    WaitForSingleObject( info.wait, INFINITE );

    setup_test( &info, winhttp_close_handle, __LINE__ );
    WinHttpCloseHandle( req );
    WinHttpCloseHandle( con );
    WinHttpCloseHandle( ses );

    WaitForSingleObject( info.wait, INFINITE );
    CloseHandle( info.wait );
}