void TestFromWide( void )
{
    char                mbs[20];
    wchar_t             wc = L'\0';
    wchar_t             wcs[] = { 'H', 'e', 'l', 'l', 'o', '\0' };

    errno_t             rc;
    size_t              retval;
    size_t              retval2;
    int                 status;
    int                 violations = NumViolations;

    rc = wctomb_s( &status, mbs, 20, wc );
    VERIFY( rc == 0 );
    VERIFY( mbs[0] == '\0' );
    VERIFY( status == 1 );
    VERIFY( violations == NumViolations );

    rc = wctomb_s( &status, mbs, 20, L'X' );
    VERIFY( rc == 0 );
    VERIFY( mbs[0] == 'X' );
    VERIFY( status == 1 );
    VERIFY( violations == NumViolations );

    rc = wctomb_s( &status, NULL, 0, L'X' );
    VERIFY( rc == 0 );
    VERIFY( status == 0 );  /* no state-dependant encodings */
    VERIFY( violations == NumViolations );


    rc = wcstombs_s( &retval, mbs, 20, wcs, 10 );
    VERIFY( rc == 0 );
    VERIFY( retval == 5 );
    VERIFY( !_mbscmp(mbs,"Hello") );
    VERIFY( violations == NumViolations );

    rc = wcstombs_s( &retval2, NULL, 0, wcs, 10 );
    VERIFY( rc == 0 );
    VERIFY( retval2 == 5 );
    VERIFY( violations == NumViolations );


    /***********************************************************************/
    /*  test runtime-constraints                                           */
    /***********************************************************************/
    rc = wctomb_s( &status, NULL, 20, wc );
    VERIFY( rc != 0 );
    VERIFY( ++violations == NumViolations );

    rc = wctomb_s( &status, mbs, 0, wc );
    VERIFY( rc != 0 );
    VERIFY( ++violations == NumViolations );

#if RSIZE_MAX != SIZE_MAX
    rc = wctomb_s( &status, mbs, ~0, wc );
    VERIFY( rc != 0 );
    VERIFY( ++violations == NumViolations );
#endif

    rc = wctomb_s( &status, mbs, 1, '\x81\xFC' );
    VERIFY( rc != 0 );
    VERIFY( ++violations == NumViolations );


    mbs[0]= 'X';
    rc = wcstombs_s( NULL, mbs, 20, wcs, 10 );
    VERIFY( rc != 0 );
    VERIFY( mbs[0] == '\0' );
    VERIFY( ++violations == NumViolations );

    mbs[0]= 'X';
    rc = wcstombs_s( &retval, mbs, 20, NULL, 10 );
    VERIFY( rc != 0 );
    VERIFY( retval == -1 );
    VERIFY( mbs[0] == '\0' );
    VERIFY( ++violations == NumViolations );

#if RSIZE_MAX != SIZE_MAX
    mbs[0]= 'X';
    rc = wcstombs_s( &retval, mbs, ~0, wcs, 10 );
    VERIFY( rc != 0 );
    VERIFY( retval == -1 );
    VERIFY( mbs[0] == 'X' );
    VERIFY( ++violations == NumViolations );

    mbs[0]= 'X';
    rc = wcstombs_s( &retval, mbs, 20, wcs, ~0 );
    VERIFY( rc != 0 );
    VERIFY( retval == -1 );
    VERIFY( mbs[0] == '\0' );
    VERIFY( ++violations == NumViolations );
#endif



}