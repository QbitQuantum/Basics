UString SieveParser::multiLine()
{
    EString r;
    require( "text:" );
    while ( ok() && ( nextChar() == ' ' || nextChar() == '\t' ) )
        step();
    if ( !present( "\r\n" ) )
        hashComment();
    while ( ok() && !atEnd() && !present( ".\r\n" ) ) {
        if ( nextChar() == '.' )
            step();
        while ( ok() && !atEnd() && nextChar() != '\r' ) {
            r.append( nextChar() );
            step();
        }
        require( "\r\n" );
        r.append( "\r\n" );
    }
    Utf8Codec c;
    UString u = c.toUnicode( r );
    if ( !c.valid() )
        setError( "Encoding error: " + c.error() );
    return u;
}