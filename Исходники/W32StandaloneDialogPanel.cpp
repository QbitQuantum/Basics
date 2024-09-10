BOOL CALLBACK W32StandaloneDialogPanel::StaticCallback(HWND hDialog, UINT message, WPARAM wParam, LPARAM lParam) {
	if (message == WM_INITDIALOG) {
		((W32DialogPanel*)lParam)->init(hDialog);
		return true;
	} else if (message == WM_COMMAND) {
		W32DialogPanel *panel = ourPanels[hDialog];
		if (panel != 0) {
			return panel->commandCallback(wParam);
		}
	} else if (message == WM_NOTIFY) {
		W32DialogPanel *panel = ourPanels[hDialog];
		if (panel != 0) {
			return panel->notificationCallback(wParam, lParam);
		}
	} else if (message == WM_GETMINMAXINFO) {
		W32DialogPanel *panel = ourPanels[hDialog];
		if (panel != 0) {
			POINT &minTrackSize = ((MINMAXINFO*)lParam)->ptMinTrackSize;
			W32Widget::Size minSize = panel->minimumSize();
			RECT r;
			r.left = 0;
			r.top = 0;
			r.right = minSize.Width;
			r.bottom = minSize.Height;
			MapDialogRect(hDialog, &r);
			minTrackSize.x = std::max(minTrackSize.x, r.right);
			minTrackSize.y += r.bottom;
			return true;
		}
	} else if (message == WM_SIZE) {
		W32DialogPanel *panel = ourPanels[hDialog];
		if (panel != 0) {
			RECT r;
			r.left = 0;
			r.top = 0;
			r.right = 100;
			r.bottom = 100;
			MapDialogRect(hDialog, &r);
			panel->setSize(W32Widget::Size(
				(int)LOWORD(lParam) * 100 / r.right,
				(int)HIWORD(lParam) * 100 / r.bottom));
			panel->updateElementSize();
		}
		return false;
	} else if (message == WM_DRAWITEM) {
		W32DialogPanel *panel = ourPanels[hDialog];
		if (panel != 0) {
			return panel->drawItemCallback(wParam, *(DRAWITEMSTRUCT*)lParam);
		}
	} else if (message == LAYOUT_MESSAGE) {
		W32DialogPanel *panel = ourPanels[hDialog];
		if (panel != 0) {
			panel->layout();
			return true;
		}
	}
	return false;
}