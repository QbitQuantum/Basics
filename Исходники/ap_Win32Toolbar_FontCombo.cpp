bool AP_Win32Toolbar_FontCombo::populate(void)
{
	// clear anything that's already there
	m_vecContents.clear();
	m_vecFontCharSet.clear();

	seenFonts.clear();

	// populate the vector
	HWND hwnd = NULL;
    HDC hdc = GetDC(hwnd) ;
	LOGFONTW lf;
	lf.lfCharSet=DEFAULT_CHARSET;
	*lf.lfFaceName=0;
	lf.lfPitchAndFamily=0;
    EnumFontFamiliesExW(hdc, &lf, (FONTENUMPROCW) AP_Win32Toolbar_FontCombo::_EnumFontsProc, (LONG_PTR) this, 0) ;
    ReleaseDC(hwnd, hdc) ;

	seenFonts.clear();

	return true;
}