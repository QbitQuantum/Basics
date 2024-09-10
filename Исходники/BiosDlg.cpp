BOOL CBiosDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	_tcscpy(m_szTempDir,_tgetenv(TEXT("SystemRoot")));
	_tcscat(m_szTempDir,TEXT("\\Temp"));
	GetCurrentDirectory(2048,m_curPath);
	typedef BOOL (WINAPI* ChangeWindowMessageFilterFn)( UINT, DWORD );
	HMODULE hUserMod = NULL;
	BOOL bResult = FALSE;
	hUserMod = LoadLibrary(TEXT("user32.dll"));
	if (hUserMod)
	{
		ChangeWindowMessageFilterFn pfnChangeWindowMessageFilter = (ChangeWindowMessageFilterFn)GetProcAddress( hUserMod, "ChangeWindowMessageFilter" );
		if (pfnChangeWindowMessageFilter)
		{
			pfnChangeWindowMessageFilter(WM_DROPFILES, 1); // 1-MSGFLT_ADD, 2-MSGFLT_REMOVE
			pfnChangeWindowMessageFilter(0x0049, 1); // 1-MSGFLT_ADD, 2-MSGFLT_REMOVE
		}

		FreeLibrary(hUserMod);
	}
	m_nBiosSize = 0;
	m_bExistKey = FALSE;
	m_strSSN = TEXT("");
	CCpuInfo ci;
	mbstowcs(m_wszCpuInfo,ci.GetBrand(),49);
	IsWow64Process(GetCurrentProcess(),&m_bIsx64);
	CBiosInfo* pInfo = ((CHWToolApp*)AfxGetApp())->m_BiosInfo;
	SetDlgItemText(IDC_IBV,pInfo->m_BiosInfoW.m_wszIVN);
	SetDlgItemText(IDC_BIOSVER,pInfo->m_BiosInfoW.m_wszIV);
	SetDlgItemText(IDC_BIOSDATE,pInfo->m_BiosInfoW.m_wszID);
	SetDlgItemText(IDC_BIOSHASH,pInfo->m_BiosInfoW.m_wszSK);
	SetDlgItemText(IDC_PID,pInfo->m_BiosInfoW.m_wszSM);
	SetDlgItemText(IDC_MODEL,pInfo->m_BiosInfoW.m_wszSP);
	SetDlgItemText(IDC_SERIALNUM,pInfo->m_BiosInfoW.m_wszSS);
	SetDlgItemText(IDC_MBPID,pInfo->m_BiosInfoW.m_wszBM);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}