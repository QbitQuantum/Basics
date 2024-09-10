BOOL CCollectingProperty::LoadScript( LPCTSTR szFile )
{
	CScript s;
	if( s.Load( szFile ) == FALSE )
		return FALSE;

	s.GetToken();	// subject or FINISHED
	while( s.tok != FINISHED )
	{
		if( s.Token == _T( "Cool" ) )
		{
			// ÃÊ
			s.GetToken();	// {
			int nCool	= s.GetNumber();
			while( *s.token != '}' )
			{
				m_anCool.push_back( nCool );
				nCool	= s.GetNumber();
			}
		}
		else if( s.Token == _T( "Enchant" ) )
		{
			// 1 / 1000
			s.GetToken();	// {
			int nProb	= s.GetNumber();
			while( *s.token != '}' )
			{
				m_anEnchant.push_back( nProb );
				nProb	= s.GetNumber();
			}
		}
		else if( s.Token == _T( "nMaxBattery" ) )
		{
			s.GetToken();	// =
			m_nMaxBattery	= s.GetNumber();
		}
		else if( s.Token == _T( "Item" ) )
		{
			COLLECTING_ITEM item;
			DWORD dwTotal	= 0;
			s.GetToken();	// {
			item.dwItemId	= s.GetNumber();
			while( *s.token != '}' )
			{
				dwTotal		+= s.GetNumber();
				item.dwProb	= dwTotal;
				m_aItem.push_back( item );
				item.dwItemId	= s.GetNumber();
			}
		}
		s.GetToken();
	}
/*
	TRACE( "cool\n" );
	for( int i = 0; i < m_anCool.size(); i++ )
	{
		TRACE( "%d\t%d\n", i, m_anCool[i] );
	}
	TRACE( "enchant\n" );
	for( i = 0; i < m_anEnchant.size(); i++ )
	{
		TRACE( "%d\t%d\n", i, m_anEnchant[i] );
	}
	TRACE( "max battery = %d\n", m_nMaxBattery );
*/
	return TRUE;
}