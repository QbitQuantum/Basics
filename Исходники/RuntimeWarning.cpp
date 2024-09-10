BOOL CRuntimeWarning::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here

	//olde style
	DWORD dwStyle = ::GetWindowLong(m_lstRuntimeWarning.m_hWnd, GWL_STYLE);
	dwStyle &= ~(LVS_TYPEMASK);
	dwStyle &= ~(LVS_EDITLABELS);

	//New Style
	SetWindowLong(m_lstRuntimeWarning.m_hWnd,GWL_STYLE,dwStyle|LVS_REPORT|LVS_NOLABELWRAP|LVS_SHOWSELALWAYS);

	//Extend Style
	DWORD styles = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	ListView_SetExtendedListViewStyleEx(m_lstRuntimeWarning.m_hWnd, styles, styles );

	CString strHeader[] = 
	{
		"告警级别", //level
		"位置",		//place
		"端局类型", //BTSType
		"告警类型", //alarmCode :1:当前实时告警, 正在发生的告警;2:历史告警记录
		"基站",		//BTSID
		"通道号",	//ChannelID
		"开始时间", //start tiem
		"结束时间", //end   time
		"处理状态", //status
		"图像类型", //Category 1.视频 2.图片, 3.无
		""			//UUID
	};

	int nCnt = sizeof(strHeader)/sizeof(strHeader[0]);
	int nWidth[] = {68,160,68,68,68,60,180,180,68,68,0};
	int i=0;
	for (; i<nCnt-1; i++)
		m_lstRuntimeWarning.InsertColumn(i,strHeader[i],LVCFMT_CENTER, nWidth[i]);
	m_lstRuntimeWarning.InsertColumn(i,strHeader[i],LVCFMT_CENTER, 0);
	

	m_imagelist.Create(16,16, TRUE|ILC_COLOR24, 3, 1);
	m_lstRuntimeWarning.SetImageList(&m_imagelist,LVSIL_SMALL);
	
	CBTSMonitorApp *pApp = (CBTSMonitorApp*)AfxGetApp();
	HICON hIcon = pApp->LoadIconA(IDI_LEVEL_1);
	if (hIcon)		m_imagelist.Add(hIcon);
	hIcon = pApp->LoadIconA(IDI_LEVEL_2);
	if (hIcon)		m_imagelist.Add(hIcon);
	hIcon = pApp->LoadIconA(IDI_LEVEL_3);
	if (hIcon)		m_imagelist.Add(hIcon);
	hIcon = pApp->LoadIconA(IDI_LEVEL_4);
	if (hIcon)		m_imagelist.Add(hIcon);
	hIcon = pApp->LoadIconA(IDI_LEVEL_5);
	if (hIcon)		m_imagelist.Add(hIcon);

#ifdef _DEBUG
	//SetTimer(WM_RUNTIME_TIMER,1000,NULL);
#endif

	/*
	//CMainFrame  *pMain = (CMainFrame *)AfxGetMainWnd();
	//CMainFrame   *pMain=(CMainFrame *)AfxGetApp()->m_pMainWnd; 
	i=0;
	for (; i<cnMAX_POP_WINDOW; i++)
	{
		VERIFY(m_pPopVideoDlg[i] = new CWarnPopVideo(this) );
		//VERIFY(m_pPopVideoDlg[i] = new CWarnPopVideo(NULL) );
		m_pPopVideoDlg[i]->SetPopVideoIndex(i);
		m_pPopVideoDlg[i]->Create(IDD_POP_VIDEO);//(IDD_POP_VIDEO,this); //AfxGetApp()->m_pMainWnd);
		m_pPopVideoDlg[i]->SetParentWnd(this);
		m_pPopVideoDlg[i]->ShowWindow(SW_HIDE);

	}
	*/

	m_gConfigMgr.SetRuntimeWarnWnd(this);

	//AddListView();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}