// CSafeManDlg 消息处理程序
BOOL CSafeManDlg::OnInitDialog()
{
	CDialogSK::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	// 创建圆角对话框
	CRect dialogRect; 
	GetClientRect(&dialogRect); 
	CRgn rgn; 
	rgn.CreateRoundRectRgn(0,0,dialogRect.Width(),dialogRect.Height(),20,20); 
	SetWindowRgn(rgn,TRUE); 

	SetBitmap(IDB_BACKGROUND);

	m_ProcessManager.LoadBitmap(IDB_PROCESSMANAGER);  // 悬停按钮载入位图
	m_SSDTManager.LoadBitmap(IDB_SSDTMANAGER);  // 悬停按钮载入位图
	m_MonitorManager.LoadBitmap(IDB_MONITORMANAGER);  // 悬停按钮载入位图
	m_Min.LoadBitmap(IDB_MIN);
	m_Exit.LoadBitmap(IDB_EXIT);
	m_Tray.LoadBitmap(IDB_TRAY);

	m_ProcessManager.SetState(TRUE);
	m_SSDTManager.SetState(FALSE);
	m_MonitorManager.SetState(FALSE);

	m_pProcessManager->Create(IDD_PROCESSMANAGER, this);
	m_pSSDTManager->Create(IDD_SSDTMANAGER, this);
	m_pMonitorManager->Create(IDD_MONITORMANAGER, this);

	m_pProcessManager->ShowWindow(SW_SHOW);  
	m_pSSDTManager->ShowWindow(SW_HIDE);  
	m_pMonitorManager->ShowWindow(SW_HIDE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}