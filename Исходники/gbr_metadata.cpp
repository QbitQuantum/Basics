std::string formatStringToGerber( const wxString& aString )
{
    /* format string means convert any code > 0x7F and unautorized code to a hexadecimal
     * 16 bits sequence unicode
     * unautorized codes are ',' '*' '%' '\'
     */
    std::string txt;

    txt.reserve( aString.Length() );

    for( unsigned ii = 0; ii < aString.Length(); ++ii )
    {
        unsigned code = aString[ii];
        bool convert = false;

        switch( code )
        {
        case '\\':
        case '%':
        case '*':
        case ',':
            convert = true;
            break;

        default:
            break;
        }

        if( convert || code > 0x7F )
        {
            txt += '\\';

            // Convert code to 4 hexadecimal digit
            // (Gerber allows only 4 hexadecimal digit)
            char hexa[32];
            sprintf( hexa,"%4.4X", code & 0xFFFF);
            txt += hexa;
        }
        else
            txt += char( code );
    }

    return txt;
}