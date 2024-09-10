int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	HRESULT Hr = ::CoInitialize(NULL);
	if( FAILED(Hr) ) return 0;
	HRESULT hRes = ::OleInitialize(NULL);
	// 初始化UI管理器
	CPaintManagerUI::SetInstance(hInstance);
	// 初始化资源
	InitResource();

	::SetCurrentDirectory(CPaintManagerUI::GetInstancePath());
#ifndef _DEBUG
	CPaintManagerUI::LoadPlugin(_T("TroyControls.dll"));
#else
	CPaintManagerUI::LoadPlugin(_T("TroyControls_d.dll"));
#endif
	CMainWnd* pFrame = new CMainWnd();
	if( pFrame == NULL ) return 0;
	pFrame->Create(NULL, _T("TroyBrowser"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 990,690);
	pFrame->CenterWindow();
	pFrame->ShowModal();

	CPaintManagerUI::MessageLoop();
	OleUninitialize();
	::CoUninitialize();
	return 0;
}