static LRESULT CALLBACK PopupThreadManagerWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PopupWnd2 *wnd = NULL;
	if (message == UTM_ADD_WINDOW || message == UTM_UPDATE_WINDOW || message == UTM_REMOVE_WINDOW || message == UTM_REQUEST_REMOVE)
		if (!(wnd = (PopupWnd2 *)lParam))
			return 0;

	switch (message) {
	case UTM_STOP_THREAD:
		gTerminating = true;
		if (db_get_b(NULL, MODULNAME, "FastExit", 0))
			for (int i = 0; i < popupList.getCount(); ++i)
				PUDeletePopup(popupList[i]->getHwnd());
		PostQuitMessage(0);
		break;

	case UTM_ADD_WINDOW:
		if (gTerminating)
			break;
		UpdatePopupPosition(popupList.getCount() ? popupList[popupList.getCount() - 1] : 0, wnd);
		popupList.insert(wnd);
		++nPopups;
		wnd->callMethodAsync(&PopupWnd2::m_show, 0);
		break;

	case UTM_UPDATE_WINDOW:
		RepositionPopups();
		break;

	case UTM_REQUEST_REMOVE:
		if ((PopupOptions.LeaveHovered && gLockCount) || (wnd && wnd->isLocked()))
			wnd->updateTimer();
		else
			PostMessage(wnd->getHwnd(), WM_CLOSE, 0, 0);
		break;

	case UTM_REMOVE_WINDOW:
	{
		for (int i = popupList.getCount() - 1; i >= 0; i--)
			if (popupList[i] == wnd)
				popupList.remove(i);
	}
	RepositionPopups();
	--nPopups;
	delete wnd;
	break;

	case UTM_LOCK_QUEUE:
		++gLockCount;
		break;

	case UTM_UNLOCK_QUEUE:
		if (--gLockCount < 0)
			gLockCount = 0;
		break;

	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}