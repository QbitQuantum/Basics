BOOL CProcessLauncher::Init()
{
	bool bStartWait, bHeartbeat;
	bStartWait = bHeartbeat = false;

	CScanner s;
	if( s.Load( "launcher.ini" ) == FALSE)
		return FALSE;

	s.GetToken();
	while( s.tok != FINISHED )
	{
		if( s.Token == "lpAddr" )
		{
			s.GetToken();	// =
			s.GetToken();
			strcpy( m_lpAddr, s.Token );
		}
		else if( s.Token == "lpApplicationName" )
		{
			s.GetToken();	// =
			s.GetToken();
			strcpy( m_lpApplicationName, s.Token );
			SetConsoleTitle( m_lpApplicationName );
		}
		else if( s.Token == "lpCurrentDirectory" )
		{
			s.GetToken();	// =
			s.GetToken();
			strcpy( m_lpCurrentDirectory, s.Token );
		}
		else if( s.Token == "dwId" )
		{
			s.GetToken();	// =
			m_dwId	= (DWORD)s.GetNumber();
		}
		else if( s.Token == "DeadlockCheck" )
		{
			s.GetToken();	// =
			m_dwMilliseconds	= (DWORD)s.GetNumber();
			bHeartbeat = true;
		}
		else if( s.Token == "bWait" )
		{
			s.GetToken();	// =
			bStartWait = (bool)(s.GetNumber() != 0);
		}
		else if( s.Token == "lpDownDirectory" )
		{
			s.GetToken();	// =
			s.GetToken();
			//m_uploader.SetDownDirectory( s.Token );
			strcpy( m_lpDownDirectory, s.Token );			
		}
		s.GetToken();
	}

	if( bStartWait && bHeartbeat )
	{
		AfxMessageBox( "INVALID CONDITION - bWait AND bHeartbeat must be exclusive" );
		return FALSE;
	}
	m_bStartWait = bStartWait;
	
	if( bStartWait || bHeartbeat )
	{
		char lpName[32];
		sprintf( lpName, "%d", GetAppID() );

		m_hEvent = CreateEvent( NULL, FALSE, FALSE, lpName ) ;
		if( m_hEvent == FALSE )
		{
			char szBuffer[128];
			sprintf( szBuffer, "CreateEvent ERROR:%d", GetLastError() );
			AfxMessageBox( szBuffer );
			return FALSE;
		}
	}

	return TRUE;
}