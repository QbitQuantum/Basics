	int Create(){
		GLuint PixelFormat;
		WNDCLASS wc;
		RECT WindowRect;
		WindowRect.left = WindowRect.top = 0;
		WindowRect.right = mWidth;
		WindowRect.bottom = mHeight;

		mInstance = GetModuleHandle(NULL);
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = (WNDPROC)WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = mInstance;
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = mClassName;

		if(!RegisterClass(&wc)) return FALSE;

		AdjustWindowRectEx(&WindowRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

		mHWND = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, mClassName, mTitle, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0, 0, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top, NULL, NULL, mInstance, (LPVOID)this);

		if(!mHWND){
			Destroy();
			return FALSE;
		}

		static	PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),
			1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA,
			32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, PFD_MAIN_PLANE, 0,0, 0, 0
		};

		mHDC = GetDC(mHWND);
		if(!mHDC){
			Destroy();
			return FALSE;
		}

		PixelFormat = ChoosePixelFormat(mHDC, &pfd);
		if(!PixelFormat){
			Destroy();
			return FALSE;
		}

		if(!SetPixelFormat(mHDC, PixelFormat, &pfd)){
			Destroy();
			return FALSE;
		}

		mHRC = wglCreateContext(mHDC);

		if(!mHRC){
			Destroy();
			return FALSE;
		}

		if(!wglMakeCurrent(mHDC, mHRC)){
			Destroy();
			return FALSE;
		}

		ShowWindow(mHWND, SW_SHOW);
		SetForegroundWindow(mHWND);
		SetFocus(mHWND);
		ResizeGL(mWidth, mHeight);

		if(!InitGL()){
			Destroy();
			return FALSE;
		}

		mActive = TRUE;

		return TRUE;
	}