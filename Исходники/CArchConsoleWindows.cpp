LRESULT
CArchConsoleWindows::wndProc(HWND hwnd,
				UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_CLOSE:
		ShowWindow(m_frame, FALSE);
		m_show = false;
		return 0;

	case SYNERGY_MSG_CONSOLE_OPEN:
		return 0;

	case SYNERGY_MSG_CONSOLE_CLOSE:
		SendMessage(m_frame, WM_CLOSE, 0, 0);
		m_show = false;
		return 0;

	case SYNERGY_MSG_CONSOLE_SHOW:
		m_show = true;
		if (wParam != 0 || !m_buffer.empty()) {
			ShowWindow(m_frame, TRUE);
		}
		return 0;

	case SYNERGY_MSG_CONSOLE_WRITE:
		appendBuffer(reinterpret_cast<const char*>(wParam));
		return 0;

	case SYNERGY_MSG_CONSOLE_CLEAR:
		clearBuffer();
		return 0;

	case WM_SIZE:
		if (hwnd == m_frame) {
			MoveWindow(m_hwnd, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
		}
		break;

	case WM_SIZING:
		if (hwnd == m_frame) {
			// get window vs client area info
			int wBase = 40 * m_wChar;
			int hBase = 40 * m_hChar;
			DWORD style   = GetWindowLong(m_frame, GWL_STYLE);
			DWORD exStyle = GetWindowLong(m_frame, GWL_EXSTYLE);
			RECT rect;
			rect.left   = 100;
			rect.top    = 100;
			rect.right  = rect.left + wBase;
			rect.bottom = rect.top + hBase;
			AdjustWindowRectEx(&rect, style, FALSE, exStyle);
			wBase = rect.right - rect.left - wBase;
			hBase = rect.bottom - rect.top - hBase;

			// get closest size that's a multiple of the character size
			RECT* newRect = (RECT*)lParam;
			int width  = (newRect->right - newRect->left - wBase) / m_wChar;
			int height = (newRect->bottom - newRect->top - hBase) / m_hChar;
			width  = width  * m_wChar + wBase;
			height = height * m_hChar + hBase;

			// adjust sizing rect
			switch (wParam) {
			case WMSZ_LEFT:
			case WMSZ_TOPLEFT:
			case WMSZ_BOTTOMLEFT:
				newRect->left = newRect->right - width;
				break;

			case WMSZ_RIGHT:
			case WMSZ_TOPRIGHT:
			case WMSZ_BOTTOMRIGHT:
				newRect->right = newRect->left + width;
				break;
			}
			switch (wParam) {
			case WMSZ_TOP:
			case WMSZ_TOPLEFT:
			case WMSZ_TOPRIGHT:
				newRect->top = newRect->bottom - height;
				break;

			case WMSZ_BOTTOM:
			case WMSZ_BOTTOMLEFT:
			case WMSZ_BOTTOMRIGHT:
				newRect->bottom = newRect->top + height;
				break;
			}
			return TRUE;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}