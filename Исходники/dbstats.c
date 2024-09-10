static boolean statsnewwindow (void) {
	
	WindowPtr w;
	hdlwindowinfo hw;
	bigstring bstitle;
	Rect rzoom, rwindow;
	hdlwindowinfo hparent;
	Handle hdata;
	
	if (!shellgetfrontrootinfo (&hparent)) /*our parent is the frontmost root window*/
		return (false);
	
	shellgetwindowcenter (hparent, &rzoom);
	
	if (!newclearhandle (sizeof (tystatsrecord), &hdata))
		return (false);
	
	rwindow.top = -1; /*accept default*/
	
	getstatsstring (idwindowtitle, bstitle);
	
	if (!newchildwindow (idstatsconfig, hparent, &rwindow, &rzoom, bstitle, &w)) {
		
		disposehandle ((Handle) hdata);
		
		return (false);
		}
		
	getwindowinfo (w, &hw);
	
	(**hw).hdata = hdata;
	
	/*ccnewsubwindow (messagewindowinfo, ixmsginfo);*/
	
//	shellpushglobals (statswindow); 
	
	#if TARGET_API_MAC_CARBON == 1
	
		SetThemeWindowBackground (w, kThemeBrushModelessDialogBackgroundActive, false);
		
	#endif

	windowzoom (w);
	
//	shellpopglobals ();
	
	statswindow = w;

	return (true);
	} /*statsnewwindow*/