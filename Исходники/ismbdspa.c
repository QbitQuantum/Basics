_WCRTLINK int _ismbdspace( unsigned int ch )
{
    if( _ismbclegal( ch ) ) {
        return( ch == 0x8140  ||  ch == ' ' );
    } else {
        return( isspace( ch ) );
    }
}