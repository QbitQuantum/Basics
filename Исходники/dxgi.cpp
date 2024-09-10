LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_SIZE:
	{
					//gWidth = LOWORD(lParam);
					//gHeight = HIWORD(wParam);
					TIMECAPS tc;
					UINT     wTimerRes;

					if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR)
					{
						// Error; application can't continue.
					}
					else
					{
						char buf[200];
						sprintf_s(buf, "\nTimer %u", tc.wPeriodMin);
						OutputDebugStringA(buf);
					}
					
					HDC hdc = GetDC(hWnd);
					gSurface = CreateCompatibleDC(hdc);

					//HDC hdc = GetDC(hWnd);

					RECT rect;
					GetWindowRect(hWnd, &rect);

					gWidth = rect.right - rect.left;
					gHeight = rect.bottom - rect.top;
					gBitmap = CreateCompatibleBitmap(hdc, gWidth, gHeight);

					gOldBitmap = (HBITMAP)SelectObject(gSurface, gBitmap);
					DeleteDC(hdc);

					SetTimer(hWnd, IDT_TIMER, 10, NULL);


					RenderInit();
					//resize the backbuffer accordingly
					//SelectObject(gSurface, gOldBitmap);


					DeleteDC(hdc);
	}
	case WM_CREATE:
	{
					  BOOL comp;
					  if (DwmIsCompositionEnabled(&comp) != S_OK)
					  {
						  exit(0);
					  }
					  
					  break;
	}

	case WM_KEYDOWN:
	{
					 RECT r = { 0, gHeight - 10,  gWidth, gHeight };
					 //ScrollWindow(gHwnd, 0, -10, NULL, NULL);
					 //startX += 10;
					 startY += 16;
					 //InvalidateRect(hWnd, NULL, FALSE);
					 Render(gSurface);
					 break;
	}
	case WM_BLIT_REQUEST:
		/*hdc = GetDC(hWnd);
		gVsyncWin->TimerBlit(hdc);
		DeleteDC(hdc);*/
		
		//gVsyncWin->TimerBlit();
		
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			//init();
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
		// TODO: Add any drawing code here...
		//Render(gSurface);
		//Rectangle(hdc, 100, 100, 500, 500);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case IDT_TIMER:
			gOldBitmap = (HBITMAP)SelectObject(gSurface, gBitmap);
			//startY += 16;
			Render(gSurface);
			SelectObject(gSurface, gOldBitmap);
			break;
		case TIMER_VSYNC:
			//gVsyncWin->TimerBlit();
			break;
		}
			
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}