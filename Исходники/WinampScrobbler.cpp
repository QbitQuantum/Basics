BOOL	CWinampScrobbler::StartScrobbling(HINSTANCE hInstance, 
										  HWND hWndWinamp, 
										  HWND hWndWinampML, 
										  CStdString strWorkingDir)
{
	if ( ( hWndWinamp != NULL) &&
		   ( ::IsWindow(hWndWinamp)) )
	{
		m_hWndWinamp		= hWndWinamp;
		m_hWndWinampML		= hWndWinampML;
		
		m_Controller.Init(FALSE, hWndWinamp, hWndWinampML);
		
		BOOL bRet =  CScrobbler::StartScrobbling(strWorkingDir, hInstance);

        EnumThreadWindows( GetCurrentThreadId(), CWinampScrobbler::enumWndProc, (LPARAM)this );

        if( m_bootstrap.bootStrapRequired() )
        {
            PRINTF(DEBUG_FLOW,
                "CWinampScrobbler::StartScrobbling", "Bootstrap is required" );

            m_bootstrap.setParentHwnd( m_mainWinAmpWnd );
            m_bootstrap.sethWndWinampML( m_hWndWinampML );
            m_bootstrap.setScrobSub( m_Submitter );
            m_bootstrap.setModuleHandle( hInstance );
            m_bootstrap.startBootStrap();
        }
        

		return bRet;
	}

	return FALSE;
} 