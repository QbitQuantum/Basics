void COptionTree::InitGlobalResources()
{
	// Declare variables
	CWindowDC dc(NULL);
	NONCLIENTMETRICS cmInfo;
	cmInfo.cbSize = sizeof(cmInfo);
	LOGFONT lfFont;
	BOOL bUseSystemFont;

	// Delete global resources
	DeleteGlobalResources();
	
	// Get system parameter information
	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(cmInfo), &cmInfo, 0);

	// Initialize logfont
	memset(&lfFont, 0, sizeof(LOGFONT));
	lfFont.lfCharSet = (BYTE)GetTextCharsetInfo(dc.GetSafeHdc(), NULL, 0);
	lfFont.lfHeight = cmInfo.lfMenuFont.lfHeight;
	lfFont.lfWeight = cmInfo.lfMenuFont.lfWeight;
	lfFont.lfItalic = cmInfo.lfMenuFont.lfItalic;

	// Check if we should use system font
	//_tcscpy(lfFont.lfFaceName, cmInfo.lfMenuFont.lfFaceName);//#OBSOLETE
	_tcscpy_s(lfFont.lfFaceName, sizeof(lfFont.lfFaceName),cmInfo.lfMenuFont.lfFaceName);

	// Use system font
	bUseSystemFont = (cmInfo.lfMenuFont.lfCharSet > SYMBOL_CHARSET);
	if (!bUseSystemFont)
	{
		// -- Check for "Tahoma" font existance:
		if (::EnumFontFamilies(dc.GetSafeHdc(), NULL, _FontFamilyProcFonts, 0) == 0)
		{
			// -- -- Found! Use MS Office font
			//_tcscpy(lfFont.lfFaceName, _T("Tahoma"));//#OBSOLETE
			_tcscpy_s(lfFont.lfFaceName, sizeof(lfFont.lfFaceName), _T("Tahoma"));
		}
		else
		{
			// -- -- Not found. Use default font
			//_tcscpy(lfFont.lfFaceName, _T("MS Sans Serif"));//#OBSOLETE
			_tcscpy_s(lfFont.lfFaceName, sizeof(lfFont.lfFaceName), _T("MS Sans Serif"));
		}
	}

	// Normal font
	m_fNormalFont = new CFont;
	m_fNormalFont->CreateFontIndirect(&lfFont);

	// Bold font
	lfFont.lfWeight = FW_BOLD;
	m_fBoldFont = new CFont;
	m_fBoldFont->CreateFontIndirect(&lfFont);
}