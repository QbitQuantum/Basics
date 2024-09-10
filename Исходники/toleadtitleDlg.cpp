BOOL CToleadtitleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CWnd* pWnd = GetDlgItem( IDC_STATIC_PLACEHOLDER );
	CRect rcCtrl;
	pWnd->GetClientRect( &rcCtrl );
	pWnd->ClientToScreen( &rcCtrl );
	pWnd->DestroyWindow();
	
	ScreenToClient( &rcCtrl );
	DWORD dwStyle = WS_CHILD|WS_BORDER|WS_VSCROLL|WS_VISIBLE|ES_MULTILINE|ES_AUTOVSCROLL|ES_WANTRETURN;
	m_RichEditCtrl.Create( dwStyle, rcCtrl, this, 0x1245 );

	CString dbdata=path+"\\data\\error.db";
	int result=sqlite3_open(dbdata,&db);
	
    if(result!=SQLITE_OK)
    {
		MessageBox("failed to open database!",NULL,MB_OK);
		OnCancel();
        return FALSE;
    }

	CEdit* pEdit = (CEdit*)m_type.GetWindow(GW_CHILD);
	// 将输入框色设置为只读
	pEdit->SetReadOnly(TRUE);
	m_type.SetCurSel(0);
	
	////////////////////////////////////////////////////////
	//读取输入历史记录
	string str;
	CString historydata=path+"\\data\\history.ini";
	fstream fpinput;
	fpinput.open(historydata,ios::in);

	int len;
	getline(fpinput,str);
	len=atoi(str.data());
	for(;len--;)
	{
		getline(fpinput,str);
		m_A.AddString(str.data());
		combox_A.push_back(str);
	}

	getline(fpinput,str);
	len=atoi(str.data());
	for(;len--;)
	{
		getline(fpinput,str);
		m_B.AddString(str.data());
		combox_B.push_back(str);
	}
	fpinput.close();
	////////////////////////////////////////////////////////

	m_A.SetCurSel(0);
	m_B.SetCurSel(0);

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}