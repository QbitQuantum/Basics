static int OnShutdown(WPARAM wParam, LPARAM lParam)
{
	DeinitProfilesModule();

	// set windowstate and docked for next startup
	if (db_get_b(NULL, MODULENAME, SETTING_SETWINSTATE, 0)) {
		int state = db_get_b(NULL, MODULENAME, SETTING_WINSTATE, SETTING_STATE_NORMAL);
		HWND hClist = pcli->hwndContactList;
		BOOL isHidden = !IsWindowVisible(hClist);
		switch (state) {
		case SETTING_STATE_HIDDEN:
			// try to use services where possible
			if (!isHidden)
				CallService(MS_CLIST_SHOWHIDE, 0, 0);
			break;

		case SETTING_STATE_MINIMIZED:
			if (!db_get_b(NULL, MODULE_CLIST, SETTING_TOOLWINDOW, 0))
				ShowWindow(hClist, SW_SHOWMINIMIZED);
			break;

		case SETTING_STATE_NORMAL:
			// try to use services where possible (that's what they're for)
			if (isHidden)
				CallService(MS_CLIST_SHOWHIDE, 0, 0);
			break;
		}
	}

	// hangup
	if (db_get_b(NULL, MODULENAME, SETTING_AUTOHANGUP, 0))
		InternetAutodialHangup(0);

	int state = db_get_b(NULL, MODULENAME, SETTING_WINSTATE, SETTING_STATE_NORMAL);
	// set windowstate and docked for next startup
	if (db_get_b(NULL, MODULENAME, SETTING_SETWINSTATE, 0))
		db_set_b(NULL, MODULE_CLIST, SETTING_WINSTATE, (BYTE)state);

	if (hMessageWindow)
		DestroyWindow(hMessageWindow);

	startupSettings.destroy();
	return 0;
}