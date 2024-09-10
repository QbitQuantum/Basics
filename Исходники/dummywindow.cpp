		DummyWindow::DummyWindow(HINSTANCE hinstance)
		{
			this->hinstance = hinstance;

			WCHAR classname[sizeof(DummyWindow*) * 2 + 1];
			win32::genClassNameStr(this, classname);

			WNDCLASSEXW klass;
			klass.cbSize = sizeof(WNDCLASSEXW);
			klass.style = CS_OWNDC;
			klass.lpfnWndProc = &wndproc;
			klass.cbClsExtra = 0;
			klass.cbWndExtra = 0;
			klass.hInstance = hinstance;
			klass.hIcon = 0;
			klass.hCursor = 0;
			klass.hbrBackground = 0;
			klass.lpszMenuName = 0;
			klass.lpszClassName = &classname[0];
			klass.hIconSm = 0;

			classatom = RegisterClassExW(&klass);
			if(!classatom)
				throw Exception("Can't register win32 window class: " + win32::getErrorMsg());

			hwnd = CreateWindowExW(
				0,
				&classname[0],
				L"",	// window title
				WS_POPUP | WS_DISABLED,
				CW_USEDEFAULT, CW_USEDEFAULT,
				100, 100, // width, height
				0,
				0,
				hinstance,
				0);

			if(!hwnd)
			{
				DWORD err = GetLastError();
				UnregisterClassW(&classname[0], hinstance);
				throw wm::Exception("Can't create Window: " + wm::win32::getErrorMsg(err));
			}
		}