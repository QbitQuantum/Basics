void dd_init()
{
	HRESULT hr = DirectDrawCreate(NULL, &dx_dd, NULL);
	if (hr != DD_OK)
		err("Could not create DirectDraw object.");

	for(int i=16;i>0;i--)
		dd_handles.push(i);
	dd_handleCount=16;

	WNDCLASS WndClass;
	memset(&WndClass, 0, sizeof(WNDCLASS));
	WndClass.hCursor = LoadCursor(0, IDC_ARROW);
	WndClass.hIcon = LoadIcon(hMainInst, MAKEINTRESOURCE(1));
	WndClass.lpszClassName = "xerxes-dd-gamewindow";
	WndClass.hInstance = hMainInst;
	WndClass.lpfnWndProc = win_gameWindowProc;
	RegisterClass(&WndClass);

	memset(&WndClass, 0, sizeof(WNDCLASS));
	WndClass.hCursor = LoadCursor(0, IDC_ARROW);
	WndClass.lpszClassName = "xerxes-dd-auxwindow";
	WndClass.hInstance = hMainInst;
	WndClass.lpfnWndProc = win_auxWindowProc;
	RegisterClass(&WndClass);

	dd_gameWindow = new dd_Window(true);
	gameWindow = dynamic_cast<AuxWindow*>(dd_gameWindow);
	hMainWnd = dd_gameWindow->hwnd;
	dd_gameWindow->setVisibility(true);

	if(automax)
	{
		ShowWindow(dd_gameWindow->hwnd,SW_SHOWMAXIMIZED);
	}

	vid_Close = dd_Close;
	Flip = dd_Flip;
	vid_createAuxWindow = dd_createAuxWindow;
	vid_findAuxWindow = dd_findAuxWindow;
	dd_initd = true;
}