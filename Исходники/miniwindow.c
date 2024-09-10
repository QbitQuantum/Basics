static boolean mininewwindow (callback setuproutine) {
	
	/*
	5.0a18 dmb: use ccfindrootwindow instead of frontrootwindow, as
	we do in minifindwindow. not just for about, but for guest roots
	*/

	register hdlminirecord hm;
	bigstring bs;
	Rect rzoom, rwindow;
	hdlwindowinfo hinfo, hparent;
	WindowPtr w;
	
	if (!ccfindrootwindow (&hparent)) /*our parent is the active root window*/
		return (false);
	
	/*shellgetwindowcenter (hparent, &rzoom);*/
	
	rzoom.top = -1; /*zoom from default rect*/
	
	if (!newclearhandle (longsizeof (tyminirecord), (Handle *) &minidata))
		return (false);
		
	hm = minidata; /*copy into register*/
	
	(**hm).savestringroutine = (minisavestringcallback) &truenoop;
	
	(**hm).loadstringroutine = (miniloadstringcallback) &truenoop;
	
	(**hm).texthitroutine = (minitexthitcallback) &truenoop;
	
	(**hm).iconenableroutine = (shellvoidcallback) &truenoop;
	
	(**hm).iconhitroutine = &truenoop;
	
	(**hm).setvalueroutine = &truenoop;
	
	(**hm).fillpopuproutine = (fillpopupcallback) &truenoop;
	
	(**hm).popupselectroutine = (popupselectcallback) &truenoop;
	
	(**hm).gettargetdataroutine = (shellshortcallback) &falsenoop;
	
	#ifdef MACVERSION
		(**hm).forecolor = blackColor;
		
		(**hm).backcolor = whiteColor;
	#endif

	(**hm).activetextitem = -1;
	
	(*setuproutine) (); /*callback to fill in user-defined fields of minidata*/
	
	minigetwindowrect (&rwindow);
	
	copystring ((**hm).windowtitle, bs);
	
	if (!newchildwindow ((**hm).idconfig, hparent, &rwindow, &rzoom, bs, &w)) {
		
		disposehandle ((Handle) hm);
		
		return (false);
		}
	
	getwindowinfo (w, &hinfo);
	
	windowsetcolor (w, (**hm).forecolor, true);
	
	windowsetcolor (w, (**hm).backcolor, false);
	
	(**hinfo).hdata = (Handle) hm;
	
	ccnewsubwindow (hinfo, (**hm).windowtype);
	
	shellpushglobals (w); 
	
	setfontsizestyle ((**hinfo).defaultfont, (**hinfo).defaultsize, (**hinfo).defaultstyle);
		
	miniresize ();
	
	minisetfontsize ();
	
	minisetvalue ();
	
	miniloadstrings ();
	
	(**hm).flselectallpending = true; /*selectall on idle*/
		
	windowzoom (w);
	
	#if TARGET_API_MAC_CARBON == 1 /*Make sure the window is fully drawn.*/
		miniresize ();
	#endif

	shellpopglobals ();
	
	return (true);
	} /*mininewwindow*/