BOOL CPcShareApp::InitInstance()
{
	AfxOleInit();

	//保证只启动一次
	m_LockHandle = CreateMutex(NULL,TRUE,"PcShare2005");
	if(m_LockHandle == NULL ||
		GetLastError() == ERROR_ALREADY_EXISTS)
		return FALSE;
	ReleaseMutex(m_LockHandle);


	//初始化SOCKET环境
	WSADATA		data;
	if(WSAStartup(MAKEWORD(2, 2), &data))
		return FALSE;
	if (LOBYTE(data.wVersion) !=2 || 
		HIBYTE(data.wVersion) != 2)
	{
		WSACleanup();
		return FALSE;
	}

	//初始化控件环境
	AfxEnableControlContainer();
	Enable3dControls();	
    CoInitialize(NULL);

	memset(&m_MainValue, 0, sizeof(m_MainValue));

	//启动主界面
	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;
	pFrame->LoadFrame(IDR_MAINFRAME);
	pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->ResizeWnd();
	pFrame->UpdateWindow();

	pFrame->StartWork();

	return TRUE;
}