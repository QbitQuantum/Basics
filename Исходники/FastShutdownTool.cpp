bool CFastShutdown::Initialization(PVOID pData)
{

	HMODULE hDll = ::LoadLibrary(_T("ntdll.dll"));

	PRtlAdjustPrivilege RtlAdjustPrivilege = (PRtlAdjustPrivilege)GetProcAddress(hDll, "RtlAdjustPrivilege");

	int nEn = 0;

	int nResult = RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, true, true, &nEn);

	if(nResult == 0x0c000007c)

	{

		nResult = RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, true, false, &nEn);

	}

	if(FALSE == InjectWinlogon((LPTHREAD_START_ROUTINE)&FastShutdown,(HINSTANCE)pData))
	{
		static TCHAR szAppName[]=TEXT("BANSHUTDOWNTOOL_NAME_FOR_SW");
		static TCHAR szClassName[]=TEXT("BANSHUTDOWNTOOL_CLASS_FOR_SW");
		HWND hwnd;
		MSG msg;
		WNDCLASS wndclass;
		wndclass.style=CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc =WndProc;
		wndclass.cbClsExtra =0;
		wndclass.cbWndExtra =0;
		wndclass.hInstance =(HINSTANCE)pData;
		wndclass.hIcon =LoadIcon(NULL,IDI_APPLICATION);
		wndclass.hCursor =LoadCursor(NULL,IDC_ARROW);
		wndclass.hbrBackground =(HBRUSH)GetStockObject(WHITE_BRUSH);
		wndclass.lpszMenuName =NULL;
		wndclass.lpszClassName =szClassName;
		if (!RegisterClass(&wndclass)) {

			Debug(Dbg,_T("启动失败"));

			return 0;
		}
		hwnd=CreateWindow(szClassName,TEXT("BanShutdownTool(Sw)"), WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,0,0,0,NULL,NULL,(HINSTANCE)pData,NULL);
		SetProcessShutdownParameters(0x4FF,0);
		ShowWindow(hwnd,SW_HIDE);
		UpdateWindow(hwnd);
		while (GetMessage(&msg,NULL,0,0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return msg.wParam ;
	}

	return true;
}