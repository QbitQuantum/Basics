static boolean dockmenuinsertmenuitem (hdlmenu hmenu, short itemnumber, hdlheadrecord hnode) {

	/*
	Insert one menu item.

	7.1b42 PBS: check menu items that should be checked.
	*/
	
	bigstring bsheadstring;
	boolean flenabled = true;
	boolean flchecked = false;

	getheadstring (hnode, bsheadstring);

	mereduceformula (bsheadstring);
	
	mereducemenucodes (bsheadstring, &flenabled, &flchecked); /*7.0b23 PBS: items can be disabled.*/

	pushpopupitem (hmenu, bsheadstring, flenabled, menuid);

	#if TARGET_API_MAC_CARBON == 1
	
		SetMenuItemCommandID (hmenu, countmenuitems (hmenu), menuid);
		
	#endif

	if (flchecked) /*7.1b42 PBS: support for checked menu items.*/
		checkmenuitem (hmenu, countmenuitems (hmenu), flchecked);

	if (!opnosubheads (hnode)) /*has subs?*/
		dockmenuinsertsubmenu (hmenu, itemnumber, hnode);

	#ifdef MACVERSION
		flstackneedsdisposing = true;
	#endif

	return (true);
	} /*dockmenuinsertmenuitem*/