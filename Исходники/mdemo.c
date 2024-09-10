LRESULT CALLBACK
WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	PAINTSTRUCT	ps;
	HDC		hdc;
#if CLIENT3D | IMAGE | GRAPH3D
	RECT		rc;
#endif
#if GRAPH3D
	static int	countup = 1;
	int		id;
	static vec1 	gx, gy;
#endif
#if TIMERDEMO
	static POINT	mousept;
#endif
#if ARCDEMO
	static int	startdegrees = 0;
	static int	enddegrees = 30;
#endif

	switch( msg) {
#if TIMERDEMO
	case WM_CREATE:
		SetTimer(hwnd, 1, 100, NULL);
		mousept.x = 60;
		mousept.y = 20;
		break;

	case WM_TIMER:
#if GRAPH3D
		GetClientRect(hwnd, &rc);
		if(countup) {
			mousept.y += 20;
			if(mousept.y >= rc.bottom) {
				mousept.y -= 20;
				countup = 0;
			}
		} else {
			mousept.y -= 20;
			if(mousept.y < 20) {
				mousept.y += 20;
				countup = 1;
			}
		}
		SendMessage(hwnd, WM_MOUSEMOVE, 0,
			MAKELONG(mousept.x, mousept.y));
#endif
#if ARCDEMO
		startdegrees += 10;
		if(startdegrees >= 360)
			startdegrees = 0;
		enddegrees += 15;
		if(enddegrees >= 360)
			enddegrees = 0;
		InvalidateRect(hwnd, NULL, TRUE);
#endif
		break;

	case WM_DESTROY:
		KillTimer(hwnd, 1);
		break;
#endif /* TIMERDEMO*/
	case WM_SIZE:
		break;

	case WM_MOVE:
		break;

#if CLIENT3D
	case WM_SETFOCUS:
		PostMessage((HWND)wp, WM_PAINT, 0, 0L);
		break;

	case WM_KILLFOCUS:
		PostMessage((HWND)wp, WM_PAINT, 0, 0L);
		break;
	case WM_ERASEBKGND:
		if(GetFocus() != hwnd)
			return DefWindowProc(hwnd, msg, wp, lp);
		return 1;
#endif
#if GRAPH3D
	case WM_ERASEBKGND:
		if((GetWindowLong(hwnd, GWL_ID) & 03) == 1)
			return 1;
		return DefWindowProc(hwnd, msg, wp, lp);
#endif
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

#if CLIENT3D
		if(GetFocus() == hwnd) {
			GetClientRect(hwnd, &rc);
			Draw3dShadow(hdc, rc.left, rc.top,
				rc.right-rc.left, rc.bottom-rc.top,
				GetSysColor(COLOR_3DDKSHADOW),
				GetSysColor(COLOR_3DLIGHT));
			InflateRect(&rc, -1, -1);
			FillRect(hdc, &rc, GetStockObject(GRAY_BRUSH));
		}
#endif
#if IMAGE
		GetClientRect(hwnd, &rc);
		DrawDIB(hdc, rc.left+2, rc.top+2, image2);
#endif
#if ARCDEMO
{
	int x, y, w, h;
	RECT rc;

	if(hdc != NULL) {
		GetWindowRect(hwnd, &rc);
		rc.top += 13;
		InflateRect(&rc, -3, -3);
		/*Ellipse(hdc, 0, 0, rc.right-rc.left, rc.bottom-rc.top);*/
		/*Arc(hdc, 0, 0, rc.right-rc.left, rc.bottom-rc.top, 0,0, 0,0);*/
		/*Pie(hdc, 0, 0, rc.right-rc.left, rc.bottom-rc.top, 0,0, 0,0);*/

		x = rc.left;
		y = rc.top;
		w = rc.right - rc.left;
		h = rc.bottom - rc.top;
		w += 10;
		GdSetForeground(GdFindColor(RGB(0,255,0)));
		GdArcAngle(hdc->psd, x+w/2, y+h/2, w/2, h/2, startdegrees*64,
			enddegrees*64, MWPIE);
		GdSetForeground(GdFindColor(RGB(0,0,0)));
		GdArcAngle(hdc->psd, x+w/2, y+h/2, w/2, h/2, startdegrees*64,
			enddegrees*64, MWARCOUTLINE);
		/*GdSetForeground(GdFindColor(RGB(255,255,255)));*/
		/*GdPoint(hdc->psd, x+w/2, y+h/2);*/
	}
	EndPaint(hwnd, &ps);
	break;
}
#endif /* ARCDEMO*/
#if GRAPH3D
		id = (int)GetWindowLong(hwnd, GWL_ID) & 03;
		init3(hdc, id == 1? hwnd: NULL);
		switch(id) {
		case 0:
			rose(1.0, 7, 13);
			break;
		case 1:
			/*look3(0.5, 0.7, 1.5);*/
			/*look3(0.2, -2 * gy, 1.0+gx);*/
			look3(-2 * gx, -2 * gy, 1.2);
			drawgrid(-8.0, 8.0, 10, -8.0, 8.0, 10);
			break;
		case 2:
			setcolor3(BLACK);
			circle3(1.0);
			break;
		case 3:
			setcolor3(BLUE);
			daisy(1.0, 20);
			break;
		}

#if CLIPDEMO
		if(id == 1) {
			HRGN	hrgn, hrgn2;

			/* create circular clip region for effect*/
			GetClientRect(hwnd, &rc);
			InflateRect(&rc, -80, -80);
			switch((int)GetWindowLong(hwnd, GWL_ID)) {
			default:
				hrgn = CreateEllipticRgnIndirect(&rc);
				break;
			case 5:
				hrgn = CreateRoundRectRgn(rc.left, rc.top,
					rc.right, rc.bottom, 100, 100);
				break;
			case 1:
				hrgn = CreateRectRgnIndirect(&rc);
				break;
			}

			/* erase background, clip out blit area*/
			GetClientRect(hwnd, &rc);
			hrgn2 = CreateRectRgnIndirect(&rc);
			SelectClipRgn(hdc, hrgn2);
			ExtSelectClipRgn(hdc, hrgn, RGN_XOR);
			DeleteObject(hrgn2);

			GetClientRect(hwnd, &rc);
			FillRect(hdc, &rc, GetStockObject(BLACK_BRUSH));

			/* clip in only blit area*/
			SelectClipRgn(hdc, hrgn);
			DeleteObject(hrgn);
		}
#endif /* CLIPDEMO*/

		paint3(hdc);

#endif /* GRAPH3D*/
		EndPaint(hwnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_MOUSEMOVE:
#if GRAPH3D
		if((GetWindowLong(hwnd, GWL_ID) & 03) == 1) {
			POINT pt;

			POINTSTOPOINT(pt, lp);
			GetClientRect(hwnd, &rc);
			gx = (vec1)pt.x / rc.right;
			gy = (vec1)pt.y / rc.bottom;
			InvalidateRect(hwnd, NULL, FALSE);
			mousept.x = pt.x;
			mousept.y = pt.y;
		}
#endif
		break;

	case WM_LBUTTONUP:
		break;

	case WM_RBUTTONDOWN:
		break;

	default:
		return DefWindowProc( hwnd, msg, wp, lp);
	}
	return( 0);
}