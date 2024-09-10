void opdraggingmove (Point ptstart, hdlheadrecord hsource) {
	
	/*
	9/22/93 dmb: need to validate a drag just like a copy. also need to 
	provide for client sorting, like a paste
	*/
	
	long tc = 0;
	tyhotspot hotspot;
	Point pt;
	tydirection dir;
	
	if (!((**outlinedata).validatecopycallback) (STR_move))
		return;
	
	clearbytes ((ptrchar) &hotspot, longsizeof (hotspot));
	
	hotspot.pt = ptstart;
	
	hotspot.hsource = hsource;
	
	/*
	opgetwindowhandle (pt, &hotspot.sourcewindowhandle);
	
	hotspot.destwindowhandle = hotspot.sourcewindowhandle;
	*/
	
	if (true /*claystartdrag(ptstart, hsource) != noErr*/) {
		
		while (mousestilldown ()) {
			
			getmousepoint (&pt);
			
			#if false
			
				Handle currentwindow;
			
				if (!pointinrect (pt, (*FrontWindow ()).portRect))
					Debugger ();
			
				opgetwindowhandle (pt, &currentwindow);
				
				if (currentwindow != hotspot.destwindowhandle) { /*pointing into another window*/
					
					opsetwindowhandlecontext (hotspot.destwindowhandle);
			
					operasehotspot (&hotspot);
					
					hotspot.destwindowhandle = currentwindow;
					
					opsetwindowhandlecontext (hotspot.destwindowhandle);
			
					opupdatehotspot (ptstart, pt, &hotspot);
					}
			#endif
			
			if ((gettickcount () - tc) > draggingscrollrate) {
				
				if (mousecheckautoscroll (pt, (**outlinedata).outlinerect, false, &dir)) {
				
					opscrollfordrag (&hotspot, dir);
					
					tc = gettickcount ();
					}
				}
			
			opupdatehotspot (ptstart, pt, &hotspot);
			} /*while*/
		
		operasehotspot (&hotspot); /*user let up on the button*/
	
		opmovetohotspot (&hotspot);
		}  // if noErr
	} /*opdraggingmove*/