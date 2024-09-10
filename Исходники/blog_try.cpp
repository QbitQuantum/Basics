int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);//设置程序实例
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));//实例句柄与渲染类关联,获得皮肤文件目录（加载皮肤文件在OnCreate之中）

	HRESULT Hr = ::CoInitialize(NULL);//初始化COM库, 为加载COM库提供支持
	if( FAILED(Hr) ) 
		return 0;

	CMainFrame* pMainFrame = new CMainFrame();//创建应用程序窗口类对象
	if( pMainFrame == NULL ) 
		return 0;
	pMainFrame->SetIcon(IDI_ICON1);
	//以背景的句柄为父窗口创建DLG，如果不这样的话，在任务栏会产生两个窗体，不信，你就把下面create的第一个参数改成NULL试试，你就懂了
	pMainFrame->Create(pMainFrame->m_pBackWnd->GetHandle(), _T("AdderCalc"), UI_WNDSTYLE_DIALOG, 0);
	//让背景图片居中
	pMainFrame->m_pBackWnd->CenterWindow();
	
	pMainFrame->ShowWindow(true);//显示窗口
	CPaintManagerUI::MessageLoop();//进入消息循环

	::CoUninitialize();//退出程序并释放COM库
	return 0;
}