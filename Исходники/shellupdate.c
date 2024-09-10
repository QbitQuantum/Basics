void shellupdatewindow (WindowPtr w) {
	
	/*
	1/17/91 dmb: draw scrollbars, buttons, etc. before window contents
	*/
	
	hdlwindowinfo hinfo;
	register hdlwindowinfo hw;
	
	getwindowinfo (w, &hinfo);
	
	hw = hinfo; /*copy into register*/
	
	if ((hinfo == nil) || (**hinfo).fldisposewhenpopped) {

		#ifdef MACVERSION
			BeginUpdate (w);
			
			EndUpdate (w);
		#endif
		
		return;
		}
	
	BeginUpdate (w);
	
	if (!shellpushglobals (w))
		goto exit;
	
	//Code change by Timothy Paustian Monday, August 21, 2000 4:31:49 PM
	//Must pass a CGrafPtr to pushport on OS X to avoid a crash
	{
	CGrafPtr	thePort;
	#if TARGET_API_MAC_CARBON == 1
	thePort = GetWindowPort(w);
	#else
	thePort = (CGrafPtr)w;
	#endif
		
	pushport (thePort);/*7/7/90 DW: this probably is not necessary, shellpushglobals does it*/
	}
#ifdef MACVERSION	
	if (!config.fldialog) /*if it's a dialog, the callback routine re-drew the controls*/
		DrawControls (w);
	
	if (config.flvertscroll)
		showscrollbar ((**hw).vertscrollbar); /*make sure it is visible*/
	
	shelldrawgrowicon (hw);
	
	if (config.flhorizscroll)
		showscrollbar ((**hw).horizscrollbar);
	//Code change by Timothy Paustian Saturday, April 29, 2000 11:07:46 PM
	//Changed to Opaque call for Carbon
	//This is working, but it is giving bact the coordinates in local not
	//global. It seems to make more sense to me so leave it.
	#if ACCESSOR_CALLS_ARE_FUNCTIONS == 1
	{
	CGrafPtr	thePort = GetWindowPort(w);
	(**hw).drawrgn = NewRgn(); //note we delete this below
	(**hw).drawrgn = GetPortVisibleRegion(thePort, (**hw).drawrgn);
	}
	#else
	//old code
	(**hw).drawrgn = (*w).visRgn; /*so updater knows what needs drawing*/
	#endif
#endif

#ifdef WIN95VERSION
//	(**hw).drawrgn = getvisregion (w);

	pushcliprgn ((**hw).drawrgn, false);
#endif

	if (shellrectneedsupdate (&(**hw).buttonsrect)) /*if window has an attached button list, draw it*/
		shelldrawbuttons ();
	
	drawwindowmessage (w);
	
	// 4.11.97 dmb: it appears that under Windows we need to push the clipk here.
	// Most likely, we should be establishing this wider clip soon arter window
	// creation, one time.

	if (shellrectneedsupdate (&(**hw).contentrect))
		(*shellglobals.updateroutine) ();
	
#ifdef WIN95VERSION
	popclip ();
	
	DeleteObject ((**hw).drawrgn);
#endif
#ifdef MACVERSION
	//Code change by Timothy Paustian Saturday, April 29, 2000 11:11:12 PM
	//Changed to Opaque call for Carbon
	//Get rid of the drawrgn to prevent a memory leak
	#if ACCESSOR_CALLS_ARE_FUNCTIONS == 1
	DisposeRgn((**hw).drawrgn);	
	#endif
#endif
	(**hw).drawrgn = nil; /*this is a temp, keep it nil normally*/
	
	popport (); /*7/7/90 DW: see comment for pusport, above*/
	
	shellpopglobals ();
	
	exit:
	
	EndUpdate (w);
	} /*shellupdatewindow*/