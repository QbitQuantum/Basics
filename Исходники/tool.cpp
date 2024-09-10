void XTool::LoadINI()
{
	TCHAR szWork[1024];
	XE::GetCwd( szWork, sizeof(szWork) / sizeof(TCHAR)  );	// SE.exe 실행파일 폴더를 얻어냄
	CString strIniName = szWork;
	strIniName += _T("\\se.ini");
	CONSOLE( "GetCwd:%s", szWork );
	GetCurrentDirectory( 1024, szWork );		// spr파일을 직접 더블클릭해서 실행시킬땐 se.ini를 spr이 있는 폴더에서 찾아서 이방법 포기함. 현재디렉토리(작업디렉터리)를 얻어옴
	CONSOLE( "GetCurrentDirectory:%s", szWork );

	{
		CToken token;
		if( token.LoadFile( strIniName, TXT_UTF16 ) )		{
			while( token.GetToken() )		// "Working_Folder"
			{
				if( token == _T("Working_Folder") )	{
					m_strWorkPath = token.GetToken();
				} else
				if( token == _T("bg") ) {
					auto szToken = token.GetToken();
					if( XE::IsHave(szToken) )
						m_pathBg = szToken;
				} else
				if( token == _T( "grid_unit" ) ) {
					GetFrameView()->m_GridUnit = (CFrameView::xtGridUnit)token.GetNumber();
				} else
				if( token == _T("LuaGlue") )
				{
					token.GetToken();		// {
					char* cblock = token.CreateGetBlock();		// 블럭안의 코드를 모두 읽는다
					strcpy_s( XSprDat::s_cGlobalLua, cblock );
					SAFE_DELETE( cblock );
//					token.GetToken();		// lua본문을 읽는다.
//					strcpy_s( XSprDat::s_cGlobalLua, Convert_TCHAR_To_char( token.m_Token ) );
//					token.GetToken();		// }
				}
			}
			if( m_strWorkPath.IsEmpty() )
				XERROR( "Working_Folder항목을 찾을수 없습니다. 에러가 계속 되는경우 se.ini파일을 지우고 다시 실행하십시요." );

			GetConsoleView()->Message( _T("%s 로딩완료"), strIniName );
		} else
		{
			// 최초실행시 defineAct.h가 있는 워킹폴더를 지정하는 단계
			{
				TCHAR szDisplayName[MAX_PATH];
				BROWSEINFO bi;
				bi.hwndOwner = g_pMainFrm->GetSafeHwnd();
				bi.lParam = 0;
				bi.lpfn = nullptr;
				bi.lpszTitle = _T("리소스 폴더를 지정해주세요");
				bi.pidlRoot = nullptr;
				bi.pszDisplayName = szDisplayName;
				bi.ulFlags = 0;
				ITEMIDLIST *pidList = SHBrowseForFolder( &bi );
				if( pidList )
				{
					SHGetPathFromIDList( pidList, szDisplayName );
					m_strWorkPath = szDisplayName;
					// 폴더 선택후 곧바로 ini에 기록
					SaveINI( strIniName );
				}
			}
		}
	}

	GetConsoleView()->Message( _T("working folder: %s"), m_strWorkPath );
	XE::SetWorkDir( m_strWorkPath );

	// defineAct.h를 읽음
	CString str = m_strWorkPath + _T("\\defineAct.h");
	if( m_pDefineAct ) {
		XLOG( "" );
		SAFE_DELETE( m_pDefineAct );
	}
	m_pDefineAct = new CDefine;
	if( !m_pDefineAct->Load( str ) ) {
		GetConsoleView()->Message( _T("%s를 찾을 수 없습니다"), str );
		XALERT( "%s를 찾을 수 없습니다", str );
		SAFE_DELETE( m_pDefineAct );
	} else
		GetConsoleView()->Message( _T("%s 로딩완료"), str );
}