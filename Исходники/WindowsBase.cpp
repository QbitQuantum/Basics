	StaticWindowManager()
	{
		if (!gWindowClassInitialized)
		{
			HINSTANCE instance = (HINSTANCE)GetModuleHandle(NULL);
			memset(&gWindowClass, 0, sizeof(gWindowClass));
			gWindowClass.style = 0;
			gWindowClass.lpfnWndProc = WinProc;
			gWindowClass.hInstance = instance;
			gWindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			gWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			gWindowClass.lpszClassName = CONFETTI_WINDOW_CLASS;

			gAppRunning = RegisterClassW(&gWindowClass) != 0;

			if (!gAppRunning)
			{
				//Get the error message, if any.
				DWORD errorMessageID = ::GetLastError();

				if (errorMessageID != ERROR_CLASS_ALREADY_EXISTS)
				{
					LPSTR messageBuffer = nullptr;
					size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
					String message(messageBuffer, size);
					ErrorMsg(message.c_str());
					return;
				}
				else
				{
					gAppRunning = true;
					gWindowClassInitialized = gAppRunning;
				}
			}

			RAWINPUTDEVICE Rid[2];

			Rid[0].usUsagePage = 0x01;
			Rid[0].usUsage = 0x02;
			Rid[0].dwFlags = 0;	// adds HID mouse and also ignores legacy mouse messages
			Rid[0].hwndTarget = 0;

			Rid[1].usUsagePage = 0x01;
			Rid[1].usUsage = 0x06;
			Rid[1].dwFlags = 0;	// adds HID keyboard and also ignores legacy keyboard messages
			Rid[1].hwndTarget = 0;

			if (RegisterRawInputDevices(Rid, 2, sizeof(Rid[0])) == FALSE)
			{
				LOGERRORF("Failed to register raw input devices");
				//registration failed. Call GetLastError for the cause of the error
			}
		}

		collectMonitorInfo();
	}