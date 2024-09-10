PSDash::_void CLoginDlg::OnCreateSessionResult( _dword dwCode )
{
	if(GetFramework()->GetLocalPSUID().IDType() == PSUID_GameServer)
	{
		return;
	}
	
	if(dwCode != E_SP_SUCCESS)
	{
		AtlMessageBox(m_hWnd,(LPCTSTR)GetFramework()->GetError(dwCode));
	}
	else
	{
		
		BSTR Username = NULL, Password = NULL;
		GetDlgItemText(IDC_USERNAME, Username);
		GetDlgItemText(IDC_PASSWORD, Password);
		if(Username == NULL) Username = L"";
		if(Password == NULL) Password = L"";
		
		m_cfg.Set(L"Config", L"UserName",Username);
		m_cfg.Set(L"Config", L"Password",Password);
		GetLogWindow().SetParent(NULL);
		DestroyWindow();
		AtlTrace(L"[LOGINDLG] Post Quit MSG 1\n");
		::PostQuitMessage(1);
	}
}