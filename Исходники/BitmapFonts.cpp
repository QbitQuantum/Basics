void CBitmapFonts::Build(HDC hDC, char *FontName, int *pbase, int FontSize, CBitmapFontSettings *pSettings)
{
	HFONT  font;	
	// Base of the font texture ID
	base = *pbase;

	SetSettings(pSettings);

	// Generate storage for 96 chars
	glGenLists(MaxFont);	

	// Create/Load the font
	font = CreateFontA(FontSize*(-1),// Height Of Font
					  0,			// Width Of Font
					  0,			// Angle Of Escapement
					  0,			// Orientation Angle
					  /*FW_THIN*/FW_BOLD,// Font Weight
					  FALSE,	// Italic
					  FALSE,	// Underline
					  FALSE,	// Strikeout
					  ANSI_CHARSET,// Character Set Identifier
					  OUT_TT_PRECIS,// Output Precision
					  CLIP_DEFAULT_PRECIS,// Clipping Precision
					  ANTIALIASED_QUALITY,// Output Quality
					  FF_DONTCARE|DEFAULT_PITCH,// Family And Pitch
					  FontName);// Font Name

	// Selects The Font We Want
	SelectObject(hDC, font);

	// Builds 96 characters starting at character 32 (space)
	wglUseFontBitmaps(hDC, 32, MaxFont, base);

	*pbase += MaxFont;
}