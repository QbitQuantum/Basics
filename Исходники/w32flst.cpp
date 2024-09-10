MCFontnode::MCFontnode(const MCString &fname, uint2 &size,
                       uint2 style, Boolean printer)
{
	reqname = fname.clone();
	reqsize = size;
	reqstyle = style;
	reqprinter = printer;
	font = new MCFontStruct;
	if (MCnoui)
	{
		memset(font, 0, sizeof(MCFontStruct));
		return;
	}
	LOGFONTA logfont;
	memset(&logfont, 0, sizeof(LOGFONTA));
	uint4 maxlength = MCU_min(LF_FACESIZE - 1U, fname.getlength());
	strncpy(logfont.lfFaceName, fname.getstring(), maxlength);
	logfont.lfFaceName[maxlength] = '\0';

	// MW-2012-05-03: [[ Bug 10180 ]] Make sure the default charset for the font
	//   is chosen - otherwise things like WingDings don't work!
	logfont.lfCharSet = DEFAULT_CHARSET;

	//parse font and encoding
	char *sptr = logfont.lfFaceName;
	if (sptr = strchr(logfont.lfFaceName, ','))
	{
		*sptr = '\0';
		sptr++;
	}
	HDC hdc;

	// MW-2013-11-07: [[ Bug 11393 ]] 'printer' in the fontstruct now means use ideal
	//   metrics for rendering and measuring.
	MCScreenDC *pms = (MCScreenDC *)MCscreen;
	hdc = pms->getsrchdc();
	logfont.lfHeight = MulDiv(MulDiv(size, 7, 8),
	                          SCREEN_WIDTH_FOR_FONT_USE, 72);

	logfont.lfWeight = weighttable[MCF_getweightint(style)];
	if (style & FA_ITALIC)
		logfont.lfItalic = TRUE;
	if (style & FA_OBLIQUE)
		logfont.lfOrientation = 3600 - 150; /* 15 degree forward slant */
	
	HFONT newfont = CreateFontIndirectA(&logfont);
	SelectObject(hdc, newfont);
	char testname[LF_FACESIZE];
	memset(testname, 0, LF_FACESIZE);
	GetTextFaceA(hdc, LF_FACESIZE, testname);

	// MW-2012-02-13: If we failed to find an exact match then remap the font name and
	//   try again.
	if (newfont == NULL || (MCU_strncasecmp(testname, logfont.lfFaceName, strlen(testname) + 1)))
	{
		if (newfont != NULL)
			DeleteObject(newfont);

		mapfacename(logfont.lfFaceName, logfont.lfFaceName, printer == True);

		// Force the resulting font to be TrueType and with ANSI charset (otherwise
		// we get strange UI symbol font on XP).
		logfont.lfCharSet = ANSI_CHARSET;
		logfont.lfOutPrecision = OUT_TT_ONLY_PRECIS;
		newfont = CreateFontIndirectA(&logfont);
		SelectObject(hdc, newfont);
	}

	// At this point we will have either found an exact match for the textFont, mapped
	// using the defaults table and found a match, or been given a default truetype font.

	TEXTMETRICA tm;
	GetTextMetricsA(hdc, &tm);
	font->fid = (MCSysFontHandle)newfont;
	font->size = size;
	// MW-2013-12-19: [[ Bug 11606 ]] Use Mac-style metric adjustment in printer (ideal
	//   layout mode).
	if (!printer)
	{
		font->ascent = MulDiv(tm.tmAscent, 15, 16);
		font->descent = tm.tmDescent;
	}
	else
	{
		font -> ascent = size - 1;
		font -> descent = size * 2 / 14 + 1;
	}
	font->printer = printer;
}