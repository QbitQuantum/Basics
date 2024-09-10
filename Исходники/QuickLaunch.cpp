LRESULT QuickLaunchBar::WndProc(UINT nmsg, WPARAM wparam, LPARAM lparam)
{
	switch(nmsg) {
	  case PM_REFRESH:
		AddShortcuts();
		break;

	  case PM_GET_WIDTH: {
		 // take line wrapping into account
		int btns = SendMessage(_hwnd, TB_BUTTONCOUNT, 0, 0);
		int rows = SendMessage(_hwnd, TB_GETROWS, 0, 0);

		if (rows<2 || rows==btns)
			return _size;

		RECT rect;
		int max_cx = 0;

		for(QuickLaunchMap::const_iterator it=_entries.begin(); it!=_entries.end(); ++it) {
			SendMessage(_hwnd, TB_GETRECT, it->first, (LPARAM)&rect);

			if (rect.right > max_cx)
				max_cx = rect.right;
		}

		return max_cx;}

	  case PM_UPDATE_DESKTOP:
		UpdateDesktopButtons(wparam);
		break;

	  case WM_CONTEXTMENU: {
		TBBUTTON btn;
		QuickLaunchMap::iterator it;
		Point screen_pt(lparam), clnt_pt=screen_pt;
		ScreenToClient(_hwnd, &clnt_pt);

		Entry* entry = NULL;
		int idx = SendMessage(_hwnd, TB_HITTEST, 0, (LPARAM)&clnt_pt);

		if (idx>=0 &&
			SendMessage(_hwnd, TB_GETBUTTON, idx, (LPARAM)&btn)!=-1 &&
			(it=_entries.find(btn.idCommand))!=_entries.end()) {
			entry = it->second._entry;
		}

		if (entry) {	// entry is NULL for desktop switch buttons
			HRESULT hr = entry->do_context_menu(_hwnd, screen_pt, _cm_ifs);

			if (!SUCCEEDED(hr))
				CHECKERROR(hr);
		} else
			goto def;
		break;}

	  default: def:
		return super::WndProc(nmsg, wparam, lparam);
	}

	return 0;
}