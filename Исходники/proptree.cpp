void CPropTree::InitGlobalResources( bool bFontBold )
{
	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);
#if (WINVER >= 0x0600)
	ncm.cbSize -= 4; //<== ADD HERE!! 
#endif
	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(info), &info, 0);

	LOGFONT lf;
	memset(&lf, 0, sizeof (LOGFONT));

	CWindowDC dc(NULL);
	lf.lfCharSet = (BYTE)GetTextCharsetInfo(dc.GetSafeHdc(), NULL, 0);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	// check if we should use system font
	_ncscpy(lf.lfFaceName, info.lfMenuFont.lfFaceName);

	BOOL fUseSystemFont = (info.lfMenuFont.lfCharSet > SYMBOL_CHARSET);
	if (!fUseSystemFont)
	{
		// check for "Tahoma" font existance:
		if (::EnumFontFamilies(dc.GetSafeHdc(), NULL, FontFamilyProcFonts, 0)==0)
		{
			// Found! Use MS Office font!
			_tcscpy_s(lf.lfFaceName, strOfficeFontName);
		}
		else
		{
			// Not found. Use default font:
			_tcscpy_s(lf.lfFaceName, strDefaultFontName);
		}
	}

	s_pNormalFont = new CFont;
	s_pNormalFont->CreateFontIndirect(&lf);

	if( bFontBold )
		lf.lfWeight = FW_DEMIBOLD;		

	s_pBoldFont = new CFont;
	s_pBoldFont->CreateFontIndirect(&lf);
}