void CMCUDemoDlg::Login()
{
	tstringstream strServerFullUrl;	

	BOOL bHasInterface;
	CConfig::Instance()->GetLoginInterface( bHasInterface );
	if ( bHasInterface )
	{
		CLoginDialog loginDlg;
		int nloginType = loginDlg.DoModal();
		if ( CLoginDialog::LOGIN_CANCEL == nloginType )
		{
			// 退出程序。
			EndDialog(0);
			return;
		}

		this->m_htmlWnd.ClearHistoryURL();

		TCHAR ServerFullUrl[1024];
		memset(ServerFullUrl, 0, sizeof(ServerFullUrl));
		if( CConfig::Instance()->GetServerFullUrl((LPTSTR)ServerFullUrl) )
		{
			Log() << L"ServerFullUrl:"<<ServerFullUrl << endl;
		}
		else
		{
			Log() << L"服务器地址不是合法的HTTP地址:"<< endl;
			MessageBox(L"服务器地址不是合法的HTTP地址!", L"错误", MB_OK);
			return;
		}

		HRESULT hr = IsValidURL( NULL, (LPCTSTR)ServerFullUrl, 0 );
		if( S_OK != hr )
		{
			MessageBox(L"服务器地址配置不合法!", L"错误", MB_OK);
			return; 
		}

		strServerFullUrl << ServerFullUrl;

		tstring strRegionId;
		CConfig::Instance()->GetRegionId( strRegionId );
		tstringstream ssAccount;
		ssAccount << (LPCTSTR)loginDlg.m_strUserId << _T( "@" ) << strRegionId;

		string strResult = UTF16toUTF8( ssAccount.str() );
		char* strAccount = (char *) LocalAlloc(LMEM_FIXED, 10240);
		memset(strAccount, 0, 10240);
		UTF_8ToAsciiDisplay( strAccount, 10240, strResult.c_str(), strlen(strResult.c_str()));

		strServerFullUrl << _T( "?" );
		//strServerFullUrl << _T( "Account=" ) << ssAccount.str() << _T( "&" );
		//strServerFullUrl << _T( "Account=" ) << L"admin@%E4%BB%96.wx.js@110000"<<_T( "&" );
		strServerFullUrl << _T( "Account=" ) << strAccount << _T( "&" );
		strServerFullUrl << _T( "Password="******"&" );
		strServerFullUrl << _T( "StreamingType=" ) << int( loginDlg.m_b3GStream ? STREAM_EVDO : STREAM_1X )  << _T( "&" );
		strServerFullUrl << _T( "LoginType=" ) << (int)loginDlg.m_eLoginType;
		LocalFree (strAccount);

		// 保存.
		CMCUSession::Instance()->UserId( ssAccount.str() );
		CMCUSession::Instance()->Password( (LPCTSTR)loginDlg.m_strPassword );
		
	}
	else
	{
		tstring strServer;
		CConfig::Instance()->GetServer( strServer );
		strServerFullUrl << strServer;
	}

	this->m_htmlWnd.OpenUrl( strServerFullUrl.str().c_str() );

}