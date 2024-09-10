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
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		::TextOut(hdc, 10, 10, L"Arrow keys to turn.", 19);
		::SetTextColor(hdc, RGB(200,0,0));
		::TextOut(hdc, 10, 25, L"Red = Original;", 15);
		::SetTextColor(hdc, RGB(0,0,255));
		::TextOut(hdc, 120, 25, L"Blue = Extrapolated", 19);
		::SetTextColor(hdc, RGB(0,0,0));
		{
		  wchar_t buf[100];
		  _snwprintf(buf, 100, L"Latency %d ms Jitter %d ms Droprate %d%%", (int)(LATENCY*1000), (int)(JITTER*1000),
		      (int)(DROPRATE*100));
		  buf[99] = 0;
		  ::TextOut(hdc, 10, 40, buf, (INT)wcslen(buf));
		}
		::TextOut(hdc, 10, 55, L"F2: change draw mode", 20);
		::TextOut(hdc, 10, 70, L"F3: pause/go", 12);
		::TextOut(hdc, 10, 85, L"F4: single step", 15);
		if (gPaused) {
		  ::SetTextColor(hdc, RGB(255,0,0));
		  ::TextOut(hdc, 300, 10, L"PAUSED", 6);
		  ::SetTextColor(hdc, RGB(0,0,0));
		}
		if (gPointDisplay) {
		  ::TextOut(hdc, 300, 25, L"POINTS", 6);
		}
		else {
		  ::TextOut(hdc, 300, 25, L"LINES", 5);
		}
    DrawWindow(hWnd, hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		gRunning = false;
		break;

  case WM_SYSKEYDOWN:
  case WM_KEYDOWN:
    keyDown[wParam&0xff] = true;
    break;
  case WM_SYSKEYUP:
  case WM_KEYUP:
    keyDown[wParam&0xff] = false;
    break;
  case WM_ACTIVATEAPP:
    gActive = (wParam != 0);
    memset(keyDown, 0, sizeof(keyDown));
    break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}