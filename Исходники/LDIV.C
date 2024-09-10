int main( void )
{
    ldiv_t result;
    result = ldiv( 5, 2 );
    TESTCASE( result.quot == 2 && result.rem == 1 );
    result = ldiv( -5, 2 );
    TESTCASE( result.quot == -2 && result.rem == -1 );
    result = ldiv( 5, -2 );
    TESTCASE( result.quot == -2 && result.rem == 1 );
    TESTCASE( sizeof( result.quot ) == sizeof( long ) );
    TESTCASE( sizeof( result.rem )  == sizeof( long ) );
    return TEST_RESULTS;
}