BOOL CKeyBoardDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		//pSysMenu->DeleteMenu(SC_TASKLIST, MF_BYCOMMAND);
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ENABLE_OFFLINE, "离线记录(&O)");
		pSysMenu->AppendMenu(MF_STRING, IDM_CLEAR_RECORD, "清空记录(&C)");

		if (m_bIsOfflineRecord)
			pSysMenu->CheckMenuItem(IDM_ENABLE_OFFLINE, MF_CHECKED);
	}


	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_edit.SetLimitText(MAXDWORD); // 设置最大长度
	ResizeEdit();
	UpdateTitle();
	SendNext();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}