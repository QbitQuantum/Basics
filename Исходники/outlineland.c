static boolean drawline (hdlheadrecord hnode) {
	
	register hdlheadrecord h = hnode;
	Point pt;
	Rect r;
	short listnum;
	short iconnum;
	tyfinderinfo info;
	byte typestring [6];
	boolean fltextmode = opeditingtext (hnode);
	
	opgetrefcon (hnode, &info, sizeof (info));
	
	GetPen (&pt);
	
	setrect (&r, pt.v - 12, pt.h - 2, pt.v + 4, pt.h + 14);
	
	listnum = findersmalliconlist;
	
	if (fltextmode)
		++listnum;
	
	plotsmallicon (r, listnum, geticonnum (h), false);
	
	movepento (pt.h + widthsmallicon, pt.v);
	
	if (info.flalias)		
 		pushstyle ((**outlinedata).fontnum, (**outlinedata).fontsize, italic);
	
	if (fltextmode)
		opeditupdate ();
	else
		pendrawstring ((**h).headstring);
	
	if (info.flalias)
		popstyle (); 
	
	movepento (pt.h + namecolwidth, pt.v);
	
	ostypetostring (info.filetype, typestring);
	
	pendrawstring (typestring);
	
	return (true);
	} /*drawline*/