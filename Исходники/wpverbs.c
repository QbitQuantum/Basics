boolean wpedit (hdlexternalvariable hvariable, hdlwindowinfo hparent, ptrfilespec fs, bigstring bstitle, rectparam rzoom) {

	//
	// 2006-09-16 creedon: on Mac, set window proxy icon
	//
	// 5.0b18 dmb: further protection: set flwindowopen bit before newchildwindow, which will yield
	//
	// 1997-04-17 dmb: protect against globals smashing under Windows
	//
	// 5.0.2b6 dmb: added flwindowopen loop to handle Windows async overlap
	//
	
	register hdlwpvariable hv = (hdlwpvariable) hvariable;
	register hdlwprecord hwp;
	Rect rwindow;
	WindowPtr w;
	hdlwindowinfo hi;
	
	if (!wpverbinmemory ((hdlexternalvariable) hv)) // couldn't swap it into memory
		return (false);
	
	hwp = (hdlwprecord) (**hv).variabledata; // it's in memory
	
	while ((**hwp).flwindowopen) { // bring to front, return true
		
		if (shellfinddatawindow ((Handle) hwp, &hi)) {
			
			if ((*rzoom).top > -2)
				shellbringtofront (hi);
			
			return (true);
			}

		#ifdef MACVERSION
			break;
		#else
			if (!shellyield (false))
				return (false);
		#endif
		}
	
	rwindow = (**hwp).windowrect; // window comes up where it was last time
	
	(**hwp).flwindowopen = true;

	if (!newchildwindow (idwpconfig, hparent, &rwindow, rzoom, bstitle, &w)) {
		
		(**hwp).flwindowopen = false;

		return (false);
		}
	
	wpdata = hwp; // copy into global
	
	getwindowinfo (w, &hi);
	
	(**hi).hdata = (Handle) hwp;
	
	if ( fs != nil ) {
	
		(**hi).fspec = *fs;
		
		#ifdef MACVERSION
		
			if (macfilespecisresolvable (fs))
				SetWindowProxyCreatorAndType (w, 'LAND', 'FTwp', kOnSystemDisk);
				
		#endif
		
		}
	
	shellpushglobals (w);

	wplinkwindowinfo ();
	
	shellpopglobals ();
	
	// (**hwp).flwindowopen = true;
	
	if ((**hwp).fldirty)
		shellsetwindowchanges (hi, true);

	windowzoom (w); // show the window to the user. do last, or we'd have to push globals
	
	return (true);
	
	} // wpedit