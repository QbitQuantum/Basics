static boolean langerrornewwindow (void) {
	
	/*
	5.0.2b3 dmb: added inhibiterrorclear logic to make sure zooming doesn't 
	clear us
	
	6.2b6 AR: Extended inhibiterrorclear protection so that langerrorlcear doesn't interfer
	*/
	
	hdlwindowinfo hw;
	WindowPtr w;
	bigstring bstitle;
	Rect rzoom, rwindow;
	hdlwindowinfo hparent;
	tylangerrorrecord **hdata;
	boolean fl = false;
	
	++inhibiterrorclear; // protect us from other threads while we're still busy creating the window
	
	if (!shellgetfrontrootinfo (&hparent)) /*our parent is the frontmost root window*/
		goto exit;
			
	shellgetwindowcenter (hparent, &rzoom);
	
	if (pendingerrordata != nil) {
		
		hdata = pendingerrordata;
		
		pendingerrordata = nil;
		}
	else {
		
		if (!newclearhandle (sizeof (tylangerrorrecord), (Handle *) &hdata))
			goto exit;
		}
	
	langerrorgetwindowrect (&rwindow);
	
	getstringlist (langerrorlistnumber, langerrortitlestring, bstitle);
	
	if (!newchildwindow (idlangerrorconfig, hparent, &rwindow, &rzoom, bstitle, &w)) {
		
		disposehandle ((Handle) hdata);
		
		goto exit;
		}
		
	getwindowinfo (w, &hw);
	
	(**hw).hdata = (Handle) hdata;
	
	ccnewsubwindow (hw, ixlangerrorinfo);
	
	windowzoom (w);

	fl = true;
	
exit:
	
	--inhibiterrorclear;
	
	return (fl);
	} /*langerrornewwindow*/