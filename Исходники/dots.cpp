//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd, 0, 1000, NULL);
		Director::getDirector().hWnd = hWnd;
		Director::getDirector().playBackgroundMusic();
		std::srand(GetTickCount64());
		
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Director::getDirector().update();
		EndPaint(hWnd, &ps); 
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		Director::getDirector().mouseDownEvent();
		break;
	case WM_LBUTTONUP:
		Director::getDirector().mouseUpEvent();
		break;
	case WM_MOUSEMOVE:
		Director::getDirector().mouseX = GET_X_LPARAM(lParam);
		Director::getDirector().mouseY = GET_Y_LPARAM(lParam);
		Director::getDirector().mouseMove();
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 0x53://S
			Director::getDirector().startGame();
			break;
		case 0x51://Q
			Director::getDirector().stopGame();
			break;
		}
		break;
	case WM_TIMER:
		
		Director::getDirector().timerEvent();
		
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}