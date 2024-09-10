void WindowFinder::findWindows(HDESK hDesktop, ProcedureData *pData)
{
	if (hDesktop == NULL) return;
	EnumDesktopWindows(hDesktop, (WNDENUMPROC)EnumWndInfoProc, (LPARAM)pData);
}