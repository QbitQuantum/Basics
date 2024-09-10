int NewConsole::run(int nShowCmd)
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));
	wcex.cbSize = sizeof(wcex);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = TEXT("Console");
	wcex.lpfnWndProc = (WNDPROC)&NewConsole::WndProc_;
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.hCursor = LoadCursor(NULL, IDC_IBEAM);

	mainWnd_ = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW | WS_EX_LAYERED, (LPCWSTR)RegisterClassEx(&wcex), TEXT("Console"), 
							  WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, this);

	ShowWindow(mainWnd_, nShowCmd);

	consoles_.push_back(std::make_shared<ConsoleWnd>(L"C:\\windows\\system32\\cmd.exe", shared_from_this(), L"Consolas", 10.f));
	activeConsole_ = *consoles_.begin();
	activeConsole_.lock()->activated();

	COORD size = activeConsole_.lock()->querySize(80, 24);
	SetWindowPos(mainWnd_, nullptr, 0, 0, size.X, size.Y, SWP_NOMOVE | SWP_NOZORDER);

	redraw();

	MSG msg;
	while(true)
	{
		MsgWaitForMultipleObjectsEx(0, nullptr, INFINITE, QS_ALLEVENTS, MWMO_ALERTABLE);
		while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if(msg.message == WM_QUIT)
				break;
		}
		if(msg.message == WM_QUIT)
			break;
	}

	return 0;
}