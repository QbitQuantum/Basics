void RemoteDesktop::DesktopBackground::HideWallpaper(){
	//the desktop has to be the default, not screen saver or logon
	if (!_HidingWallpaper)
	{
		if (_SaveWallpaper()){
			_SaveWallpaperStyle();
			SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, L"", SPIF_SENDCHANGE);
			_HidingWallpaper = true;
		}

	}

}