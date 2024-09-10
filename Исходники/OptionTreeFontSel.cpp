void COptionTreeFontSel::ConvertFont(LOGFONT &lf, CHARFORMAT &cfFont)
{
	// Declare variables
	CDC dc;
	dc.CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	long yPerInch = dc.GetDeviceCaps(LOGPIXELSY);


	// Create log font
	// -- Font name
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfQuality = DEFAULT_QUALITY;
	lf.lfPitchAndFamily = cfFont.bPitchAndFamily;
	_tcscpy(lf.lfFaceName, cfFont.szFaceName);
	// -- Size
	lf.lfHeight = abs(((cfFont.yHeight * yPerInch) / 1440));
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	// -- Bold
	if (cfFont.dwEffects & CFE_BOLD)
	{
		lf.lfWeight = FW_BOLD;
	}
	else
	{
		lf.lfWeight = FW_NORMAL;
	}
	// -- Strikeout
	if (cfFont.dwEffects & CFE_STRIKEOUT)
	{
		lf.lfStrikeOut = TRUE;
	}
	else
	{
		lf.lfStrikeOut = FALSE;
	}
	// -- Underline
	if (cfFont.dwEffects & CFE_UNDERLINE)
	{
		lf.lfUnderline = TRUE;
	}
	else
	{
		lf.lfUnderline = FALSE;
	}
	// -- Italic
	if (cfFont.dwEffects & CFE_ITALIC)
	{
		lf.lfItalic = TRUE;
	}
	else
	{
		lf.lfItalic = FALSE;
	}
}