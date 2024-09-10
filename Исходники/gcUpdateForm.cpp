void GCUpdateInfo::onPageLoad()
{
	ERROR_OUTPUT("Showing update form");
	
	Show(true);

#ifdef WIN32
	FLASHWINFO info;

	memset(&info, 0, sizeof(FLASHWINFO));
	info.cbSize = sizeof(FLASHWINFO);
	info.hwnd = (HWND)GetHWND();
	info.dwFlags = FLASHW_TRAY|FLASHW_TIMERNOFG;
	info.uCount = 20;

	FlashWindowEx(&info);
#endif
}