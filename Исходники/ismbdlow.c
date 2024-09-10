_WCRTLINK int _ismbdlower( unsigned int ch )
{
    if( _ismbclegal( ch ) ) {
        return( ch >= 0x8281  &&  ch <= 0x829A );
    } else {
        return( islower( ch ) );
    }
}