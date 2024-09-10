BOOL Script( LPCSTR lpszFileName )
{
	CScanner s;
	CServerDesc* pServer;
	POINT topLeft;
	SIZE	size;

	if( s.Load( lpszFileName ) )
	{
		g_MyTrace.AddLine( '-' );

		s.GetToken();

		while( s.tok != FINISHED )
		{
			if( s.Token == "Sys" )
			{
				g_dwSys	= s.GetNumber();
			}
			else if( s.Token ==  "dwId" )
			{
				g_dwId = s.GetNumber();
			}
			else if( s.Token == "Database" )
			{
				s.GetToken();
				strcpy( szDataBaseAddr, s.Token );
			}
			else if( s.Token == "Certifier" )
			{
				s.GetToken();
				strcpy( szCertifierAddr, s.Token );
			}
			else if( s.Token == "TEST" )
			{
				s_bTest	= TRUE;			
			}
			else if( s.Token == "PartyExpRate" )
			{
				s_fPartyExpRate		= s.GetFloat();
			}
			else
			{
				pServer		= new CServerDesc;
				u_long uKey	= (u_long)_ttoi( s.Token );
				pServer->SetKey( uKey );

				if( s.GetToken() == DELIMITER )
				{
					while( s.GetToken() != DELIMITER )
					{
						CJurisdiction* pJurisdiction	= new CJurisdiction;
						pJurisdiction->m_dwWorldID	= (DWORD)_ttoi( s.Token );
						topLeft.x	= s.GetNumber();	topLeft.y	= s.GetNumber();
						size.cx		= s.GetNumber();	size.cy		= s.GetNumber();
						pJurisdiction->m_rect.SetRect( topLeft.x, topLeft.y, topLeft.x + size.cx, topLeft.y + size.cy );
						pJurisdiction->m_wLeft	= s.GetNumber();	pJurisdiction->m_wRight		= s.GetNumber();
						pServer->m_lspJurisdiction.push_back( pJurisdiction );
					}
				}
		#ifdef __STL_0402
				bool bResult	= g_dpCoreSrvr.m_apSleepServer.insert( CServerDescArray::value_type( pServer->GetKey(), pServer ) ).second;
				ASSERT( bResult );
		#else	// __STL_0402
				g_dpCoreSrvr.m_apSleepServer.SetAt( pServer->GetKey(), pServer );
		#endif	// __STL_0402
				g_MyTrace.Add( pServer->GetKey(), TRUE, "%04d", pServer->GetKey() );
			}
			s.GetToken();
		}
		g_MyTrace.AddLine( '-' );

		return TRUE;
	}

	Error( "Can't open file, %s.\n", lpszFileName );
	return FALSE;
}