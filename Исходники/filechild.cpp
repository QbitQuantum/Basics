LRESULT FileChildWindow::WndProc(UINT nmsg, WPARAM wparam, LPARAM lparam)
{
	switch(nmsg) {
		case WM_DRAWITEM: {
			LPDRAWITEMSTRUCT dis = (LPDRAWITEMSTRUCT)lparam;
			Entry* entry = (Entry*) dis->itemData;

			if (dis->CtlID == IDW_TREE_LEFT) {
				_left->draw_item(dis, entry);
				return TRUE;
			} else if (dis->CtlID == IDW_TREE_RIGHT) {
				_right->draw_item(dis, entry);
				return TRUE;
			}

			goto def;}

		case WM_SIZE:
			if (wparam != SIZE_MINIMIZED)
				resize_children(LOWORD(lparam), HIWORD(lparam));
			return DefMDIChildProc(_hwnd, nmsg, wparam, lparam);

		case PM_GET_FILEWND_PTR:
			return (LRESULT)this;

		case WM_SETFOCUS: {
			TCHAR path[MAX_PATH];

			if (_left && _left->_cur) {
				_left->_cur->get_path(path, COUNTOF(path));
				SetCurrentDirectory(path);
			}

			SetFocus(_focus_pane? _right_hwnd: _left_hwnd);
			goto def;}

		case PM_DISPATCH_COMMAND: {
			Pane* pane = GetFocus()==_left_hwnd? _left: _right;

			switch(LOWORD(wparam)) {
			  case ID_WINDOW_NEW: {CONTEXT("FileChildWindow PM_DISPATCH_COMMAND ID_WINDOW_NEW");
				if (_root._entry->_etype == ET_SHELL)
					FileChildWindow::create(ShellChildWndInfo(GetParent(_hwnd)/*_hmdiclient*/, _path, DesktopFolderPath()));
				else
					FileChildWindow::create(FileChildWndInfo(GetParent(_hwnd)/*_hmdiclient*/, _path));
				break;}

			  case ID_REFRESH: {CONTEXT("ID_REFRESH");
				refresh();
				break;}

			  case ID_ACTIVATE: {CONTEXT("ID_ACTIVATE");
				activate_entry(pane);
				break;}

			  default:
				if (pane->command(LOWORD(wparam)))
					return TRUE;
				else
					return super::WndProc(nmsg, wparam, lparam);
			}

			return TRUE;}

		case WM_CONTEXTMENU: {
			 // first select the current item in the listbox
			HWND hpanel = (HWND) wparam;
			POINT pt;
			pt.x = LOWORD(lparam);
			pt.y = HIWORD(lparam);
			POINT pt_screen = pt;
			ScreenToClient(hpanel, &pt);
			SendMessage(hpanel, WM_LBUTTONDOWN, 0, MAKELONG(pt.x, pt.y));
			SendMessage(hpanel, WM_LBUTTONUP, 0, MAKELONG(pt.x, pt.y));

			 // now create the popup menu using shell namespace and IContextMenu
			Pane* pane = GetFocus()==_left_hwnd? _left: _right;
			int idx = ListBox_GetCurSel(*pane);
			if (idx != -1) {
				Entry* entry = (Entry*) ListBox_GetItemData(*pane, idx);

				HRESULT hr = entry->do_context_menu(_hwnd, pt_screen, _cm_ifs);

				if (SUCCEEDED(hr))
					refresh();
				else
					CHECKERROR(hr);
			}
			break;}

		default: def:
			return super::WndProc(nmsg, wparam, lparam);
	}

	return 0;
}