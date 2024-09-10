bool Application::Birth()
{
	CoInitializeEx(NULL,NULL);
	Globals.Exiting	=	false;
	srand(GetTickCount());
	Input::I = new Input::Input_t;
	//===[ КОНФИГУРАЦИЯ ]===========================================================================
		ReadConfig();
	//===[ КОНФИГУРАЦИЯ ]===========================================================================	
	CCons.INIT();
#ifdef WIN32
	WNDCLASSEX wc;
	DWORD dwExStyle;
	DWORD dwStyle;
	RECT WindowRect;

	WindowRect.left = 0L;
	WindowRect.top	= 0L;
	WindowRect.right = Globals.VP.Width;
	WindowRect.bottom = Globals.VP.Height;

	Application::Vars.App.HInstance = GetModuleHandle(NULL);
	memset(&wc,0,sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = Application::Vars.App.HInstance;
	wc.hIcon = LoadIcon(Application::Vars.App.HInstance,MAKEINTRESOURCE(IDI_ICON1));
	wc.hIconSm = LoadIcon(Application::Vars.App.HInstance,MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+2);//NULL;
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = MY_WINDOW_CLASS_NAME;

	FASSERT(RegisterClassEx(&wc));
	if(IsFullScreen)
	{
		EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&Application::Vars.win.PrevDS);
		memset(&Application::Vars.win.CurrDS, 0, sizeof(Application::Vars.win.CurrDS));
		Application::Vars.win.CurrDS.dmSize = sizeof(Application::Vars.win.CurrDS);
		Application::Vars.win.CurrDS.dmPelsWidth = Globals.VP.Width;
		Application::Vars.win.CurrDS.dmPelsHeight = Globals.VP.Height;
		Application::Vars.win.CurrDS.dmBitsPerPel = Globals.VP.Bits;
		Application::Vars.win.CurrDS.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT|DM_DISPLAYFREQUENCY;
		Application::Vars.win.CurrDS.dmDisplayFrequency=Globals.VP.Hzs;

		if(ChangeDisplaySettings(&Application::Vars.win.CurrDS,CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			if(MessageBox(0, "Cannot run in fullscreen mode!\nRun in window?",
				"Hardware trouble!", MB_YESNO|MB_ICONEXCLAMATION) == IDYES)
			{
				IsFullScreen = false;
			}
			else 
			{
				MessageBox(0, "OK!!! I'm quit...", "!!!", MB_OK | MB_ICONQUESTION);
				PostQuitMessage(1);
				return NO_ERROR;
			};
		};
	};

	if(IsFullScreen)
	{
			dwExStyle	= WS_EX_APPWINDOW/* | WS_EX_TOPMOST*/; // WS_EX_TOPMOST - Поверх всех окон
			dwStyle		= WS_POPUP;
	}
	else
	{
// ВНИМАНИЕ Здесь обнаружены глюки при использовании nView от nVidia!
			dwExStyle	= WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			dwStyle		= WS_OVERLAPPEDWINDOW;
	};
	ShowCursor(false);
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);
	if (WindowRect.left < 0)
		WindowRect.right -= WindowRect.left,WindowRect.left = 0;
	if (WindowRect.top < 0)
		WindowRect.bottom -= WindowRect.top,WindowRect.top = 0;
	Application::Vars.win.MHWnd =
			CreateWindowEx(		dwExStyle, 
								MY_WINDOW_CLASS_NAME,
								MY_WINDOW_NAME,
								dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
								WindowRect.left,
								WindowRect.top,
								WindowRect.right - WindowRect.left,
								WindowRect.bottom - WindowRect.top,
								NULL,
								NULL,
								GetModuleHandle(0),
								NULL
								);
	FASSERT(Application::Vars.win.MHWnd);
	ShowWindow(Application::Vars.win.MHWnd, SW_SHOW);
	SetForegroundWindow(Application::Vars.win.MHWnd);
	SetFocus(Application::Vars.win.MHWnd);

	// Получаем контекст устройства
	Application::Vars.win.DC = GetDC(Application::Vars.win.MHWnd);
		FASSERT(Application::Vars.win.DC);
	// Установка формата пикселей
		PIXELFORMATDESCRIPTOR mainPFD;
		memset(&mainPFD,0,sizeof(PIXELFORMATDESCRIPTOR));
		mainPFD.nSize			= sizeof(PIXELFORMATDESCRIPTOR);
		mainPFD.nVersion		= 1;
		mainPFD.iPixelType		= PFD_TYPE_RGBA;
		mainPFD.dwFlags			= PFD_DRAW_TO_WINDOW |PFD_DOUBLEBUFFER |PFD_SUPPORT_OPENGL;
		mainPFD.iLayerType		= PFD_MAIN_PLANE;
		mainPFD.cDepthBits		=	16;
		int PF;
		PF = ChoosePixelFormat(Application::Vars.win.DC,&mainPFD);
		FASSERT(PF);	// Выбрали!
		FASSERT(SetPixelFormat(Application::Vars.win.DC,PF,&mainPFD));			// Поставили!
	// Создание контекста рендера
		Application::Vars.win.RC = wglCreateContext (Application::Vars.win.DC);
		FASSERT(Application::Vars.win.RC);
	// Установка полученого контекста главным
		FASSERT(wglMakeCurrent (Application::Vars.win.DC, Application::Vars.win.RC));
#else
		dpy = XOpenDisplay(0);						// Открываем дисплей по-умолчанию (может быть сетевой)
		vi = glXChooseVisual(	dpy,				// Получаем подходящий визуал
								DefaultScreen(dpy),
								attributeList);
		cx = glXCreateContext(dpy, vi, 0, GL_TRUE);	// Создание контекста
		// create	a color	map
		cmap = XCreateColormap(dpy, RootWindow(dpy, vi->screen),
				 vi->visual, AllocNone);
		// Создаём окно
		swa.colormap = cmap;
		swa.border_pixel = 0;
		swa.event_mask = StructureNotifyMask;
		win = XCreateWindow(dpy, RootWindow(dpy, vi->screen), 0, 0, 100, 100,
			  0, vi->depth,	InputOutput, vi->visual,
			  CWBorderPixel|CWColormap|CWEventMask,	&swa);
		XMapWindow(dpy, win);
		XIfEvent(dpy, &event, WaitForNotify, (char*)win);

		
		glXMakeCurrent(dpy, win, cx);				// Привязка контекста к окну
#endif
		GetSysInfo();
#ifndef	_DEBUG
		if (AVIp.Open("data/VIDEO/logo.avi") == FJC_NO_ERROR)
		{
			AVIp.Caching();
			GT.Start();
			ShowMovie(true);
			AVIp.CloseAVI();
		}
		else
		{
			LF.Logf("Birth","Невозможно загрузить и проиграть заставку");
		}
#endif
	// Инициализация библиотек и глобальных объектов
		InitOpenGL();						// Графика - OpenGL
		LF.Log("BIRTH","Init OpenGL complete");
		InitOpenIL();						// Поддержка изображений - OpenIL(DevIL)
		LF.Log("BIRTH","Init OpenIL complete");
// инициализация менеджера ресурсов		
		rm.INIT("Consolas.LFont","default.png","cube.lwo");
		CCons.SetFont(rm.SELECT_Font("Console"));

		SimpleLogo.init(&SwapBuffersEXT,IL_PNG,"data/textures/Logos/NewLOGO.PNG");
		SimpleLogo.render_logo(FJC_STARTUP_LOGO_MODE_BEGIN);
		rm.SELECT_Font("Courier")->SetColor(1,0,0);
		SimpleLogo.render_logo(	FJC_STARTUP_LOGO_MODE_PROCEED_WITH_TEXT,1,
								TextBlock(rm.SELECT_Font("Consolas"),"Now loading, please wait",250.0f,300.0f));
		Sound.Init();
		TestBuf.Init();
		TestBuf.LoadWav("data/sounds/KDE_Startup_new2.wav");
		TestSource.Init();
		TestSource.LinkWithBufer(&TestBuf);
		LF.Log("BIRTH","Init OpenAL complete");
		InitMATH();							// Математическая библиотека
		LF.Log("BIRTH","InitMATH");
		LF.Msg("Init complete");
		LoadResources();
		PS.INIT();
	return NO_ERROR;
};