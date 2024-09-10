boolean shellsetglobals (WindowPtr wglobals) {
	
	/*
	set up globals for the window.
	
	8/25/90 DW: when we're closing all the windows, we pop the globals stack
	but there are no windows open to set globals to.  we put a defensive driving
	check in at the lowest level -- it can do double-duty protecting against
	similar problems that might crop up elsewhere.  the call to see if the window
	list is empty is very, very cheap.
	*/
	
	register WindowPtr w = wglobals;
	hdlwindowinfo hinfo;
	register hdlwindowinfo hw;
	short ix = 0;
	
	if (!wglobals || emptywindowlist ()) { /*defensive driving, avoid a crash, it CAN happen*/
		
		shellwindow = nil;
		
		shellwindowinfo = nil;
		
		shellundostack = nil; /*7/21/91 dmb*/
		
#ifdef WIN95VERSION
		setport (NULL); // must clear port from prev globals
#endif

		return (false);
		}
	
	if (!getwindowinfo (w, &hinfo)) /*chase the refcon field of the mac window*/
		return (false);
	
	hw = hinfo; /*copy into register*/
	
	shellwindow = w; /*a global, this is the window whose globals are current*/
	
	shellwindowinfo = hw; /*the windowinfo record whose globals are current*/
	
	shellundostack = (hdlundostack) (**hw).hundostack;
	
	shellredostack = (hdlundostack) (**hw).hredostack;
	
	shellfindcallbacks ((**hw).configresnum, &ix);
	
	shellglobals = globalsarray [ix];
	
	config = shellglobals.config;
	
	*shellglobals.windowholder = w;
	
	*shellglobals.infoholder = hw;
	
	*shellglobals.dataholder = (**hw).hdata;
	
	(*shellglobals.setglobalsroutine) ();
	
	//You must call with a GrafPtr or CGrafPtr.
	//Code change by Timothy Paustian Wednesday, August 23, 2000 9:08:56 PM
	//
	{
	#if TARGET_API_MAC_CARBON
	CGrafPtr thePort = GetWindowPort(w);
 	#else
 	GrafPtr thePort = (GrafPtr)w;
 	#endif
	if (getport () != thePort) /*make sure w is current port; a courtesy to the content handler*/
		setport (thePort);
	}

	return (true);
	} /*shellsetglobals*/