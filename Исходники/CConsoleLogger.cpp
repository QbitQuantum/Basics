//
// Replace next word in string with something
//
int CConsoleLogger::ReplaceNextWord( SString& strLine, int iPos, const char* szBlankText )
{
    int iStart = strLine.find_first_not_of( "': ", iPos );
    if ( iStart != std::string::npos )
    {
        int iEnd = strLine.find_first_of( "' ", iStart );
        if ( iEnd == std::string::npos )
            iEnd = strLine.length();
        strLine = strLine.SubStr( 0, iStart ) + szBlankText + strLine.SubStr( iEnd );
        iPos = iStart + strlen( szBlankText );
    }
    return iPos;
}