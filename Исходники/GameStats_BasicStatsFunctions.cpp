void BasicGameStats_t::SaveToBuffer( CUtlBuffer& buf )
{
	buf.PutInt( m_nSecondsToCompleteGame );

	m_Summary.SaveToBuffer( buf );

	int c = m_MapTotals.Count();
	buf.PutInt( c );
	for ( int i = m_MapTotals.First(); i != m_MapTotals.InvalidIndex(); i = m_MapTotals.Next( i ) )
	{
		char const *name = m_MapTotals.GetElementName( i );
		BasicGameStatsRecord_t &rec = m_MapTotals[ i ];

		buf.PutString( name );
		rec.SaveToBuffer( buf );
	}

	buf.PutChar( (char)m_nHL2ChaptureUnlocked );	
	buf.PutChar( m_bSteam ? 1 : 0 );
	buf.PutChar( m_bCyberCafe ? 1 : 0 );
	buf.PutShort( (short)m_nDXLevel );
}