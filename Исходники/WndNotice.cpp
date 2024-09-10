void CWndInfoNotice::OnInitialUpdate() 
{ 
	CWndNeuz::OnInitialUpdate(); 
	// 여기에 코딩하세요

	CWndButton* pWndCheck = (CWndButton*)GetDlgItem( WIDC_CHECK1 );
	pWndCheck->SetCheck( !g_Option.m_bNotice );
	CWndText* pWndText = (CWndText*)GetDlgItem( WIDC_TEXT1 );

#ifdef __YNOTICE_UNI1026
	CString strnotice;
	strnotice = GetLangFileName( ::GetLanguage(), FILE_NOTICE );
		
	CScript scanner;
	if( scanner.Load( "Client\\"+strnotice ) == FALSE )
		return;
	
	pWndText->m_string.AddParsingString( scanner.m_pProg  );
	pWndText->ResetString();
#else //__YNOTICE_UNI1026
	CFileStatus fileStatus;
	
	CString strnotice;
	strnotice = GetLangFileName( ::GetLanguage(), FILE_NOTICE );
	
	if( CFile::GetStatus( "Client\\"+strnotice, fileStatus ) == TRUE )
	{
		if( g_Option.m_tNoticeTime != fileStatus.m_mtime.GetTime() )
			g_Option.m_tNoticeTime = static_cast< time_t >( fileStatus.m_mtime.GetTime() );

		CFileIO file;

		strnotice = GetLangFileName( ::GetLanguage(), FILE_NOTICE );
	
		if(::GetLanguage() == LANG_VTN)
		{
			if( file.Open( "Client\\"+strnotice, "rb" ) )
			{
				int nLength = file.GetLength();
				TCHAR* pChar = new TCHAR[ nLength + 2 ];
				file.Read( pChar, nLength );
				*(pChar + nLength ) = '\0';
				*(pChar + nLength + 1 ) = '\0';

				char* lpMultiByte = new char[ nLength + 2 ];

				int nResult = WideCharToMultiByteEx( g_codePage, 0, 
					                               (LPWSTR)(pChar+2), -1, 
						                           lpMultiByte, nLength, 
												   NULL, NULL );

				if( nResult > 0 )
				{
					lpMultiByte[nResult-1] = 0;
					pWndText->m_string.AddParsingString( lpMultiByte );
					pWndText->ResetString();
				}
				safe_delete_array(pChar);
				safe_delete_array(lpMultiByte);
			}
		}
		else
		{
			if( file.Open( "Client\\"+strnotice, "rb" ) )
			{
				int nLength = file.GetLength();
				TCHAR* pChar = new TCHAR[ nLength + 1];
				file.Read( pChar, nLength );
				pChar[ nLength ] = 0;
				//pWndText->SetString( pChar );
				pWndText->m_string.AddParsingString( pChar );
				pWndText->ResetString();
				safe_delete( pChar );
			}
		}
	}
#endif //__YNOTICE_UNI1026

	// 윈도를 중앙으로 옮기는 부분.
	CRect rectRoot = m_pWndRoot->GetLayoutRect();
	CRect rectWindow = GetWindowRect();
	CPoint point( rectRoot.right - rectWindow.Width(), 110 );
	Move( point );
	MoveParentCenter();

/////////////////////////////////////////////////////////////////////////////////////////
	int nCount = 0;	
	CScript script;
	if( script.Load(MakePath(DIR_THEME, "TexBannerList.inc" )) )
	{
		int nLang;
		nLang = script.GetNumber();
		do 
		{
			if( nLang == ::GetLanguage() )
			{
				script.GetToken();
				
				nCount = atoi( script.token );
				
				script.GetToken();				
				
				for( int i=0; i<nCount; i++ )
				{
					CString addStr = script.token;
					m_vecStrBanner.push_back( addStr );
					script.GetToken();
				}
				
				if( nCount <= 0 )
				{
					Error( "TexBannerList.inc의 갯수가 0이다" );
					return;
				}
				
				break;
			}
			else
				script.GetLastFull();

			nLang = script.GetNumber();
		} while( script.tok != FINISHED );		
	}
	
	SAFE_DELETE( m_atexPannel );
	if( nCount > 0 )
	{
		m_atexPannel = new IMAGE;
		LoadImage( MakePath( DIR_THEME, m_vecStrBanner[xRandom(nCount)] ), m_atexPannel );
		AdjustWndBase();	
	}
/////////////////////////////////////////////////////////////////////////////////////////	
} 