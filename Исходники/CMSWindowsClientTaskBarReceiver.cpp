void
CMSWindowsClientTaskBarReceiver::runMenu(int x, int y)
{
	// do popup menu.  we need a window to pass to TrackPopupMenu().
	// the SetForegroundWindow() and SendMessage() calls around
	// TrackPopupMenu() are to get the menu to be dismissed when
	// another window gets activated and are just one of those
	// win32 weirdnesses.
	createWindow();
	SetForegroundWindow(m_window);
	HMENU menu = GetSubMenu(m_menu, 0);
	SetMenuDefaultItem(menu, IDC_TASKBAR_STATUS, FALSE);
	HMENU logLevelMenu = GetSubMenu(menu, 3);
	CheckMenuRadioItem(logLevelMenu, 0, 6,
							CLOG->getFilter() - kERROR, MF_BYPOSITION);
	int n = TrackPopupMenu(menu,
							TPM_NONOTIFY |
							TPM_RETURNCMD |
							TPM_LEFTBUTTON |
							TPM_RIGHTBUTTON,
							x, y, 0, m_window, NULL);
	SendMessage(m_window, WM_NULL, 0, 0);

	// perform the requested operation
	switch (n) {
	case IDC_TASKBAR_STATUS:
		showStatus();
		break;

	case IDC_TASKBAR_LOG:
		copyLog();
		break;

	case IDC_TASKBAR_SHOW_LOG:
		ARCH->showConsole(true);
		break;

	case IDC_TASKBAR_LOG_LEVEL_ERROR:
		CLOG->setFilter(kERROR);
		break;

	case IDC_TASKBAR_LOG_LEVEL_WARNING:
		CLOG->setFilter(kWARNING);
		break;

	case IDC_TASKBAR_LOG_LEVEL_NOTE:
		CLOG->setFilter(kNOTE);
		break;

	case IDC_TASKBAR_LOG_LEVEL_INFO:
		CLOG->setFilter(kINFO);
		break;

	case IDC_TASKBAR_LOG_LEVEL_DEBUG:
		CLOG->setFilter(kDEBUG);
		break;

	case IDC_TASKBAR_LOG_LEVEL_DEBUG1:
		CLOG->setFilter(kDEBUG1);
		break;

	case IDC_TASKBAR_LOG_LEVEL_DEBUG2:
		CLOG->setFilter(kDEBUG2);
		break;

	case IDC_TASKBAR_QUIT:
		quit();
		break;
	}
}