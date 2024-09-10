    QRenderedFontFT(QDiskFont* f, const QFontDef &d) :
	QRenderedFont(f,d)
    {
	QDiskFontFT *df = (QDiskFontFT*)(f->p);
	myface=df->face;
	selectThisSize();
	// A 1-pixel baseline is excluded in Qt/Windows/X11 fontmetrics
	// (see QFontMetrics::height())
	//
	fascent=CEIL(myface->size->metrics.ascender)/64;
	fdescent=-FLOOR(myface->size->metrics.descender)/64-1;
	fmaxwidth=CEIL(myface->size->metrics.max_advance)/64;
	fleading=CEIL(myface->size->metrics.height)/64
	    - fascent - fdescent - 1;

	// FT has these in font units
	funderlinepos = ptsize/200+1;
	funderlinewidth = ptsize/200+1;
    }