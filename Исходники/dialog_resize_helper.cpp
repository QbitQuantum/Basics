BOOL dialog_resize_helper::ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult) {
	switch(uMsg) {
	case WM_SIZE:
		on_wm_size();
		return FALSE;
	case WM_GETMINMAXINFO:
		{
			RECT r;
			LPMINMAXINFO info = (LPMINMAXINFO) lParam;
			DWORD dwStyle = GetWindowLongPtr(hWnd, GWL_STYLE);
			DWORD dwExStyle = GetWindowLongPtr(hWnd, GWL_EXSTYLE);
			if (max_x && max_y)
			{
				r.left = 0; r.right = max_x;
				r.top = 0; r.bottom = max_y;
				MapDialogRect(hWnd,&r);
				AdjustWindowRectEx(&r, dwStyle, FALSE, dwExStyle);
				info->ptMaxTrackSize.x = r.right - r.left;
				info->ptMaxTrackSize.y = r.bottom - r.top;
			}
			if (min_x && min_y)
			{
				r.left = 0; r.right = min_x;
				r.top = 0; r.bottom = min_y;
				MapDialogRect(hWnd,&r);
				AdjustWindowRectEx(&r, dwStyle, FALSE, dwExStyle);
				info->ptMinTrackSize.x = r.right - r.left;
				info->ptMinTrackSize.y = r.bottom - r.top;
			}
		}
		lResult = 0;
		return TRUE;
	case WM_INITDIALOG:
		set_parent(hWnd);
		{
			t_size n;
			for(n=0;n<m_table.get_size();n++) {
				GetChildWindowRect(parent,m_table[n].id,&rects[n]);
			}
		}
		return FALSE;
	case WM_DESTROY:
		reset();
		return FALSE;
	default:
		return FALSE;
	}
}