int mainLoop()
{
	MSG msg;
	HACCEL hAccel;
	bool screenSaver = isScreenSaver();
//	DWORD startTickCount = GetTickCount();

	hAccel = LoadAccelerators(CUIWindow::getLanguageModule(),
		MAKEINTRESOURCE(IDR_ACCELERATORS));
	while (1)
	{
		HWND parentWindow;
		HWND topParent;
		HWND newParent;
		DWORD tickCount = GetTickCount();

		debugOut("%d\n", tickCount);
/*
		if (tickCount > startTickCount + 3000 || tickCount < startTickCount)
		{
			OleUninitialize();
			return 0;
		}
*/
		if (!GetMessage(&msg, NULL, 0, 0))
		{
			OleUninitialize();
			return (int)msg.wParam;
		}
#ifdef _DEBUG
//			_CrtDbgReport(_CRT_WARN, NULL, 0, NULL, "hWnd: 0x%6X msg: 0x%X\n", msg.hwnd, msg.message);
#endif // _DEBUG
		parentWindow = GetParent(msg.hwnd);
		topParent = msg.hwnd;
		while ((newParent = GetParent(topParent)) != NULL)
		{
			topParent = newParent;
		}
		if (screenSaver || !TranslateAccelerator( 
		    topParent,     // handle to receiving window 
			hAccel,        // handle to active accelerator table 
			&msg))
		{
			if (!parentWindow || !IsDialogMessage(parentWindow, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				if (screenSaver && msg.message == WM_DESTROY)
				{
					debugOut("WM_DESTROY\n", tickCount);
					PostQuitMessage(0);
				}
			}
		}
		TCAutoreleasePool::processReleases();
	}
}