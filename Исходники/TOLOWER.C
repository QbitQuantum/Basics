int _CType tolower( int ch )
{
    if( ch == -1 )  return( -1 );

    if( isupper( (unsigned char)ch) )
    {
        return( _tolower((unsigned char)ch) );
    }
    else
    {
        return( (unsigned char)ch );
    }
}