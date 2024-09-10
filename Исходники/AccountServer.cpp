BOOL Script( LPCTSTR lpszFileName )
{
#ifdef __INTERNALSERVER	
	strcpy( g_DbManager.m_szLoginPWD, "#^#^account" );
	strcpy( g_DbManager.m_szLogPWD, "#^#^log" );
#endif

/*
AddTail( -1, 1, "TEST", "192.168.0.103" );
	AddTail( 1, 1, "1", "" );
*/

	CScanner s;
	BOOL bSkipTracking = FALSE;

	if( s.Load( lpszFileName ) )
	{
		s.GetToken();
		while( s.tok != FINISHED )
		{
			if( s.Token == ";" )
			{
				s.GetToken();
				continue;
			}
			else if( s.Token == "TEST" )
			{
				HMENU hMenu	= GetMenu( hMainWnd );
				CheckMenuItem( hMenu, IDM_OPT_EXTERNAL, MF_CHECKED );
				EnableMenuItem( hMenu, IDM_OPT_EXTERNAL, MF_DISABLED | MF_GRAYED );
				CheckMenuItem( hMenu, IDM_OPT_INTERNAL, MF_UNCHECKED );
				EnableMenuItem( hMenu, IDM_OPT_INTERNAL, MF_ENABLED );
				g_dpSrvr.m_bCheckAddr	= false;
				char lpString[MAX_LOADSTRING];
#ifdef _DEBUG
				sprintf( lpString, "%s - debug", szTitle );
#else	// _DEBUG
				sprintf( lpString, "%s - release", szTitle );
#endif	// _DEBUG
				SetWindowText( hMainWnd, lpString );
			}
			else if( s.Token == "AddTail" )
			{
				LPSERVER_DESC pServer
					= g_dpSrvr.m_aServerset + g_dpSrvr.m_dwSizeofServerset++;
				s.GetToken();	// (
				pServer->dwParent	= s.GetNumber();
				s.GetToken();	// ,
				pServer->dwID	= s.GetNumber();
				s.GetToken();	// ,
				s.GetToken();
				strcpy( pServer->lpName, s.Token );
				s.GetToken();	// ,
				s.GetToken();
				strcpy( pServer->lpAddr, s.Token );
				s.GetToken();	// ,
				pServer->b18	= (BOOL)s.GetNumber();
				s.GetToken();	// ,
				pServer->lEnable	= (long)s.GetNumber();
#ifdef __SERVERLIST0911
				pServer->lEnable	= 0L;
#endif	// __SERVERLIST0911
				s.GetToken();	// ,
				pServer->lMax	= (long)s.GetNumber();
				s.GetToken();	// )

//				if( pServer->dwParent != NULL_ID )
				{
					u_long uId	= pServer->dwParent * 100 + pServer->dwID;
					g_dpSrvr.m_2ServersetPtr.insert( map<u_long, LPSERVER_DESC>::value_type( uId, pServer ) );
				}
			}
			else if( s.Token == "MAX" )
			{
				g_dpSrvr.m_nMaxConn = s.GetNumber();
			}
			else if( s.Token == "BillingIP" )
			{
				s.GetToken();
				GetBillingMgr()->SetConfig( BID_IP, (DWORD)(LPCTSTR)s.Token );
			}
			else if( s.Token == "BillingPort" )
			{
				GetBillingMgr()->SetConfig( BID_PORT, s.GetNumber() );
			}
			else if( s.Token == "BillingFreePass" )
			{
				GetBillingMgr()->SetConfig( BID_FREEPASS, s.GetNumber() );
			}
			else if( s.Token == "BillingPWD" )
			{
				// 디비패스워드는 암호화 되어 있다. 암호 시키는 프로그램은 외부실행파일이다.
				s.GetToken();
				char* szPWD = GetBillingPWD();
				::GetPWDFromToken( s.Token, szPWD ); // from query.cpp
			}
			else if( s.Token == "MSG_VER" )
			{
				s.GetToken();
				lstrcpy( g_dpSrvr.m_szVer, s.Token );
			}
			else if( s.Token == "SKIP_TRACKING" )		// login logout로그를 남기지 않는다.
			{
				bSkipTracking = TRUE;
				g_DbManager.SetTracking( FALSE );
			}
			else if( s.Token == "DSN_NAME_LOGIN" )
			{
				s.GetToken();
				strcpy( DSN_NAME_LOGIN, s.Token );
				if( bSkipTracking == FALSE )
					g_DbManager.SetTracking( TRUE );
			}
			else if( s.Token == "DB_ADMIN_ID_LOGIN" )
			{
				s.GetToken();
				strcpy( DB_ADMIN_ID_LOGIN, s.Token );
			}
			else if( s.Token == "DSN_NAME_LOG" )
			{
				s.GetToken();
				strcpy( DSN_NAME_LOG, s.Token );
			}
			else if( s.Token == "DB_ADMIN_ID_LOG" )
			{
				s.GetToken();
				strcpy( DB_ADMIN_ID_LOG, s.Token );
			}
			else if( s.Token == "DSN_NAME_BILLING" )
			{
				s.GetToken();
				strcpy( DSN_NAME_BILLING, s.Token );
			}
			else if( s.Token == "DB_ADMIN_ID_BILLING" )
			{
				s.GetToken();
				strcpy( DB_ADMIN_ID_BILLING, s.Token );
			}
			else if( s.Token == "NOT_RELOADPRO" )
			{
				g_dpSrvr.m_bReloadPro = FALSE;
			}
			else if( s.Token == "NOLOG" )
			{
				g_DbManager.SetLogging( FALSE );	// 상용화 아이템 로그를 남기지 않는다.
			}
			else if( s.Token == "DB_PWD_LOGIN" )
			{
				s.GetToken();
				::GetPWDFromToken( s.Token, g_DbManager.m_szLoginPWD ); 
				TRACE("%s\n", g_DbManager.m_szLoginPWD ); 
			}
			else if( s.Token == "DB_PWD_LOG" )
			{
				s.GetToken();
				::GetPWDFromToken( s.Token, g_DbManager.m_szLogPWD ); 
				TRACE("%s\n", g_DbManager.m_szLogPWD ); 
			}
#ifdef __LOG_PLAYERCOUNT_CHANNEL
			else if( s.Token == "AddChannel" )
			{
				s.GetToken();
				g_dpDbSrvr.m_vecstrChannelAccount.push_back( s.Token );
			}
#endif // __LOG_PLAYERCOUNT_CHANNEL

			s.GetToken();
		}
		return TRUE;
	}

	Error( "Can't open file %s\n", lpszFileName );
	return FALSE;
}