	void PresetHotkeyGroup::ResizeToContent() {
		int x = 0;
		int y = 0;
		for (CWnd *pWnd = GetWindow(GW_CHILD); pWnd != NULL; pWnd = pWnd->GetNextWindow(GW_HWNDNEXT)) {
			//Insert your code here. pWnd is a pointer to control window.
			CRect rect;
			pWnd->GetWindowRect(rect);

			y = max(rect.bottom, y);
			x = max(rect.right, x);
		}

		CRect rect;
		GetWindowRect(rect);
		rect.right = x;
		rect.bottom = y;
		MoveWindow(rect);
	}