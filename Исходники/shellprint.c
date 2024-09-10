boolean shellinitprint (void) {
	
	/*
	 9/5/90 dmb: close print resources after initializing stuff
	 
	 10/21/91 dmb: added margins field to print info; structure is now here to 
	 have user-settable margins.
	 
	 12/31/91 dmb: initialize shellprintinfo.paperrect to standard 72dpi values in 
	 case no printer is chosen and shellcopyprintinfo never gets called
	 
	 1/18/93 dmb: don't call shellcheckprinterror the first time; if PrOpen fails 
	 here, we don't want to raise an alert.
	 */
	
#if MACVERSION && !TARGET_API_MAC_CARBON
	
	Handle h;
	
#endif
	
	currentprintport = NULL;
	
	clearbytes (&shellprintinfo, longsizeof (shellprintinfo));
	
	setrect (&shellprintinfo.margins, 36, 36, 36, 36);
	
	setrect (&shellprintinfo.paperrect, 5, 6, 725, 546); /*defaults in case PrOpen fails*/
	
	shellprintinfo.scaleMult = 1;
	shellprintinfo.scaleDiv = 1;
	
#ifdef MACVERSION
	
#	if TARGET_API_MAC_CARBON == 1
	
	//I realized this is only called once during the startup of the app.
	//Carbon printing really doesn't need any global structures. Better to 
	//allocate them as we use them.
	
	// Nope.
	// We need a global var for calling page setup
	
	shellprintinfo.printport = nil;
	shellprintinfo.printhandle = nil;
	shellprintinfo.pageformat = nil;
	shellprintinfo.printsettings = nil;
	// shellprintinfo.pagerect = {0,0,0,0};
	
#	else		
	
	if (!newclearhandle (longsizeof (TPrint), &h))
		return (false);
	
	shellprintinfo.printhandle = (THPrint) h; /*copy into print record*/
	
	PrOpen (); /*initialize the Mac print manager*/
	
	if (PrError () != noErr)
		goto error;
	
	PrintDefault (shellprintinfo.printhandle); /*set default print record*/
	
	PrClose (); /*shouldn't leave print resources open all the time*/
	
	if (!shellcheckprinterror (false)) 
		goto error;
#	endif
	
#endif
	
#ifdef WIN95VERSION
	
	ZeroMemory (&shellprintinfo.pagesetupinfo, sizeof (PAGESETUPDLG));
	
	shellprintinfo.pagesetupinfo.lStructSize = sizeof (PAGESETUPDLG);
	
	shellprintinfo.pagesetupinfo.hwndOwner = NULL;
	
	shellprintinfo.pagesetupinfo.Flags = PSD_RETURNDEFAULT | PSD_NOWARNING;
	
	if (! PageSetupDlg (&shellprintinfo.pagesetupinfo)) {
		
		if (CommDlgExtendedError() != 0)
			goto error;
	}
	
#endif
	
	//#if !TARGET_API_MAC_CARBON
	
	shellcopyprintinfo (); /*copies fields from handle into record*/
	
	//#endif
	
	return (true);
	
#if !defined(MACVERSION) || !TARGET_API_MAC_CARBON
	
error:
		
#endif
		
		/*
		 shelldisposeprintinfo ();
		 */
		
		return (false);
} /*shellinitprint*/