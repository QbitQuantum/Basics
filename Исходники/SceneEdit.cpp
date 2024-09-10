BOOL CSceneEditApp::InitInstance()
{
// 	// 如果一个运行在 Windows XP 上的应用程序清单指定要
// 	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
// 	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
// 	INITCOMMONCONTROLSEX InitCtrls;
// 	InitCtrls.dwSize = sizeof(InitCtrls);
// 	// 将它设置为包括所有要在应用程序中使用的
// 	// 公共控件类。
// 	InitCtrls.dwICC = ICC_WIN95_CLASSES;
// 	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


//	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	//初始化OLE
	OleInitialize(NULL);

	//初始化GDI+
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&g_gdiplusToken, &gdiplusStartupInput, NULL);

	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// 创建并加载框架及其资源
	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, NULL);

	///////////////////////////////////////////
	///////////////////////////初始化主程序
	CView* pView = pFrame->GetActiveView();
	RECT rect;
	pView->GetClientRect(&rect);

	m_app.Init(rect.right-rect.left, rect.bottom-rect.top, pView->GetSafeHwnd(), m_pMainWnd->GetSafeHwnd());

	///////////////////////////////////////////
	///////////////////////////初始化编辑器UI
	if(!pFrame->CreateEditorMainUI())
		return FALSE;

	///////////////////////////////////////////
	///////////////////////////初始化完毕,开始渲染...
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	//pFrame->SetForegroundWindow();

	pFrame->SetTimer(0, (UINT)TIME_PER_FRAME*1000, NULL);

	return TRUE;
}