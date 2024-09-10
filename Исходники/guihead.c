int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	int result = prepare(lpCmdLine);

	if (result == ERROR_ALREADY_EXISTS)
	{
		HWND handle = getInstanceWindow();
		ShowWindow(handle, SW_SHOW);
		SetForegroundWindow(handle);
		closeLogFile();
		return 2;
	}

	if (result != TRUE)
	{
		signalError();
		return 1;
	}

	splash = loadBool(SHOW_SPLASH)
			&& strstr(lpCmdLine, "--l4j-no-splash") == NULL;
	restartOnCrash = loadBool(RESTART_ON_CRASH);

	// if we should restart on crash, we must also stay alive to check for crashes
	stayAlive = restartOnCrash ||
			  (loadBool(GUI_HEADER_STAYS_ALIVE)
			&& strstr(lpCmdLine, "--l4j-dont-wait") == NULL);
			
	if (splash || stayAlive)
	{
		hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, "STATIC", "",
				WS_POPUP | SS_BITMAP,
				0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
		if (splash)
		{
			char timeout[10] = {0};
			if (loadString(SPLASH_TIMEOUT, timeout))
			{
				splashTimeout = atoi(timeout);
				if (splashTimeout <= 0 || splashTimeout > MAX_SPLASH_TIMEOUT)
				{
					splashTimeout = DEFAULT_SPLASH_TIMEOUT;
				}
			}
			splashTimeoutErr = loadBool(SPLASH_TIMEOUT_ERR)
					&& strstr(lpCmdLine, "--l4j-no-splash-err") == NULL;
			waitForWindow = loadBool(SPLASH_WAITS_FOR_WINDOW);
			HANDLE hImage = LoadImage(hInstance,	// handle of the instance containing the image
					MAKEINTRESOURCE(SPLASH_BITMAP),	// name or identifier of image
					IMAGE_BITMAP,					// type of image
					0,								// desired width
					0,								// desired height
					LR_DEFAULTSIZE);
			if (hImage == NULL)
			{
				signalError();
				return 1;
			}
			SendMessage(hWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hImage);
			RECT rect;
			GetWindowRect(hWnd, &rect);
			int x = (GetSystemMetrics(SM_CXSCREEN) - (rect.right - rect.left)) / 2;
			int y = (GetSystemMetrics(SM_CYSCREEN) - (rect.bottom - rect.top)) / 2;
			SetWindowPos(hWnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
			ShowWindow(hWnd, nCmdShow);
			UpdateWindow (hWnd);
		}
	}

	do
	{
		if (splash || stayAlive)
		{
			if (!SetTimer (hWnd, ID_TIMER, 1000 /* 1s */, TimerProc))
			{
				signalError();
				return 1;
			}
		}

		if (!execute(FALSE, &dwExitCode))
		{
			signalError();
			return 1;
		}

		if (!(splash || stayAlive))
		{
			debug("Exit code:\t0\n");
			closeProcessHandles();
			closeLogFile();
			return 0;
		}
	
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		if (restartOnCrash && dwExitCode != 0)
		{
	  		debug("Exit code:\t%d, restarting the application!\n", dwExitCode);
  		}

  		closeProcessHandles();
	} while (restartOnCrash && dwExitCode != 0);

	debug("Exit code:\t%d\n", dwExitCode);
	closeLogFile();
	return dwExitCode;
}