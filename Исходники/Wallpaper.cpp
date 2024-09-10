void CWallpaper::Remove()
{
	if(IsWallpaperRemoved)
		return;

	// Black color...
	static const DWORD BlackColor = RGB(0,0,0);

	// Save the current background color
	OriginalColor = GetSysColor(COLOR_BACKGROUND);

	// Set the desktop background color to the wanted one
	int colorID = COLOR_BACKGROUND;
	COLORREF color = BlackColor;
	SetSysColors(1, &colorID, &color);

	// Remove the desktop wallpaper, without updating the registry
	char nullchar = 0;
	SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, &nullchar, 0);

	IsWallpaperRemoved = true;
}