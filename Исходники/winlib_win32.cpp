GHL_API int GHL_CALL GHL_StartApplication( GHL::Application* app,int argc, char** argv)
{
	(void)argc;
	(void)argv;

	OSVERSIONINFO	os_ver;
	SYSTEMTIME		tm;
	MEMORYSTATUS	mem_st;

	GetLocalTime(&tm);
	char buf[256];
	sprintf(buf,"Date: %02d.%02d.%d, %02d:%02d:%02d",tm.wDay, tm.wMonth, tm.wYear, tm.wHour, tm.wMinute, tm.wSecond);
	LOG_INFO( buf );

	os_ver.dwOSVersionInfoSize=sizeof(os_ver);
	GetVersionEx(&os_ver);
	sprintf(buf,"OS: Windows %ld.%ld.%ld",os_ver.dwMajorVersion,os_ver.dwMinorVersion,os_ver.dwBuildNumber);
	LOG_INFO( buf );
	GlobalMemoryStatus(&mem_st);
	sprintf(buf,"Memory: %ldK total, %ldK free",mem_st.dwTotalPhys/1024L,mem_st.dwAvailPhys/1024L);
	LOG_INFO( buf );


	
	GHL::VFSWin32Impl vfs;
	app->SetVFS(&vfs);

	GHL::ImageDecoderImpl image;
	app->SetImageDecoder(&image);

	HINSTANCE hInstance = GetModuleHandle(0);
	WNDCLASS		winclass;
	{
		winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		winclass.lpfnWndProc	= &WindowProc;
		winclass.cbClsExtra		= 0;
		winclass.cbWndExtra		= 0;
		winclass.hInstance		= hInstance;
		winclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
		winclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
		winclass.lpszMenuName	= NULL;
		winclass.lpszClassName	= WINDOW_CLASS_NAME;
		winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		if (!RegisterClass(&winclass)) {
			LOG_ERROR( "Can't register window class" );
			return 1;
		}
	}
	GHL::Settings settings;
	settings.width = 800;
	settings.height = 600;
	settings.fullscreen = false;
	app->FillSettings(&settings);

	RECT rect_w;
	rect_w.left      =   GetSystemMetrics(SM_CXSCREEN)/2 - settings.width/2;
	rect_w.top       =   GetSystemMetrics(SM_CYSCREEN)/2 - settings.height/2;
	rect_w.right     =   rect_w.left + settings.width;
	rect_w.bottom    =   rect_w.top  + settings.height;
	DWORD style_w =   WS_POPUP|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_VISIBLE; //WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;
 
	AdjustWindowRect(&rect_w,style_w,false);

	/*m_rect_fs.left=0;
	m_rect_fs.top=0;
	m_rect_fs.right=m_width;
	m_rect_fs.bottom=m_height;
	m_style_fs=WS_POPUP|WS_VISIBLE; 
	*/

	HWND hwndParent = 0; /// @todo
	HWND hwnd = 0;
	//if(!settings.fullscreen)

		hwnd = CreateWindowEx(0, WINDOW_CLASS_NAME, TEXT("Test"), style_w,
				rect_w.left, rect_w.top, rect_w.right-rect_w.left, 
				rect_w.bottom-rect_w.top,
				hwndParent, NULL, hInstance, NULL);
	/*else
		m_hwnd = CreateWindowExA(WS_EX_TOPMOST, WINDOW_CLASS_NAME, "Test", m_style_fs,
				0, 0, 0, 0,
				NULL, NULL, hInstance, NULL);*/
	if (!hwnd)
	{
		LOG_ERROR( "Can't create window" );
		return 1;
	}

#ifndef GHL_NO_SOUND
	GHL::SoundDSound sound(8);
	if (!sound.SoundInit(hwnd)) {
		LOG_ERROR( "Can't init sound" );
		return 1;
	}
	app->SetSound(&sound);
#endif

	Win32System sys(hwnd);
	app->SetSystem(&sys);

	g_proxy.Register();
	app->SetPlatformProxy(&g_proxy);

	HDC hDC = GetDC (hwnd);
	if (!hDC) {
		DestroyWindow(hwnd);
		return 1;
	}

	PIXELFORMATDESCRIPTOR pfd =											// pfd Tells Windows How We Want Things To Be
	{
		sizeof (PIXELFORMATDESCRIPTOR),									// Size Of This Pixel Format Descriptor
		1,																// Version Number
		PFD_DRAW_TO_WINDOW |											// Format Must Support Window
		PFD_SUPPORT_OPENGL |											// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,												// Must Support Double Buffering
		PFD_TYPE_RGBA,													// Request An RGBA Format
		32,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,												// Color Bits Ignored
		0,																// No Alpha Buffer
		0,																// Shift Bit Ignored
		0,																// No Accumulation Buffer
		0, 0, 0, 0,														// Accumulation Bits Ignored
		24,																// 16Bit Z-Buffer (Depth Buffer)  
		8,																// No Stencil Buffer
		0,																// No Auxiliary Buffer
		PFD_MAIN_PLANE,													// Main Drawing Layer
		0,																// Reserved
		0, 0, 0															// Layer Masks Ignored
	};

	int PixelFormat = ChoosePixelFormat (hDC, &pfd);				// Find A Compatible 

	if (PixelFormat == 0)												// Did We Find A Compatible Format?
	{
		// Failed
		ReleaseDC (hwnd, hDC);							// Release Our Device Context
		hDC = 0;												// Zero The Device Context
		DestroyWindow (hwnd);									// Destroy The Window
		hwnd = 0;												// Zero The Window Handle
		return 1;													// Return False
	}

	if (SetPixelFormat (hDC, PixelFormat, &pfd) == FALSE)		// Try To Set The Pixel Format
	{
		// Failed
		ReleaseDC (hwnd, hDC);							// Release Our Device Context
		hDC = 0;												// Zero The Device Context
		DestroyWindow (hwnd);									// Destroy The Window
		hwnd = 0;												// Zero The Window Handle
		return 1;													// Return False
	}

	HGLRC hRC = wglCreateContext(hDC);

	if (hRC == 0)												// Did We Get A Rendering Context?
	{
		// Failed
		ReleaseDC (hwnd, hDC);							// Release Our Device Context
		hDC = 0;												// Zero The Device Context
		DestroyWindow (hwnd);									// Destroy The Window
		hwnd = 0;												// Zero The Window Handle
		return 1;													// Return False
	}
	SetWindowLongPtr(hwnd,GWLP_USERDATA,(LONG_PTR)app);

	if (wglMakeCurrent (hDC, hRC) == FALSE)
	{
		// Failed
		wglDeleteContext (hRC);									// Delete The Rendering Context
		hRC = 0;												// Zero The Rendering Context
		ReleaseDC (hwnd, hDC);							// Release Our Device Context
		hDC = 0;												// Zero The Device Context
		DestroyWindow (hwnd);									// Destroy The Window
		hwnd = 0;												// Zero The Window Handle
		return 1;													// Return False
	}

	ShowWindow(hwnd, SW_SHOW);
	

	wglMakeCurrent (hDC, hRC);

	GHL::RenderOpenGL render(settings.width,settings.height);
	render.RenderInit();
	app->SetRender(&render);

	app->Initialize();
	//GHL_DispatchPlatformEvent(&g_proxy, "platform:app_init_done", 0);

	if (!app->Load())
		return 1;

	bool done = false;
	timeBeginPeriod(1);
	DWORD ms = timeGetTime();
	while (!done) {
	/*
	if (m_input)
		m_input->Update();
		*/
#ifndef GHL_NO_SOUND
		sound.Process();
#endif

		MSG		msg;
		while (PeekMessage(&msg,hwnd,0,0,PM_REMOVE) && !done)
		{
			if (msg.message == WM_QUIT) {
				done = true;
				if (app) {
					app->Release();
					app = 0;
				}
				render.RenderDone();
#ifndef GHL_NO_SOUND
				sound.SoundDone();
#endif
				LOG_INFO( "Done" );
				break;
			} else
				DispatchMessage(&msg);
		}
		if (app) {	
			wglMakeCurrent (hDC, hRC);
			DWORD now = timeGetTime();
			DWORD dt = now - ms;
			ms = now;
			//if (dt>1000)
			//	dt = 1000;
			app->OnFrame(dt);
			SwapBuffers (hDC);
			Sleep(1);
		}
	}
	timeEndPeriod(1);
	
	return 0;
}