BOOL CResManager::Load( LPCTSTR lpszName )
{
	CScript scanner;
	if( scanner.Load( lpszName, FALSE ) == FALSE )
		return FALSE;

	DWORD dwWndType;
	scanner.GetToken_NoDef();

	while( scanner.tok != FINISHED )
	{
		LPWNDAPPLET pWndApplet = new WNDAPPLET;
		pWndApplet->pWndBase = NULL;
		pWndApplet->strDefine = scanner.token;

	//	Error( "Load %s", scanner.token);

		pWndApplet->dwWndId = CScript::GetDefineNum( scanner.token );

		scanner.GetToken();
		pWndApplet->strTexture = scanner.token;

		scanner.GetToken();

		pWndApplet->bTile = scanner.GetNumber();
		CSize size;
		pWndApplet->size.cx = scanner.GetNumber();
		pWndApplet->size.cy = scanner.GetNumber();
		pWndApplet->dwWndStyle = scanner.GetNumber();
		pWndApplet->d3dFormat = (D3DFORMAT)scanner.GetNumber();

		// 타이틀 
		pWndApplet->strTitle = GetLangApplet( scanner, pWndApplet, FALSE );
		// 핼프 키 
		pWndApplet->strToolTip = GetLangApplet( scanner, pWndApplet, TRUE );

		
		// HelpKey
		m_mapWndApplet.SetAt( (void*)pWndApplet->dwWndId, pWndApplet );
		scanner.GetToken(); // skip {
		dwWndType = scanner.GetNumber(); 
		while( *scanner.token != '}' )
		{
			LPWNDCTRL pWndCtrl = new WNDCTRL;
			pWndCtrl->dwWndType = dwWndType;
			scanner.GetToken_NoDef();
			pWndCtrl->strDefine = scanner.token;///Char;
			for( int z = 0; z < pWndApplet->ptrCtrlArray.GetSize(); z++ )
			{
				if( ((LPWNDCTRL)pWndApplet->ptrCtrlArray.GetAt( z ) )->strDefine == pWndCtrl->strDefine )
				{
					CString string;
					string.Format( "%s에서 ID 충돌 %s ", pWndApplet->strDefine, pWndCtrl->strDefine );
					AfxMessageBox( string );
			//		assert(false);
				}
			}
			pWndCtrl->dwWndId = CScript::GetDefineNum( scanner.token );
			scanner.GetToken();
			pWndCtrl->strTexture = scanner.token;//token;
			pWndCtrl->bTile = scanner.GetNumber();
			pWndCtrl->rect.left = scanner.GetNumber();
			pWndCtrl->rect.top = scanner.GetNumber();
			pWndCtrl->rect.right = scanner.GetNumber();
			pWndCtrl->rect.bottom = scanner.GetNumber();
			pWndCtrl->dwWndStyle = scanner.GetNumber();

			// visible, Group, Disabled, TabStop
			pWndCtrl->m_bVisible = scanner.GetNumber();
			pWndCtrl->m_bGroup = scanner.GetNumber();
			pWndCtrl->m_bDisabled = scanner.GetNumber();
			pWndCtrl->m_bTabStop = scanner.GetNumber();
			
			scanner.GetNumber();
			scanner.GetNumber();
			scanner.GetNumber();

			// 타이틀 
			pWndCtrl->strTitle = GetLangCtrl( scanner, pWndCtrl, FALSE );
			// 핼프 키 
			pWndCtrl->strToolTip = GetLangCtrl( scanner, pWndCtrl, TRUE );
			
			pWndApplet->ptrCtrlArray.Add( pWndCtrl );
			dwWndType = scanner.GetNumber(); 
		} 
		scanner.GetToken_NoDef();
	} 

	return TRUE;
}