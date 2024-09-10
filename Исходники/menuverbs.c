boolean menuedit (hdlexternalvariable hvariable, hdlwindowinfo hparent, ptrfilespec fs, bigstring bstitle, rectparam rzoom) {
	
	//
	// 2006-09-16 creedon: on Mac, set window proxy icon
	//
	// 5.0d19 dmb: set flwindowopen; use locals, not menu globals.
	//
	
	register hdlmenuvariable hv = (hdlmenuvariable) hvariable;
	hdlmenurecord hm;
	Rect rwindow;
	WindowPtr w;
	hdlwindowinfo hi;
	
	if ((**hv).flinmemory) {
			
		if (shellfinddatawindow ((Handle) (**hv).variabledata, &hi)) {
			
			if ((*rzoom).top > -2)
				shellbringtofront (hi);
			
			return (true);
			}
		}
		
	if (!menuverbinmemory (hv)) // error swapping menurecord into memory
		return (false);
		
	hm = (hdlmenurecord) (**hv).variabledata;
	
	rwindow = (**hm).menuwindowrect; // window comes up where it was last time
	
	if (!newchildwindow (idmenueditorconfig, hparent, &rwindow, rzoom, bstitle, &w)) 
		return (false);
	
	getwindowinfo (w, &hi);
	
	(**hi).hdata = (Handle) hm; // link data into shell's structure
	
	if ( fs != nil ) {
	
		(**hi).fspec = *fs;
		
		#ifdef MACVERSION
		
			if (macfilespecisresolvable (fs))
				SetWindowProxyCreatorAndType ( w, 'LAND', 'FTmb', kOnSystemDisk );
				
		#endif
		
		}
	
	shellpushglobals (w);
	
	meeditmenurecord ();
	
	shellpopglobals ();
	
	(**hm).flwindowopen = true;
	
	if ((**hm).fldirty)
		shellsetwindowchanges (hi, true);
	
	windowzoom (w); // show the window to the user
	
	return (true);
	
	} // menuedit