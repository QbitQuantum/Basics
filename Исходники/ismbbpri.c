_WCRTLINK int _ismbbprint( unsigned int ch )
{
    if( __MBCodePage == 932 ) {
        return( isprkana( ch ) );
    } else {
        return( _ismbcprint( ch & 0xFF ) );
    }
}