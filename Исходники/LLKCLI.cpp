BOOL CLLKCLIApp::InitInstance()
{

	AfxSocketInit();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	GetPrivateProfileStringA("SERVER_INFO","IP","127.0.0.1",ip,sizeof(ip),"./set.ini");
	char strPort[5];
	GetPrivateProfileStringA("SERVER_INFO","PORT","5601",strPort,sizeof(strPort),"./set.ini");
	port = atoi(strPort);
	m_pSockThd = new CSockThd;
	m_pSockThd->CreateThread();

	CLLKCLIDlg login;
	int nResponse = login.DoModal();

	if(nResponse == IDCANCEL)
		return FALSE;

	CLLKHome home;
	home.m_uid=userInfo.id;
	home.m_nick=userInfo.nick;
	home.m_score=userInfo.type;
	if(userInfo.sex==0){
		home.m_sex="Å®";
	}
	else{
		home.m_sex="ÄÐ";
	}
	m_pMainWnd = &home;
	home.DoModal();

	return FALSE;
}