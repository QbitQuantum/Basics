char CISpellAffix::ToLowerCase ( char cChar )
{
	if ( m_bFirstCaseConv )
	{
		LoadLocale ();
		m_bFirstCaseConv = false;
	}

	// dictionary conversion
	if ( m_bUseDictConversion )
		return m_dCharset [(BYTE) cChar] ? m_dCharset [(BYTE) cChar] : cChar;

	// user-defined character mapping
	if ( m_bUseLowerCaser )
	{
		char cResult = (char)m_LowerCaser.ToLower ( (BYTE) cChar );
		return cResult ? cResult : cChar;
	}

	// user-specified code page conversion
	return (char)tolower ( (BYTE)cChar ); // workaround for systems (eg. FreeBSD) which default to signed char. marvelous!
}