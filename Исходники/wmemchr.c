int main( void )
{
    TESTCASE( wmemchr( wabcde, L'c', 5 ) == &wabcde[2] );
    TESTCASE( wmemchr( wabcde, L'a', 1 ) == &wabcde[0] );
    TESTCASE( wmemchr( wabcde, L'a', 0 ) == NULL );
    TESTCASE( wmemchr( wabcde, L'\0', 5 ) == NULL );
    TESTCASE( wmemchr( wabcde, L'\0', 6 ) == &wabcde[5] );
    return TEST_RESULTS;
}