BOOL CSetProxyPage::OnInitDialog()
{
	ISettingsPropPage::OnInitDialog();

	m_tooltips.Create(this);
	m_tooltips.AddTool(IDC_SERVERADDRESS, IDS_SETTINGS_PROXYSERVER_TT);

	CString proxy = g_Git.GetConfigValue(_T("http.proxy"), CP_UTF8);

	m_SSHClient = m_regSSHClient;
	if (m_SSHClient.IsEmpty())
		m_SSHClient = CRegString(_T("Software\\TortoiseGit\\SSH"), _T(""), FALSE, HKEY_LOCAL_MACHINE);
	if (m_SSHClient.IsEmpty())
	{
		TCHAR sPlink[MAX_PATH];
		GetModuleFileName(NULL, sPlink, _countof(sPlink));
		LPTSTR ptr = _tcsrchr(sPlink, _T('\\'));
		if (ptr)
		{
			_tcscpy_s(ptr + 1, MAX_PATH - (ptr - sPlink + 1), _T("TortoiseGitPLink.exe"));
			m_SSHClient = CString(sPlink);
		}
	}
	m_serveraddress = m_regServeraddress;
	m_serverport = _ttoi((LPCTSTR)(CString)m_regServerport);
	m_username = m_regUsername;
	m_password = m_regPassword;

	if (proxy.IsEmpty())
	{
		m_isEnabled = FALSE;
		EnableGroup(FALSE);
	}
	else
	{
		int start=0;
		start = proxy.Find(_T("://"),start);
		if(start<0)
			start =0;
		else
			start+=3;

		int at = proxy.Find(_T("@"), 0);
		int port;

		if(at<0)
		{
			m_username=_T("");
			m_password=_T("");
			port=proxy.Find(_T(":"),start);
			if(port<0)
				m_serveraddress = proxy.Mid(start);
			else
				m_serveraddress = proxy.Mid(start, port-start);

		}
		else
		{
			int username;
			username = proxy.Find(_T(":"),start);
			if(username<=0 || username >at)
			{
				StringUnescape(proxy.Mid(start, at - start), &m_username);
				m_password=_T("");
			}
			else if(username < at)
			{
				StringUnescape(proxy.Mid(start, username - start), &m_username);
				StringUnescape(proxy.Mid(username + 1, at - username - 1), &m_password);
			}

			port=proxy.Find(_T(":"),at);
			if(port<0)
				m_serveraddress = proxy.Mid(at+1);
			else
				m_serveraddress = proxy.Mid(at+1, port-at-1);
		}

		if(port<0)
		{
			m_serverport= 0;
		}
		else
			m_serverport = _ttoi(proxy.Mid(port+1));

		m_isEnabled = TRUE;
		EnableGroup(TRUE);
	}

	SHAutoComplete(::GetDlgItem(m_hWnd, IDC_SSHCLIENT), SHACF_FILESYSTEM | SHACF_FILESYS_ONLY);

	UpdateData(FALSE);

	return TRUE;
}