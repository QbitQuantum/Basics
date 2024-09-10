int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BASICENGINE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BASICENGINE));

    MSG msg;

	pMain = new cMain;
	pMain->Setup();

	DWORD dwThID;
	pRenderHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)StartRenderThread, NULL, NULL/*CREATE_SUSPENDED*/, &dwThID);

	while (isQuit)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			pMain->Update();
		}
	}

	DWORD dwExitCode;
	GetExitCodeThread(pRenderHandle, &dwExitCode);
	ExitThread(dwExitCode);



	SAFE_DELETE(pMain);

    return (int) msg.wParam;
}