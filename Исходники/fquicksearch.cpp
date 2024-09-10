StringSearch_c::StringSearch_c ( const wchar_t * szPattern, bool bMatchCase, bool bWholeWord )
	: m_iPatLen 	( wcslen ( szPattern ) )
	, m_iMin		( szPattern [0] )
	, m_pFile		( NULL )
	, m_bEndReached	( false )
	, m_bMatchCase	( bMatchCase )
	, m_bWholeWord	( bWholeWord )
	, m_iNextOffset	( 0 )
{
	Assert ( ! ( READ_BUFFER_SIZE & 1 ) );
	Assert ( m_iPatLen < READ_BUFFER_SIZE );
	m_iMax = m_iMin;

	const wchar_t * szStart = szPattern;
	while ( *szStart )
	{
		if ( *szStart > m_iMax )
			m_iMax = *szStart;
		else 
			if ( *szStart < m_iMin )
				m_iMin = *szStart;

		++szStart;
	}

	int iSize = m_iMax - m_iMin + 1;
	m_dBadChar = new unsigned short [iSize];
	wmemset ( (wchar_t*)m_dBadChar, m_iPatLen + 1, iSize );

	m_szPattern = new wchar_t [ wcslen ( szPattern ) + 1 ];
	wcscpy ( m_szPattern, szPattern );
	
	if ( ! m_bMatchCase )
		for ( int i = 0; i < m_iPatLen; ++i )
			m_szPattern [i] = towlower ( m_szPattern [i] );

	for ( int i = 0; i < m_iPatLen; ++i )
		m_dBadChar [ szPattern [i] - m_iMin ] = m_iPatLen - i;
}