_WCRTLINK int _ismbdalpha( unsigned int ch )
{
    if( _ismbclegal( ch ) ) {
        return( (ch>=0x8260 && ch<=0x8279)  ||  (ch>=0x8281 && ch<=0x829A) );
    } else {
        return( isalpha( ch ) );
    }
}