static boolean tableverbresetrects (hdlwindowinfo hw) {
	
	register short scrollbarwidth;
	register hdltableformats hc = (hdltableformats) (**hw).hdata;
	hdloutlinerecord ho;
	Rect rcontent;
	Rect r;
	Rect tablerect, titlerect, wholerect;
	short msgheight;
	short titleheight = 12;
	#define seprectheight 4 /*height of rectangle separating titles from table content*/
	
	if (hc != nil) { // don't check outlinedata if tableformats aren't even attached yet
		
		ho = (**hc).houtline;
		
		if (ho == nil) // this emulates original return when outlinedata was nil
			return (false);
		
		if (isclaydisplay (hc))
			titleheight = 0;
		else
			titleheight = (**ho).defaultlineheight;
		}
	
	rcontent = (**hw).contentrect;
	
	/*set up some values for all rect computations*/ {
	
		scrollbarwidth = getscrollbarwidth ();
		
		msgheight = popupheight; 
		}
	
	/*do info.growiconrect*/ {
		
		shellcalcgrowiconrect (rcontent, hw);
		}
	
	/*do wholerect*/ {
		
		r = rcontent;
		
		r.top += tabletopmargin; /*three pixels between titles and top of window*/
		
		r.bottom -= msgheight + windowmargin;
		
		r.left += windowmargin;
		
		r.right -= windowmargin + iconrectwidth + windowmargin + scrollbarwidth;
		
		wholerect = r;
		}
	
	tablerect = wholerect;
	
	/*do titlerect*/ {
		
		titlerect = tablerect; /*set top, left, right*/
		
		titlerect.bottom = titlerect.top + titleheight;
		
		tablerect.top = titlerect.bottom + seprectheight;
		}
	
	if (hc != nil) {
		
		(**hc).wholerect = wholerect;
		
		(**hc).tablerect = tablerect;
		
		(**hc).titlerect = titlerect;
		}
	
	/*do kindpopuprect*/ {
		
		r.left = tablerect.left + 3; /*flush with left edge of icons*/
		
		r.right = r.left + popupwidth;
		
		r.top = tablerect.bottom + ((rcontent.bottom - tablerect.bottom - msgheight) / 2);
		
		r.bottom = r.top + msgheight;
		
		if (hc != nil)
			(**hc).kindpopuprect = r; 
		}
		
	/*do sortpopuprect*/ {
		
		r.left = r.right + popupbetweenwidth;
		
		r.right = r.left + popupwidth;
		
		if (hc != nil)
			(**hc).sortpopuprect = r;
		}
		
	/*do messagerect*/ {
		
		r.left = r.right + popupbetweenwidth;
		
		r.right = tablerect.right + scrollbarwidth;
		
		(**hw).messagerect = r; 
		}
		
	/*do iconrect*/ {
	
		r.top = tablerect.top;
		
		r.bottom = r.top + iconrectheight;
		
		r.right = rcontent.right - windowmargin;
		
		r.left = r.right - iconrectwidth;
		
		if (iconrectwidth > 0)
			insetrect (&r, -4, 0); /*a little extra width for title*/
		
		if (hc != nil)
			(**hc).iconrect = r; 
		}
		
	/*do vertscrollbar*/ {
		
		r = tablerect; /*the space occupied by the grid of cells*/
		
		r.left = r.right; /*scrollbar is just to right of grid*/
		
		r.right = r.left + scrollbarwidth;
		
		setscrollbarrect ((**hw).vertscrollbar, r);
		
		showscrollbar ((**hw).vertscrollbar);
		}
	
	return (true);
	} /*tableverbresetrects*/