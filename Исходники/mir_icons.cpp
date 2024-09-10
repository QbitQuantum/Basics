HICON IcoLib_LoadIcon(const char *iconName, BOOL copy)
{
	if (!ServiceExists(MS_SKIN2_GETICON))
		return NULL;

	if (iconName == NULL || iconName[0] == 0)
		return NULL;
	
	HICON hIcon = (HICON) CallService(MS_SKIN2_GETICON, 0, (LPARAM) iconName);
	if (copy && hIcon != NULL)
	{
		hIcon = CopyIcon(hIcon);
		CallService(MS_SKIN2_RELEASEICON, (WPARAM) hIcon, 0);
	}
	return hIcon;
}