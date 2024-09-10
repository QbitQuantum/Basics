	void ApplicationWindows::OnCreateInternal()
	{
		Options& opts = Core::GetOptions();
		HINSTANCE instance = ::GetModuleHandle(NULL);
		const bool windowCreated = CreateWin32Window(instance);
		if (!windowCreated)
			throw std::runtime_error("Window cannot be created.");

		//single instance check
		TCHAR fileName[MAX_PATH];
		GetModuleFileName(NULL, fileName, MAX_PATH);
		fileName[MAX_PATH - 1] = 0; //string can be not null-terminated on winXP
		for (int i = 0; i < MAX_PATH; ++i)
		{
			if (fileName[i] == L'\\') //symbol \ is not allowed in CreateMutex mutex name
				fileName[i] = ' ';
		}

		SetLastError(0);

		LPCWSTR class_name = L"Tetris";
		RegisterApplicationClass(instance, (WNDPROC)WndProc, class_name);

		// calculate client size
		RECT clientSize;
		clientSize.top = 0;
		clientSize.left = 0;
		clientSize.right = opts.width;
		clientSize.bottom = opts.height;

		ULONG style = WINDOWED_STYLE | WS_CLIPCHILDREN;
		AdjustWindowRect(&clientSize, style, FALSE);

		int realWidth = clientSize.right - clientSize.left;
		int realHeight = clientSize.bottom - clientSize.top;

		int windowLeft = -10000;
		int windowTop = -10000;

		// create window
		mh_window = CreateWindow(class_name, L"", style, windowLeft, windowTop,
			realWidth, realHeight, NULL, NULL, mh_instance, NULL);

		ShowWindow(mh_window, SW_SHOW);
		UpdateWindow(mh_window);

		// fix ugly ATI driver bugs. Thanks to ariaci (Taken from Irrlight).
		MoveWindow(mh_window, windowLeft, windowTop, realWidth, realHeight, TRUE);
		SetWindowText(mh_window, class_name);

		// move window
		clientSize.top = 0;
		clientSize.left = 0;
		clientSize.right = Core::GetOptions().width;
		clientSize.bottom = Core::GetOptions().height;

		AdjustWindowRect(&clientSize, style, FALSE);

		realWidth = clientSize.right - clientSize.left;
		realHeight = clientSize.bottom - clientSize.top;

		windowLeft = (GetSystemMetrics(SM_CXSCREEN) - realWidth) / 2;
		windowTop = (GetSystemMetrics(SM_CYSCREEN) - realHeight) / 2;
		MoveWindow(mh_window, windowLeft, windowTop, realWidth, realHeight, TRUE);

		Core::SetupRenderer(std::unique_ptr<IRenderer>(new OpenGLRenderer(mh_window, IRect())));
		auto p_renderer = Core::GetRenderer();
		p_renderer->Initialize();
		p_renderer->Reshape();

		RAWINPUTDEVICE Rid[2];
		// Keyboard
		Rid[0].usUsagePage = 0x01;
		Rid[0].usUsage = 0x06;
		Rid[0].dwFlags = 0;
		Rid[0].hwndTarget = NULL;
		// Mouse
		Rid[1].usUsagePage = 0x01;
		Rid[1].usUsage = 0x02;
		Rid[1].dwFlags = 0;
		Rid[1].hwndTarget = NULL;

		if (RegisterRawInputDevices(Rid, 2, sizeof(RAWINPUTDEVICE)) == FALSE)
			throw std::runtime_error("Cannot register input devices");

		// initialize timer
		QueryPerformanceFrequency(&liFrequency);
	}