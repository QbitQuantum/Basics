//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		500, 500, win_width, win_height, NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		return FALSE;
	}
	// Remove borders
	SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_MINIMIZEBOX);
	SetWindowLong(hWnd, GWL_EXSTYLE, 0);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//create a ball instance
	ball = CreateWindow(L"ballclass", szTitle, WS_VISIBLE|WS_CHILD,
		184, 50, ball_diameter, ball_diameter, hWnd, NULL, GetModuleHandle(NULL), NULL);
	//make window round
	SetWindowRgn(ball,(HRGN)CreateRoundRectRgn(0,0,ball_diameter,ball_diameter,ball_diameter,ball_diameter),TRUE);
	ShowWindow(ball, nCmdShow);
	UpdateWindow(ball);
	//create a pallet instance
	pallet = CreateWindow(L"palletclass", szTitle, WS_VISIBLE|WS_CHILD,
		150, win_height-25, pallet_width, pallet_height, hWnd, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(pallet, nCmdShow);
	UpdateWindow(pallet);
	SetFocus(pallet);
	//create a pallet2 instance
	pallet2 = CreateWindow(L"pallet2class", szTitle, WS_VISIBLE|WS_CHILD,
		150, 5, pallet_width, pallet_height, hWnd, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(pallet2, nCmdShow);
	UpdateWindow(pallet2);

	return TRUE;
}