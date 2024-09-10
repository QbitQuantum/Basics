BOOL CSmartVillageApp::InitInstance()
{
	//XP数据库支持
	//ZOGNA//DOWN
	AfxOleInit();
	//CoInitialize(NULL);

	//AfxGetStaticModuleState();
//	AfxGetModuleState()->m_hCurrentInstanceHandle = GetModuleHandle(NULL); 
/*

	HRESULT hr = OleInitialize(NULL);   
	if(hr == S_FALSE)   
	{   
		OleUninitialize();   
	}   
	AfxEnableControlContainer();   
	COleObjectFactory::RegisterAll(); 
*/
	//当前路径
	GetCurrentDirectory(ZOG_MAX_PATH_STR, CurrentDir);
	sprintf(DlgSetSystem.SystemIniPath,"%s\\yrsysteminfo.ini",CurrentDir);
	
	//ZOGNA//UP
	//读系统配置表
	DlgSetSystem.Read2Dlg();

	CWzdSplash wndSplash;                 //创建启动窗口类的实例
	wndSplash.Create(IDB_SPLASH);
	wndSplash.CenterWindow();
	wndSplash.UpdateWindow();          //send WM_PAINT

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif


	////////////////lynn/////////////////
	////////////////lynn/////////////////
	int ioError = MySqlIO.ConnectionMySQL("YRSVDataBaseConfig.db");
	if(ioError == ReadFile_FAIL)
	{
		CDLGWarnning dlgw;
		dlgw.m_wintxt="连接数据库";					//窗口标题
		dlgw.m_warntxt="读数据库配置文件失败";	//窗口内容
		dlgw.DoModal();

		return FALSE;
	}
	else if(ioError == MySQLInit_FAIL)
	{
		CDLGWarnning dlgw;
		dlgw.m_wintxt="连接数据库";					//窗口标题
		dlgw.m_warntxt="数据库ADO初始化失败";	//窗口内容
		dlgw.DoModal();

		return FALSE;
	}
	else if(ioError == ContOpen_FAIL)
	{
		CDLGWarnning dlgw;
		dlgw.m_wintxt="连接数据库";					//窗口标题
		dlgw.m_warntxt="数据库无法连接:账号密码IP异常 或文件夹带()";	//窗口内容
		dlgw.DoModal();

		return FALSE;
	}
	else if(ioError == Connectd_DONE)
	{
		//MessageBox("连接数据库成功");
	}
#if OPEN_FACEDETECT_CODE
	//初始化人脸模型
	SetCurrentDirectory(CurrentDir);
	if(Face_Init("models", &RWmodule_handle) != 0)
	{
		CDLGWarnning dlgw;
		dlgw.m_wintxt="人脸模型";					//窗口标题
		dlgw.m_warntxt="人脸模型加载失败";	//窗口内容
		dlgw.DoModal();
	}
#endif

	wndSplash.DestroyWindow();//销毁初始画面窗口

	////////////////lynn/////////////////

	LPWSTR *szArglist = NULL;  
    int nArgs = 0;  
    szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);  
    if( nArgs > 1)  
    {  
		//szArglist就是保存参数的数组  
		//nArgs是数组中参数的个数  
		//数组的第一个元素表示进程的path，也就是szArglist[0]，其他的元素依次是输入参数。  
		DlgLogin.SilentMode=TRUE;
		DlgLogin.flag=LOGIN_IN;
		DlgLogin.m_user = szArglist[1];
		DlgLogin.m_password = szArglist[2];
		//静默登陆
		DlgLogin.OnOK_Silent();
    }  
	else
	{
		DlgLogin.SilentMode=FALSE;
		//登陆框
		DlgLogin.flag=LOGIN_IN;
		if( IDCANCEL == DlgLogin.DoModal())
		{
#if OPEN_FACEDETECT_CODE
			Face_UnInit();
#endif
			return FALSE;
		}
	}
    //取得参数后，释放CommandLineToArgvW申请的空间  
    LocalFree(szArglist);  

		
	//主界面
	CSmartVillageDlg dlg;
	m_pMainWnd = &dlg;

	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

#if OPEN_FACEDETECT_CODE
	Face_UnInit();
#endif

	//ZOGNA//DOWN
	//CoUninitialize();
	//ZOGNA//UP

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}