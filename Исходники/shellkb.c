void shellhandlekeystroke (void) {
	
	/*
	if it's a cmd-key we first offer it to the frontmost window, if he doesn't
	consume it, we pass it on to the menubar.
	
	if it's shift-enter, we close the frontmost window.
	
	otherwise we pass the keystroke to the front window's handler.
	
	7/18/90 DW: add hooks.  they're allowed to consume a keystroke by returning
	false.
	
	11/8/90 DW: add support for style keys -- cmd-shift BIOUS.
	
	12/6/91 dmb: give menubar priority over cmdkeyfilter
	*/
	
	unsigned int chkb;
	#ifdef MACVERSION	
		register boolean fl;
		long codeword;
	#endif
	
	timelastkeystroke = gettickcount ();
	
	setkeyboardstatus (shellevent.message, shellevent.what, shellevent.modifiers); /*fill keyboardstatus record with info about the event*/
	
	if (!keyboardstatus.flautokey)	/*4.0b7 dmb: new non-repeating ouchs*/
		flouchlocked = false;

#ifdef MACVERSION	
	if (shellfilterfunctionkey (&codeword) || shellfilterfontkey (&codeword)) {
		
		fl = shellpushfrontglobals ();
		
		shellupdatemenus ();
		
		HiliteMenu (HiWord (codeword));
		
		shellhandlemenu (codeword);
		
		if (fl)
			shellpopglobals ();
			
		return;
		}
#endif
	
	if (!shellcallkeyboardhooks ())
		return;
	
	chkb = keyboardstatus.chkb; /*move into register*/

#ifdef MACVERSION	
	if (keyboardstatus.flcmdkey && (chkb >= chspace)) {
		
		if (chkb == '.') { /*cmd-period is consumed here*/
		
			keyboardsetescape ();
			
			return;
			}
		
		/*
		if (shellpushfrontglobals ()) { /%a window is open%/
			
			fl = (*shellglobals.cmdkeyfilterroutine) (keyboardstatus.chkb);
			
			shellpopglobals ();
			
			if (!fl) /%cmd-key was consumed%/
				return;
			}
		*/
		
		fl = shellpushfrontglobals ();
		
		shellupdatemenus (); /*be sure the menus are properly checked and highlighted*/
		
		if (!shellhandlemenu (MenuKey (chkb))) { /*cmd-key not consumed by menubar*/
			
			if (fl)
				(*shellglobals.cmdkeyfilterroutine) (chkb);
			}
		
		if (fl)
			shellpopglobals ();
		
		return;
		}
#endif
		
	if (shellpushfrontglobals ()) { /*a window is open to close or receive keystroke*/
	
		if (shellcalleventhooks (&shellevent, shellwindow)) /*keystroke wasn't consumed*/
			(*shellglobals.keystrokeroutine) ();
		
		shellpopglobals ();
		}
	} /*shellhandlekeystroke*/