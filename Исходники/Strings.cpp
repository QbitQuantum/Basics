double stringToNumber( wstring& text )
{
    wstring::size_type endptr;
    double number = std::stod( text, &endptr );
    // the conversion is successful only when no text remains after the number
    if( endptr != text.length() )
    {
        throw new std::invalid_argument( "stringToNumber called on a text that contains characters after the number" );
    }
    return( number );
}