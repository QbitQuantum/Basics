int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

	HRESULT Hr = ::CoInitialize(NULL);
	if( FAILED(Hr) ) return 0;
	HRESULT hRes = ::OleInitialize(NULL);
	// 初始化UI管理器
	CPaintManagerUI::SetInstance(hInstance);
	// 初始化资源
	InitResource();

	CDemoFrame* pFrame = new CDemoFrame();
	if( pFrame == NULL ) return 0;
	pFrame->Create(NULL, _T("duilib使用例子集锦（By Troy）"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 800, 572);
	pFrame->CenterWindow();
	ShowWindow(*pFrame, SW_SHOW);
	CPaintManagerUI::MessageLoop();
	delete pFrame;
	pFrame = NULL;
	CResourceManager::GetInstance()->Release();

	OleUninitialize();
	::CoUninitialize();
	return 0;
}