//-----------------------------------------------------------------------------
// Parses a token from the excel .csv file
//-----------------------------------------------------------------------------
CSFMGenApp::TokenRetVal_t CSFMGenApp::ParseToken( CUtlBuffer &buf, char *pToken, int nMaxTokenLen )
{
	*pToken = 0;

	if ( !buf.IsValid() )
		return TOKEN_EOF;

	int nLen = 0;
	char c = buf.GetChar();
	bool bIsQuoted = false;
	while ( true )
	{
		if ( c == '"' )
		{
			bIsQuoted = !bIsQuoted;
		}
		else if ( ( c == ',' || c == '\n' ) && !bIsQuoted )
		{
			pToken[nLen] = 0;
			return ( c == '\n' ) ? TOKEN_RETURN : TOKEN_COMMA;
		}

		if ( nLen < nMaxTokenLen - 1 )
		{
			if ( c != '"' )
			{
				pToken[nLen++] = c;
			}
		}
		if ( !buf.IsValid() ) 
		{
			pToken[nLen] = 0;
			return TOKEN_EOF;
		}
		c = buf.GetChar();
	}

	// Should never get here
	return TOKEN_EOF;
}