/**
 * Function XmlEsc
 * translates '<' to "&lt;", '>' to "&gt;" and so on, according to the spec:
 * http://www.w3.org/TR/2000/WD-xml-c14n-20000119.html#charescaping
 * May be moved to a library if needed generally, but not expecting that.
 */
static wxString XmlEsc( const wxString& aStr, bool isAttribute = false )
{
    wxString    escaped;

    escaped.reserve( aStr.length() );

    for( wxString::const_iterator it = aStr.begin();  it != aStr.end();  ++it )
    {
        const wxChar c = *it;

        switch( c )
        {
        case wxS( '<' ):
            escaped.append( wxS( "&lt;" ) );
            break;
        case wxS( '>' ):
            escaped.append( wxS( "&gt;" ) );
            break;
        case wxS( '&' ):
            escaped.append( wxS( "&amp;" ) );
            break;
        case wxS( '\r' ):
            escaped.append( wxS( "&#xD;" ) );
            break;
        default:
            if( isAttribute )
            {
                switch( c )
                {
                case wxS( '"' ):
                    escaped.append( wxS( "&quot;" ) );
                    break;
                case wxS( '\t' ):
                    escaped.append( wxS( "&#x9;" ) );
                    break;
                case wxS( '\n' ):
                    escaped.append( wxS( "&#xA;" ));
                    break;
                default:
                    escaped.append(c);
                }
            }
            else
                escaped.append(c);
        }
    }

    return escaped;
}