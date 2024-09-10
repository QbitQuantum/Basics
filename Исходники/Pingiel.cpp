int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW |CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(PINGIEL_ICON));
	wc.hCursor = 0;
	wc.hbrBackground = 0;
	wc.lpszMenuName = MAKEINTRESOURCE(PINGIEL_MENU);
	wc.lpszClassName = "PingielClass";

	if (!RegisterClass(&wc))	
		return false;

	MessageBox(0, "hejo", "okienko", MB_OK);

	int horizontal=GetSystemMetrics(16);
	int vertical = GetSystemMetrics(17);

	HWND hWnd = CreateWindow(wc.lpszClassName, "Okno", WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, 0, 0,horizontal, vertical, NULL, NULL, hInstance, NULL);
	if (hWnd == NULL)
		return false;

	static PIXELFORMATDESCRIPTOR pfd=  //struktura formatu pixeli
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,//numerwersji
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		16,//tryb koloru
		0,0,0,0,0,0,//ignorowane bity koloru
		0,//brak kanalu alpha
		0,//ignorowanie rpzesuniecia
		0,//brak akumulatora
		0,0,0,0,//ignorowane przesuniecie akumulatora
		16,//16bitowy bufor glebokosci
		0,//no stencil buffer
		0,//no auxiliary buffer
		PFD_MAIN_PLANE,//glowna warstwa rysowania
		0,//zarezerwowane
		0,0,0//ignorowanie warstwy maski

	};

	HDC hDC = NULL;//kontekst urzadzenia
	HGLRC hRC = NULL;//kontekst renderowania
	GLuint PixelFormat;//styl pixeli

	if (!(hDC = GetDC(hWnd))) return 0;//pobranie kontekstu
	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))return 0;//wyszukiwanie formatu pixeli
	if (!SetPixelFormat(hDC, PixelFormat, &pfd)) return 0;//ust. formatu pixeli
	if (!(hRC = wglCreateContext(hDC)))return 0;//pobvranie kontekstu renderowania
	if (!wglMakeCurrent(hDC, hRC))return 0; //uruchomienie kontekstu renderowania

	ShowWindow(hWnd, iCmdShow);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
									// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}
	BOOL done = false;
	MSG msg;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))//czy jest zdarzenie do obslugi?
		{
			if (msg.message == WM_QUIT) done = TRUE;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			DrawGLScene();
			SwapBuffers(hDC);
		}
		
		
	}
	if (hRC)
	{
		wglMakeCurrent(NULL, NULL);//usuw. kontekstu rend.
		wglDeleteContext(hRC);//usuw. kontekstu rend.
		hRC = NULL;//wyzerowanie kontekstu rend.
	}
	if (hDC && !ReleaseDC(hWnd, hDC)) { hDC = NULL; }//wyzerowanie kontekstu
	if (hWnd&& !DestroyWindow(hWnd)){ hWnd = NULL; }//wyzerowanie uchwytu okienka

	return 0;
}