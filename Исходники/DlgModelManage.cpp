BOOL CDlgModelManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	m_strModelName=GetModelName();
	SetWindowTextA(m_hWnd,m_strModelName.c_str());
	m_trayiocn.AddIcon(m_hWnd,m_hIcon,WM_USER+1234,MultCharToWideChar(m_strModelName).c_str());
	ShowWindow(SW_MAXIMIZE);
	CRect rt;
	m_listModelState.GetClientRect (&rt);
	m_listModelState.SetExtendedStyle(m_listModelState.GetExtendedStyle() |LVS_EX_HEADERDRAGDROP| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_SUBITEMIMAGES|LVS_EX_AUTOSIZECOLUMNS);   
	m_listModelState.InsertColumn (0,_T("模块名"),LVCFMT_LEFT,100);
	m_listModelState.InsertColumn (1,_T("编号"),LVCFMT_LEFT,200);
	m_listModelState.InsertColumn (2,_T("城市名"),LVCFMT_LEFT,180);
	m_listModelState.InsertColumn (3,_T("PID"),LVCFMT_LEFT,80);
	m_listModelState.InsertColumn (4,_T("接收地址"),LVCFMT_LEFT,180);
	m_listModelState.InsertColumn (5,_T("接收量"),LVCFMT_LEFT,150);
	m_listModelState.InsertColumn (6,_T("状态"),LVCFMT_LEFT,100);
	//m_listModelState.SetImageList(&m_imgList,LVSIL_SMALL);
	m_ProManager.Initiate();
	SetTimer(IDS_UPDATE_STATES,1000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}