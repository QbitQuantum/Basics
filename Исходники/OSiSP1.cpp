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
	int wmId, wmEvent,length;
	static char *str;
	static int mouseX,mouseY,menu,width,polX,polY;
	static bool polFl = true, fl = false, text=false,zoom=false;
	static float k=1;
	PAINTSTRUCT ps;
	static HDC hdc;
	HBITMAP hbmp1,hbmp2;
	HGDIOBJ hobj;
	HFONT hFont;
	static RECT r;
	static COLORREF clr;
	static HPEN hpen;
	switch (message)
	{
	case WM_CREATE:
		hdc = GetDC(hWnd);
		scrhor =3* GetDeviceCaps(hdc, HORZRES);
		scrvert =3* GetDeviceCaps(hdc, VERTRES);
		hdc1 = CreateCompatibleDC(hdc);
		hdc2 = CreateCompatibleDC(hdc);
		hbmp1 = CreateCompatibleBitmap(hdc, scrhor, scrvert);
		hbmp2 = CreateCompatibleBitmap(hdc, scrhor, scrvert);
		SelectObject(hdc1, hbmp1);
		SelectObject(hdc2, hbmp2);
		r.left = 0;
		r.top = 0;
		r.right = scrhor;
		r.bottom = scrvert;
		FillRect(hdc1, &r, (HBRUSH)CreateSolidBrush(RGB(255, 255, 255)));
		FillRect(hdc2, &r, (HBRUSH)CreateSolidBrush(RGB(255, 255, 255)));
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IM_PENCIL:
			menu = IM_PENCIL;
			break;
		case IM_LINE:
			menu = IM_LINE;
			break;
		case IM_TEXT:
			menu = IM_TEXT;
			break;
		case IM_RECTANGLE:
			menu = IM_RECTANGLE;
			break;
		case IM_COLOR:
			GetPenColor(hWnd, &clr);
			hpen = CreatePen(PS_SOLID, 1, clr);
			SelectObject(hdc, hpen);
			SelectObject(hdc1, hpen);
			SelectObject(hdc2, hpen);
			break;
		case IM_POLYLINE:
			menu = 8;
			break;
		case IM_POLYGON:
			menu = 9;
			break;
		case IM_SAVE:
			SaveEnhMetaFile(hWnd);
			break;
		case IM_OPEN:
			OpenEnhMetaFile(hWnd);
			break;
		case IM_PRINT:
			Print(hWnd);
			break;
		case IM_ELLIPSE:
			menu = IM_ELLIPSE;
			break;
		case IM_WIDTH_1:
			width = 1;
			break;
		case IM_WIDTH_2:
			width = 2;
			break;
		case IM_WIDTH_3:
			width = 3;
			break;
		case IM_WIDTH_4:
			width = 4;
			break;
		case IM_WIDTH_5:
			width = 5;
			break;
		case IM_WIDTH_6:
			width = 6;
			break;
		case IM_WIDTH_7:
			width = 7;
			break;
		case IM_WIDTH_8:
			width = 8;
			break;
		case IM_WIDTH_9:
			width = 9;
			break;
		case IM_WIDTH_10:
			width = 10;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		if (width > 0)
		{
			hpen = CreatePen(PS_SOLID, width, clr);
			SelectObject(hdc, hpen);
			SelectObject(hdc1, hpen); 
			SelectObject(hdc2, hpen);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (zoom)
		{
			StretchBlt(hdc2, scrhor/3, scrvert/3, scrhor, scrvert, hdc1, scrhor/3, scrvert/3, scrhor*k, scrvert*k, SRCCOPY);
			StretchBlt(hdc, 0, 0, scrhor, scrvert, hdc1, scrhor/3,scrvert/3, scrhor*k, scrvert*k, SRCCOPY);
		}
		else
		{
			BitBlt(hdc, 0, 0, scrhor, scrvert, hdc1, scrhor/3, scrvert/3, SRCCOPY);
		}
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_CHAR:
		if (menu == IM_TEXT && text)
		{
			length = strlen(str);
			if (wParam == 8)
			{
				str[length - 1] = '\0';
				BitBlt(hdc1, 0, 0, scrhor, scrvert, hdc2, 0, 0, SRCCOPY);
				TextOutA(hdc1, mouseX+scrhor/3, mouseY+scrvert/3, str, strlen(str));
				BitBlt(hdc, 0, 0, scrhor, scrvert, hdc2, scrhor/3, scrvert/3, SRCCOPY);
				InvalidateRect(hWnd, NULL, false);
			}
			else
			{
				if (wParam == 13)
				{
					text = false;
				}
				else
				{
					str = (char*)realloc(str, length + 2);
					length = length + 2;
					str[length - 2] = wParam;
					str[length - 1] = '\0';
					TextOutA(hdc1, mouseX+scrhor/3, mouseY+scrvert/3, str, strlen(str));
					InvalidateRect(hWnd, NULL, false);
				}
			}
		}
		break;
	case WM_KEYUP:
		if (wParam == VK_SHIFT)
		{
			zoom = false;
			k = 1;
			BitBlt(hdc1, 0, 0, scrhor, scrvert, hdc2, 0, 0, SRCCOPY);
		}
		break;
	case WM_MOUSEWHEEL:
		if (HIWORD(wParam) > WHEEL_DELTA)
		{
			if (LOWORD(wParam)==MK_SHIFT)
			{
				k = k/1.1;
				zoom = true; 
			}
			else
			{
				if (LOWORD(wParam)==MK_CONTROL)
				{
					ScrollDC(hdc1, 5, 0, &r, NULL, NULL, NULL);
					BitBlt(hdc, 0, 0, scrhor, scrvert, hdc1, scrhor/3, scrvert/3, SRCCOPY);
				}
				else
				{
					ScrollDC(hdc1, 0, 5, &r, NULL, NULL, NULL);
					BitBlt(hdc, 0, 0, scrhor, scrvert, hdc1, scrhor/3, scrvert/3, SRCCOPY);
				}
			}
		}
		else
		{
			if (LOWORD(wParam)==MK_SHIFT)
			{
				k = k*1.1;
				zoom = true;
			}
			else
			{
				if (LOWORD(wParam)==MK_CONTROL)
				{
					ScrollDC(hdc1, -5, 0, &r, NULL, NULL, NULL);
					BitBlt(hdc, 0, 0, scrhor, scrvert, hdc1, scrhor/3, scrvert/3, SRCCOPY);
				}
				else
				{
					ScrollDC(hdc1, 0, -5, &r, NULL, NULL, NULL);
					BitBlt(hdc, 0, 0, scrhor, scrvert, hdc1, scrhor/3, scrvert/3, SRCCOPY);
				}
			}
		}
		InvalidateRect(hWnd, NULL, false);
		break;
	case WM_LBUTTONDOWN:
		if (menu)
		{
			mouseX = LOWORD(lParam);
			mouseY = HIWORD(lParam);
			if (menu == IM_POLYGON && polFl)
			{
				polX = mouseX;
				polY = mouseY;
				polFl = false;
			}
			MoveToEx(hdc1, mouseX+scrhor/3, mouseY+scrvert/3, NULL); 
			MoveToEx(hdc2, mouseX+scrhor/3, mouseY+scrvert/3, NULL);
			fl = !fl;
			if (menu == IM_POLYLINE || menu==IM_POLYGON)
			{
				fl = false;
				BitBlt(hdc, 0, 0, scrhor, scrvert, hdc2, scrhor/3, scrvert/3, SRCCOPY);
				BitBlt(hdc1, 0, 0, scrhor, scrvert, hdc2, 0, 0, SRCCOPY);
			}
			if (menu == IM_TEXT)
			{
				BitBlt(hdc2, 0, 0, scrhor, scrvert, hdc1, 0, 0, SRCCOPY);
				text = true;
				str = (char*)malloc(1);
				str[0] = '\0';
			}
		}
		break;
     case WM_MOUSEMOVE:
			 if (fl)
			 {
				 hdc = GetDC(hWnd);
				 SelectObject(hdc1, hpen);
				 if (menu == IM_PENCIL)
				 {
					 mouseX = LOWORD(lParam);
					 mouseY = HIWORD(lParam);
					 LineTo(hdc1, mouseX+scrhor/3, mouseY+scrvert/3);
					 BitBlt(hdc, 0, 0, scrhor, scrvert, hdc1, scrhor/3, scrvert/3, SRCCOPY);
				 }
				 if (menu == IM_LINE)
				 {
					 BitBlt(hdc2, 0, 0, scrhor, scrvert, hdc1, 0, 0, SRCCOPY);
					 MoveToEx(hdc2, mouseX+scrhor/3, mouseY+scrvert/3, NULL);
					 LineTo(hdc2, LOWORD(lParam)+scrhor/3,HIWORD(lParam)+scrvert/3);
					 BitBlt(hdc, 0, 0, scrhor, scrvert, hdc2, scrhor/3, scrvert/3, SRCCOPY);
				 }
				 if (menu == IM_RECTANGLE)
				 {
					 BitBlt(hdc2, 0, 0, scrhor, scrvert, hdc1, 0, 0, SRCCOPY);
					 MoveToEx(hdc2, mouseX+scrhor/3, mouseY+scrhor/3, NULL);
					 hobj=SelectObject(hdc2, GetStockObject(NULL_BRUSH));
					 Rectangle(hdc2, mouseX+scrhor/3, mouseY+scrvert/3, LOWORD(lParam)+scrhor/3, HIWORD(lParam)+scrvert/3);
					 SelectObject(hdc2, hobj);
					 BitBlt(hdc, 0, 0, scrhor, scrvert, hdc2, scrhor/3, scrvert/3, SRCCOPY);
				 }
				 if (menu == IM_ELLIPSE)
				 {
					 BitBlt(hdc2, 0, 0, scrhor, scrvert, hdc1, 0, 0, SRCCOPY);
					 MoveToEx(hdc2, mouseX, mouseY, NULL); 
					 hobj=SelectObject(hdc2, GetStockObject(NULL_BRUSH));
					 Ellipse(hdc2, mouseX+scrhor/3, mouseY+scrvert/3, LOWORD(lParam)+scrhor/3, HIWORD(lParam)+scrvert/3);
					 SelectObject(hdc2, hobj);
					 BitBlt(hdc, 0, 0, scrhor, scrvert, hdc2, scrhor/3, scrvert/3, SRCCOPY);
				 }
				 if (menu == IM_POLYLINE || menu ==IM_POLYGON)
				 {
					 BitBlt(hdc2, 0, 0, scrhor, scrvert, hdc1, 0, 0, SRCCOPY);
					 MoveToEx(hdc2, mouseX+scrhor/3, mouseY+scrvert/3, NULL);
					 LineTo(hdc2, LOWORD(lParam)+scrhor/3, HIWORD(lParam)+scrvert/3);
					 BitBlt(hdc, 0, 0, scrhor, scrvert, hdc2, scrhor/3, scrvert/3, SRCCOPY);
				 }
			 }
		break;
	 case WM_LBUTTONUP:
		 if (menu == IM_LINE || menu == IM_RECTANGLE || menu == IM_ELLIPSE)
		 {
			 BitBlt(hdc1, 0, 0, scrhor, scrvert, hdc2, 0, 0, SRCCOPY);
			 BitBlt(hdc, 0, 0, scrhor, scrvert, hdc2, scrhor/3, scrvert/3, SRCCOPY);
		 }
		 if (menu == IM_POLYLINE || menu ==IM_POLYGON)
		 {
			 fl = false;
			 
		 }
		 fl = !fl;
		 break;
	 case WM_RBUTTONDOWN:
		 if (menu == IM_POLYLINE || menu==IM_POLYGON)
		 {
			 fl = false;
			 BitBlt(hdc, 0, 0, scrhor, scrvert, hdc2, scrhor/3, scrvert/3, SRCCOPY);
			 BitBlt(hdc1, 0, 0, scrhor, scrvert, hdc2, 0, 0, SRCCOPY); 
		 }
		 if (menu == IM_POLYGON)
		 {
			 LineTo(hdc2, polX+scrhor/3, polY+scrvert/3);
			 BitBlt(hdc, 0, 0, scrhor, scrvert, hdc2, scrhor/3, scrvert/3, SRCCOPY);
			 BitBlt(hdc1, 0, 0, scrhor, scrvert, hdc2, 0, 0, SRCCOPY);
			 polFl = true;
		 }
		 break;
	case WM_DESTROY:
		ReleaseDC(hWnd, hdc);
		ReleaseDC(hWnd, hdc1);
		ReleaseDC(hWnd, hdc2);
		PostQuitMessage(0); 
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}