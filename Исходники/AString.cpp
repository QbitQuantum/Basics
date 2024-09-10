// Replace ( char *, char * )
//------------------------------------------------------------------------------
uint32_t AString::Replace( const char * from, const char * to, uint32_t maxReplaces )
{
	AStackString< 2 * KILOBYTE > temp;

	uint32_t replaceCount = 0;

	// loop until the last possible position for a potential match
	const char * pos = m_Contents;
	const char * end = m_Contents + m_Length;
	const size_t fromLength = StrLen( from );
	while ( pos <= ( end - fromLength ) )
	{
		if ( StrNCmp( pos, from, fromLength ) == 0 )
		{
			temp += to;
			pos += fromLength;
			maxReplaces--;
			replaceCount++;
			if ( maxReplaces == 0 )
			{
				break;
			}
		}
		else
		{
			temp += *pos;
			pos++;
		}
	}

	// did we actually replace anything?
	if ( replaceCount > 0 )
	{
		// copy remaining unmatchable characters to the temp
		while ( pos < end )
		{
			temp += *pos;
			pos++;
		}

		// keep the result
		Assign( temp );
	}
	return replaceCount;
}