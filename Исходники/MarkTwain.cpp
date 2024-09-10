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
	case WM_CREATE:
		break;
	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);

		{
			RECT cr;
			GetClientRect(hWnd, &cr);

			int width = cr.right - cr.left;
			int height = cr.bottom - cr.top;

			HDC bufDC;
			HBITMAP bufBMP;

			bufDC = CreateCompatibleDC(hdc);
			bufBMP = CreateCompatibleBitmap(hdc, width, height);
			SelectObject(bufDC, bufBMP);

			setPaintDC(bufDC);

			RECT r = {0};
			r.right = width;
			r.bottom = height;

			FillRect(bufDC, &r, GetStockBrush(WHITE_BRUSH));

			paint();

			setPaintDC(NULL);

			BitBlt(hdc, 0, 0, width, height, bufDC, 0, 0, SRCCOPY);

			DeleteObject(bufBMP);
			DeleteDC(bufDC);
		}

		EndPaint(hWnd, &ps);
		break;
	
	case WM_MOUSEMOVE:
		{
			int x = GET_X_LPARAM(lParam); 
			int y = GET_Y_LPARAM(lParam);

			mouseMove(x, y);
		}
	break;
	
	case WM_LBUTTONDOWN:
		SetCapture(hWnd);
		mouseDown();
	break;

	case WM_LBUTTONUP:
		ReleaseCapture();
		mouseUp();
	break;

	case WM_KEYDOWN:
		{
			int vk = wParam;
			char ch = MapVirtualKey(vk, MAPVK_VK_TO_CHAR);

			keyDown(ch, vk);
		}

		break;
	
	case WM_KEYUP:
		{
			int vk = wParam;
			char ch = MapVirtualKey(vk, MAPVK_VK_TO_CHAR);

			keyUp(ch, vk);
		}

		break;

	case WM_TIMER:
		switch(wParam)
		{
		case IDT_TIMER0:
			timerTick();
			break;
		}
		
		break;

	case WM_DESTROY:
		finalize();

		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}