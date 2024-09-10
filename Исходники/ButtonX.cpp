	int CALLBACK ButtonX::windowProc(HWND hwnd , int message , WPARAM wParam, LPARAM lParam) {
		switch(message) {

		case WM_SETTEXT:
			ButtonX::fromHWND(hwnd)->_text = (char*) lParam;
			//break;
			return 0;
		case WM_GETTEXT:
			if (ButtonX::fromHWND(hwnd)->_duringPaint) {
				((char*)lParam)[0] = 0;
				return 0;
			}
			//break;
			//			strncpy((char*) lParam,ButtonX::fromHWND(hwnd)->_text , wParam);
			strncpy((char*) lParam,ButtonX::fromHWND(hwnd)->_text , wParam);
			return min(ButtonX::fromHWND(hwnd)->_text.length(), wParam-1);
		case WM_GETTEXTLENGTH:
			if (ButtonX::fromHWND(hwnd)->_duringPaint) return 0;
			//break;
			return ButtonX::fromHWND(hwnd)->_text.length();

		case WM_PAINT: {
			ButtonX * bt = ButtonX::fromHWND(hwnd);
			//if (!bt->_icon) break; // standardowa obs³uga...
			//int r = 1;
			HRGN hrgn=CreateRectRgn(0, 0, 0, 0);
			bt->_duringPaint=true;
			GetUpdateRgn(hwnd, hrgn, false);
			int r = 1;
			if (!bt->isFlat()) {
				r = CallWindowProc(ButtonX::buttonClassProc, hwnd, message, wParam, lParam);
			}
			InvalidateRgn(hwnd, hrgn, false);

			PAINTSTRUCT ps;
			HDC hdc;
			hdc = BeginPaint(hwnd, &ps);
			if (bt->isFlat()) {
				FillRgn(hdc, hrgn, GetSysColorBrush(COLOR_BTNFACE));
			}
			RECT rc = {0,0,0,0};
			bt->drawCaption(hdc, rc);
			EndPaint(hwnd, &ps);
			bt->_duringPaint=false;
			DeleteObject(hrgn);
			return r;}
		case WM_ENABLE: case WM_UPDATEUISTATE: {
			int r = CallWindowProc(ButtonX::buttonClassProc, hwnd, message, wParam, lParam);
			repaintWindow(hwnd);
			return r;}
		case WM_ERASEBKGND:
			return 0;

		case WM_SETFOCUS:
		//case BM_SETSTYLE:
		case BM_SETSTATE:
			// specjalnie dla W98
			repaintWindow(hwnd);
			break;

		case WM_SETCURSOR:
			if (fromHWND(hwnd)->isFlat()) {
				SetCursor( LoadCursor(0, IDC_HAND) );
				return true;
			}
			break;

#ifndef STAMINA_KISS
		case WM_LBUTTONDOWN: {
			ButtonX* b = fromHWND(hwnd);
			S_ASSERT(b);
			b->_pressed = true;
			b->evtMouseDown(b, wParam);
			break;}
		case WM_LBUTTONUP: {
			ButtonX* b = fromHWND(hwnd);
			S_ASSERT(b);
			if (b->_pressed) {
				b->evtMouseUp(b, wParam);
				if (getClientRect(hwnd).contains(Point::fromLParam(lParam))) {
					b->evtClick(b);
				}
			}
			b->_pressed = false;
			break;}
		case WM_LBUTTONDBLCLK: {
			//SendMessage(hwnd, BM_CLICK, 0, 0);
			ButtonX* b = fromHWND(hwnd);
			S_ASSERT(b);
			b->evtMouseDown(b, wParam);
			b->evtMouseUp(b, wParam);
			b->evtClick(b);
			break;}
		case WM_MOUSELEAVE:
			//fromHWND(hwnd)->_pressed = false;
			break;
		case WM_MOUSEMOVE:
			_tipTarget->attachButton(fromHWND(hwnd));
			ToolTipX::mouseMovement(GetParent(hwnd));
			//if (wParam == MK_LBUTTON) {
			//	fromHWND(hwnd)->_pressed = true;
			//}
			break;

#endif

		case WM_DESTROY:
			delete ButtonX::fromHWND(hwnd);
			break;

		};

		return CallWindowProc(ButtonX::buttonClassProc, hwnd, message, wParam, lParam);
	}