static void test_SetupDiClassGuidsFromNameA(void)
{
    LPGUID guid_list = NULL;
    DWORD required_size, size;

    SetLastError( 0xdeadbeef );
    ok( !SetupDiClassGuidsFromNameA( NULL, NULL, 0, NULL ),
        "Fail expected\n" );
    ok_lasterr( ERROR_INVALID_PARAMETER );

    SetLastError( 0xdeadbeef );
    ok( !SetupDiClassGuidsFromNameA( NULL, NULL, 0, &required_size ),
        "Fail expected\n" );
    ok_lasterr( ERROR_INVALID_PARAMETER );

    SetLastError( 0xdeadbeef );
    ok( SetupDiClassGuidsFromNameA( "", NULL, 0, &required_size ),
        "Error reported %lx\n", GetLastError() );
    ok( required_size == 0, "Expected 0, got %lu\n", required_size );

    SetLastError( 0xdeadbeef );
    ok( !SetupDiClassGuidsFromNameA( test_class_name, NULL, 0, &required_size ),
        "Fail expected\n" );
    ok_lasterr( ERROR_INSUFFICIENT_BUFFER );
    ok( required_size > 0, "Expected > 0, got %lu\n", required_size );

    guid_list = HeapAlloc( GetProcessHeap(), 0, ( required_size + 1 ) * sizeof( GUID ) );
    if ( !guid_list )
        return;

    SetLastError( 0xdeadbeef );
    ok( SetupDiClassGuidsFromNameA( test_class_name, guid_list, required_size, &size ),
        "Error reported %lx\n", GetLastError() );
    ok( size == required_size, "Expected size %lu, got %lu\n", required_size, size );
    ok( IsEqualIID( &guid_list[0], &test_class_guid ),
        "Expected %s, got %s\n", debugstr_guid( &test_class_guid ), debugstr_guid( &guid_list[0] ) );
    SetLastError( 0xdeadbeef );
    ok( SetupDiClassGuidsFromNameA( test_class_name, guid_list, required_size + 1, &size ),
        "Error reported %lx\n", GetLastError() );
    ok( size == required_size, "Expected size %lu, got %lu\n", required_size, size );
    ok( IsEqualIID( &guid_list[0], &test_class_guid ),
        "Expected %s, got %s\n", debugstr_guid( &test_class_guid ), debugstr_guid( &guid_list[0] ) );

    HeapFree( GetProcessHeap(), 0, guid_list );
}