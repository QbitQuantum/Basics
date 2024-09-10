const UString operator+( const UString & a, const char * b )
{
    UString result;
    uint l = a.length();
    if ( b )
        l += strlen( b );
    result.reserve( l );
    result.append( a );
    result.append( b );
    return result;
}