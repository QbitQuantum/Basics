void SetDesktopWallPaper(LPWSTR wallpaper)
{
	CoInitialize(NULL);   
    
	IActiveDesktop   *pDesk;   
	if(   S_OK   !=   CoCreateInstance   (   CLSID_ActiveDesktop,   NULL,   CLSCTX_INPROC_SERVER,   IID_IActiveDesktop,   (void**)   &pDesk   )   )   
	{ 
	  pDesk->Release();
	  return ;
	}   
	pDesk->SetWallpaper(wallpaper,0);
	WALLPAPEROPT wallpaperopt;
	wallpaperopt.dwSize = sizeof(WALLPAPEROPT);
	wallpaperopt.dwStyle = WPSTYLE_CENTER;
	pDesk->SetWallpaperOptions(&wallpaperopt,0);
	pDesk->ApplyChanges(AD_APPLY_ALL);
	pDesk->Release();
	CoFreeUnusedLibraries();   
	CoUninitialize();  
}