void test_wmemmove( void )
{
    wchar_t string1[60] = L"The quick brown dog jumps over the lazy fox";
    wchar_t string2[60] = L"The quick brown fox jumps over the lazy dog";

    wprintf( L"Wmemcpy without overlap\n" );
    wprintf( L"Source:\t\t%s\n", string1 + 40 );
    wprintf( L"Destination:\t%s\n", string1 + 16 );
    wmemcpy( string1 + 16, string1 + 40, 3 );
    wprintf( L"Result:\t\t%s\n", string1 );
    wprintf( L"Length:\t\t%d characters\n\n", wcslen( string1 ) );
    wmemcpy( string1 + 16, string2 + 40, 3 );

    wprintf( L"Wmemmove with overlap\n" );
    wprintf( L"Source:\t\t%s\n", string2 + 4 );
    wprintf( L"Destination:\t%s\n", string2 + 10 );
    wmemmove( string2 + 10, string2 + 4, 40 );
    wprintf( L"Result:\t\t%s\n", string2 );
    wprintf( L"Length:\t\t%d characters\n\n", wcslen( string2 ) );

    wprintf( L"Wmemcpy with overlap\n" );
    wprintf( L"Source:\t\t%s\n", string1 + 4 );
    wprintf( L"Destination:\t%s\n", string1 + 10 );
    wmemcpy( string1 + 10, string1 + 4, 40 );
    wprintf( L"Result:\t\t%s\n", string1 );
    wprintf( L"Length:\t\t%d characters\n\n", wcslen( string1 ) );
}