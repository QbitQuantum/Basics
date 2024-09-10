UString SmtpParser::domain()
{
    UString r;
    if ( nextChar() == '[' ) {
        uint start = pos();
        while ( !atEnd() && nextChar() != ']' )
            step();
        require( "]" );
        AsciiCodec a;
        r = a.toUnicode( input().mid( start, pos() - start ) );
    }
    else {
        r = subDomain();
        while ( nextChar() == '.' ) {
            step();
            if ( nextChar() != '>' ) {
                r.append( "." );
                r.append( subDomain() );
            }
        }
    }
    return r;
}