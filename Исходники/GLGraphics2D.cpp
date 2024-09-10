void GLFont::buildBaseImage( int size , char const* faceName , HDC hDC )
{
	mSize = size;

	HFONT	font;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	mIdBaseList = glGenLists(96);								// Storage For 96 Characters

	int height = -(int)(fabs( ( float)10 * size *GetDeviceCaps( hDC ,LOGPIXELSY)/72)/10.0+0.5);
	

	font = CreateFontA(	
		height ,					    // Height Of Font
		0,								// Width Of Font
		0,								// Angle Of Escapement
		0,								// Orientation Angle
		FW_BOLD,						// Font Weight
		FALSE,							// Italic
		FALSE,							// Underline
		FALSE,							// Strikeout
		ANSI_CHARSET,					// Character Set Identifier
		OUT_TT_PRECIS,					// Output Precision
		CLIP_DEFAULT_PRECIS,			// Clipping Precision
		ANTIALIASED_QUALITY,			// Output Quality
		FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
		faceName );			    // Font Name

	
	oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want
	wglUseFontBitmaps(hDC, 32, 96, mIdBaseList);	    // Builds 96 Characters Starting At Character 32
	SelectObject(hDC, oldfont);							// Selects The Font We Want
	DeleteObject(font);									// Delete The Font
}