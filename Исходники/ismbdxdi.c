_WCRTLINK int _ismbdxdigit( unsigned int ch )
{
    unsigned int        han;

    if( _ismbclegal( ch ) ) {
        han = _mbdzentohan( ch );
        if( han & (~0xFF) ) {
            return( 0 );
        } else {
            return( isxdigit( han ) );
        }
    } else {
        return( isxdigit( ch ) );
    }
}