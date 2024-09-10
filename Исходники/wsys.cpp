// ---------------------------------
void WSys::getURL(const char *url)
{
	if (mainWindow)
		if (strnicmp(url,"http://",7) || strnicmp(url,"mailto:",7))
			ShellExecuteA(mainWindow, NULL, url, NULL, NULL, SW_SHOWNORMAL);
}