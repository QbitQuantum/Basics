static void test_DsClientMakeSpnForTargetServer(void)
{
    static const WCHAR classW[] = {'c','l','a','s','s',0};
    static const WCHAR hostW[] = {'h','o','s','t','.','d','o','m','a','i','n',0};
    static const WCHAR resultW[] = {'c','l','a','s','s','/','h','o','s','t','.','d','o','m','a','i','n',0};
    DWORD ret, len;
    WCHAR buf[256];

    ret = DsClientMakeSpnForTargetServerW( NULL, NULL, NULL, NULL );
    ok( ret == ERROR_INVALID_PARAMETER, "got %u\n", ret );

    ret = DsClientMakeSpnForTargetServerW( classW, NULL, NULL, NULL );
    ok( ret == ERROR_INVALID_PARAMETER, "got %u\n", ret );

    ret = DsClientMakeSpnForTargetServerW( classW, hostW, NULL, NULL );
    ok( ret == ERROR_INVALID_PARAMETER, "got %u\n", ret );

    len = 0;
    ret = DsClientMakeSpnForTargetServerW( classW, hostW, &len, NULL );
    ok( ret == ERROR_BUFFER_OVERFLOW, "got %u\n", ret );
    ok( len == lstrlenW(resultW) + 1, "got %u\n", len );

    len = sizeof(buf)/sizeof(buf[0]);
    buf[0] = 0;
    ret = DsClientMakeSpnForTargetServerW( classW, hostW, &len, buf );
    ok( ret == ERROR_SUCCESS, "got %u\n", ret );
    ok( len == lstrlenW(resultW) + 1, "got %u\n", len );
    ok( !lstrcmpW( buf, resultW ), "wrong data\n" );
}