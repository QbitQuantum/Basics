static boolean pushwindowmenuvisit (WindowPtr w, ptrvoid ptr) {
#pragma unused (ptr)

	/*
	3/8/91 dmb: mark the current root item with an asterix, if not checked
	
	4/5/91 dmb: italicize hidden windows

	5.1b23 dmb: for Win threading, check getwindowinfo result

	7.0b26 PBS: mark the current root only on Macintosh. This is because the mark
	used on Windows is a checkmark, which makes for two checkmarks in the Window
	menu, which is confusing.
	*/
	
	bigstring bs;
	WindowPtr wfront;
	register short ix;
	hdlwindowinfo hinfo;
	Style itemstyle = 0;

	#ifdef MACVERSION
		hdlwindowinfo hroot;
	#endif
	
	if (!getwindowinfo (w, &hinfo))
		return (false);
	
#ifdef xxxPIKE
	/* Pike only displays visible .root windows */
	if ((hinfo != nil) && ((**hinfo).configresnum == idcancoonconfig) && (**hinfo).flhidden)
		return (true);
#endif

	shellgetwindowtitle (hinfo, bs); // 7.24.97 dmb: was windowgettitle
	
	if (isemptystring (bs))
		return (true);
	
	if (!pushmenuitem (hwindowsmenu, windowsmenu, bs, 0))
		return (false);
	
	fllastwasdottedline = false;

	frontshellwindow (&wfront);
	
	ix = countmenuitems (hwindowsmenu);
	
	if (w == wfront)
		checkmenuitem (hwindowsmenu, ix, true);
	
	#ifdef MACVERSION /*7.0b26: mark the current root only if this is the Mac version.*/

		else {
			if (frontrootwindow (&hroot) && (hinfo == hroot)) /*we're the active root*/
				markmenuitem (hwindowsmenu, ix, '×');
			}
	#endif
	
	if ((**hinfo).flmadechanges)
		itemstyle += underline;
	
	if ((**hinfo).flhidden)
		itemstyle += italic;
	
	if (itemstyle != 0)
		stylemenuitem (hwindowsmenu, ix, itemstyle);
	
	if (ix == ixsearch) /*side-effect for window menu selection*/
		hsearch = hinfo;
	
	return (true);
	} /*pushwindowmenuvisit*/