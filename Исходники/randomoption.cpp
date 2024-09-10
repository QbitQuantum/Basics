void CRandomOptionProperty::LoadScriptBlock( CScript & s, int nRandomOptionKind )
{
	int nTotalProb1		= 0;
	for( int i = 0; i < 3; i++ )	// 3	// 랜덤 옵션이 몇개 부여될 것인가에 대한 확률
	{
		m_anRandomOptionProb[nRandomOptionKind][i]	= s.GetNumber() + nTotalProb1;
		nTotalProb1	= m_anRandomOptionProb[nRandomOptionKind][i];
	}
	s.GetToken();	// {
	int nTotalProb2	= 0;
	RANDOM_OPTION	ro;
	ro.nDst		= s.GetNumber();
	while( *s.token != '}' )
	{
		ASSERT( ro.nDst <= 0xFF );	// 255	// 8
		ro.nProb	= s.GetNumber() + nTotalProb2;
		nTotalProb2		= ro.nProb;
		s.GetToken();	// {
		short	nAdj	= s.GetNumber();
		DWORD dwTotalProb3	= 0;
		while( *s.token != '}' )
		{
			DWORD dwProb	= s.GetNumber() + dwTotalProb3;
			dwTotalProb3	= dwProb;
			ASSERT( abs( nAdj ) <= 0x1FF );		// 511	// 1 | 9
			ro.aAdjData.push_back( AdjData( nAdj, dwProb ) );
			nAdj	= s.GetNumber();
		}
		if( dwTotalProb3 != 1000000000 )
			Error( "Awakening: nDst = %d, dwTotalProb = %d", ro.nDst, dwTotalProb3 );
		m_aRandomOption[nRandomOptionKind].push_back( ro );
		ro.aAdjData.clear();
		ro.nDst		= s.GetNumber();
	}
}