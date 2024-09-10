boolean clickcolorpopup (Point pt, RGBColor *rgb) {
	
	long result;
	short lo, hi;
	
	if (!flpopupinit)
		flpopupinit = initcolorpopup ();
	
	setcursortype (cursorisarrow);
	
	CalcMenuSize (colormenu);
	
	InsertMenu (colormenu, hierMenu);

	LocalToGlobal (&pt);
	
	result = PopUpMenuSelect (colormenu, pt.v, pt.h, -1);

	DeleteMenu ((**colormenu).menuID);
	
	lo = LoWord (result);
	
	hi = HiWord (result);
	
	if (hi > 0) { /*something was selected*/
	
		*rgb = (*ctable) [lo - 1].rgb;
		
		return (true);
		}
	
	return (false);
	} /*clickcolorpopup*/