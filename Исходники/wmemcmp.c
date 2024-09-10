int main( void )
{
    wchar_t const xxxxx[] = L"xxxxx";
    TESTCASE( wmemcmp( wabcde, wabcdx, 5 ) < 0 );
    TESTCASE( wmemcmp( wabcde, wabcdx, 4 ) == 0 );
    TESTCASE( wmemcmp( wabcde, xxxxx,  0 ) == 0 );
    TESTCASE( wmemcmp( xxxxx,  wabcde, 1 ) > 0 );
    return 0;
}