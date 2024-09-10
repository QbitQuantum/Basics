LRESULT CALLBACK
Cieambulant::PluginWinProc(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	typedef HRGN NPRegion;
	if (updatePlayer() != S_OK)
		return S_FALSE;

	switch (msg) {
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(&ps);
			if (m_hwnd && m_ambulant_player) {
				HDC hdc = ::GetDC(m_hwnd);
				m_ambulant_player->redraw(m_hwnd, hdc, NULL); // XXX Should pass dirty rect
				::ShowWindow(m_hwnd, SW_SHOW);
				::ReleaseDC(m_hwnd, hdc);
			}
			EndPaint(&ps);
		}
		break;
	case WM_LBUTTONDOWN:
	case WM_MOUSEMOVE:
		POINT point;
		point.x=GET_X_LPARAM(lParam);
		point.y=GET_Y_LPARAM(lParam);
		if (m_ambulant_player) {
			if (msg == WM_MOUSEMOVE) {
				// code copied from MmView.cpp
				int new_cursor_id = m_ambulant_player->get_cursor(point.x, point.y, m_hwnd);
				if(new_cursor_id != m_cursor_id) {
					HINSTANCE hIns = 0;
					HCURSOR new_cursor = 0;
					if(new_cursor_id == 0) {
						new_cursor = LoadCursor(hIns, IDC_ARROW);
					} else {
						new_cursor = LoadCursor(hIns, IDC_HAND);
					}
					SetClassLongPtr(m_hwnd, GCLP_HCURSOR, HandleToLong(new_cursor));
					m_cursor_id = new_cursor_id;
				}
			} else {
				m_ambulant_player->on_click(point.x, point.y, m_hwnd);
			}
		}
		break;

	default:
		break;
	}
	BOOL rv = DefWindowProc(msg, wParam, lParam);
	bHandled = rv;
	return rv;
}