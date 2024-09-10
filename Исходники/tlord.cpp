////////////////////////////////////////////////////////////////////////////////
// 트랜스 서버용 선거 클래스
CTElection::CTElection( CLord* pLord )
:
IElection( pLord ),
#ifdef __INTERNALSERVER
m_bRun( FALSE )	// 내부 서버는 군주 프로세스 비활성
#else	// __INTERNALSERVER
m_bRun( TRUE )
#endif	// __INTERNALSERVER
{
}

CTElection::~CTElection()
{
}

BOOL CTElection::Initialize( const char* szFile )
{	// 초기화
	if( !ReadIni( szFile ) )	// 스크립트 로드
	{
		election::OutputDebugString( "CTElection::Initialize(): LoadScript(): file not found: %s", szFile );
		return FALSE;
	}
	return TRUE;
}

BOOL CTElection::ReadIni( const char* szFile )
{	// 스크립트 로드
	CScript s;
	if( s.Load( szFile ) == FALSE )
		return FALSE;

	s.GetToken();
	while( s.tok != FINISHED )
	{
		if( s.Token == _T( "property" ) )
		{
			s.GetToken();	// {
			s.GetToken();
			while( *s.token != '}' )
			{
				if( s.Token == _T( "nDayOfWeek" ) )
					property.nDayOfWeek		= s.GetNumber();
				else if( s.Token == _T( "nHour" ) )
					property.nHour	= s.GetNumber();
				else if( s.Token == _T( "tCandidacy" ) )
					property.tCandidacy	= s.GetNumber();
				else if( s.Token == _T( "tVote" ) )
					property.tVote	= s.GetNumber();
				else if( s.Token == _T( "nDays" ) )
					property.nDays	= s.GetNumber();
				s.GetToken();
			}
		}
		else if( s.Token == _T( "rate" ) )
		{
			s.GetToken();	// {
			float fRate	= s.GetFloat();
			while( *s.token != '}' )
			{
				property.m_vReturnDepositRates.push_back( fRate );
				fRate	= s.GetFloat();
			}
		}
		else if( s.Token == _T( "fRequirementFactor" ) )
		{
			property.fRequirementFactor	= s.GetFloat();
		}
		else if( s.Token == _T( "item" ) )
		{
			int iIndex	= s.GetNumber();
			s.GetToken();	// {
			int nItem		= s.GetNumber();
			while( *s.token != '}' )
			{
				property.m_vItems[iIndex].push_back( nItem );
				nItem	= s.GetNumber();
			}
		}
		s.GetToken();
	}
	return TRUE;
}