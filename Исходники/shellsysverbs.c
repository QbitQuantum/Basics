static boolean getscrapverb (hdltreenode hparam1, tyvaluerecord *v) {
	
	/*
	5.0a10 dmb: must open/close clipboard. byte swap binary type
	*/

	OSType type;
	Handle hscrap;
	hdlhashtable htable;
	bigstring bs;
	boolean fl = false;
		
	setbooleanvalue (false, v); /*default return*/
	
	if (!getostypevalue (hparam1, 1, &type))
		return (false);
	
	flnextparamislast = true;
	
	if (!getvarparam (hparam1, 2, &htable, bs)) /*returned handle holder*/
		return (false);
	
	shellwritescrap (anyscraptype); /*export our private scrap, in necessary*/
	
	if (!newemptyhandle (&hscrap))
		return (false);
	
	if (openclipboard ()) {
		
		fl = getscrap (type, hscrap);
		
		closeclipboard ();
		}
	
	if (!fl) {
		
		disposehandle (hscrap);
		
		return (true); /*not a runtime error; return value is false*/
		}
	
	memtodisklong (type);
	
	if (!insertinhandle (hscrap, 0L, &type, sizeof (type))) {
		
		disposehandle (hscrap);
		
		return (false);
		}
	
	if (!langsetbinaryval (htable, bs, hscrap)) /*probably a memory error*/
		return (false);
	
	(*v).data.flvalue = true;
	
	return (true);
	} /*getscrapverb*/