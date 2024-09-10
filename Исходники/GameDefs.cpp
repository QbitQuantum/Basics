int GameClass::LoadStandardFont(char* name,int height,int flags,int italic)
{
	HFONT	hFont;

	StdFontBase=glGenLists(MAX_CHARS);

	size_t length=strlen(name);
	wchar_t* newStr = new wchar_t[length+1];
	mbtowc(newStr,name,length+1);
	hFont=CreateFont(	height,16,0,0,
						flags,
						italic,
						FALSE,FALSE,
						ANSI_CHARSET,
						OUT_TT_PRECIS,
						CLIP_DEFAULT_PRECIS,
						ANTIALIASED_QUALITY,
						FF_DONTCARE|DEFAULT_PITCH,
						newStr);
	delete [] newStr;

	if(!hFont)
		return 0;

	hOldFont=(HFONT)SelectObject(GLWindow.Settings.hDC,hFont);

	wglUseFontBitmaps(GLWindow.Settings.hDC,0,MAX_CHARS-1,StdFontBase);

	return 1;
}