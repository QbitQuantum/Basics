void
InitSysColors(void)
{
    char    KeyNames[1024];
    char    KeyColor[128];
    LPSTR   lpKey;
    LPSTR   lpFile;
    int	n,ret;
    COLORREF sc;
    COLORREF rc;
    HDC hDC;

    lpFile = GetTwinFilename();
    GetPrivateProfileString((LPSTR)"colors",NULL,NULL,
				KeyNames,1024,lpFile);

    hDC = GetDC(0);

    for(lpKey = KeyNames; *lpKey != 0; lpKey += strlen(lpKey) + 1) 
	for(n=0; SysColorNames[n]; n++) 
	    if(strcasecmp(SysColorNames[n],lpKey) == 0) {
		sc = GetSysColor(n);
		ret = GetPrivateProfileString(
				(LPSTR)"colors",
			        (LPSTR) lpKey,
				(LPSTR) 0,
				KeyColor,
				128,
				lpFile);
		if (ret) {
		    rc = GetStringColor(KeyColor);
		    switch (n) {
			case COLOR_MENU:
			case COLOR_WINDOW:
			case COLOR_BTNFACE:
			case COLOR_HIGHLIGHT:
			case COLOR_MENUTEXT:
			case COLOR_WINDOWTEXT:
			case COLOR_CAPTIONTEXT:
			case COLOR_HIGHLIGHTTEXT:
			case COLOR_BTNTEXT:
			    /* those cannot be dithered */
			    rc = GetNearestColor(hDC,rc);
			    break;
			default:
			    break;
		    }
		    SetSysColors(1,&n,&rc);
		    break;
		}
	    }

    ReleaseDC(0,hDC);
}