EXPORT BOOL SetInlinePosition(HWND hWnd, int x, int y, int font_height)
{
	BOOL ret = FALSE;
	HIMC hIMC = ImmGetContext(hWnd);

	if (ImmGetOpenStatus(hIMC)) {
		COMPOSITIONFORM cf = {0};
		cf.dwStyle = CFS_POINT;
		cf.ptCurrentPos.x = x;
		cf.ptCurrentPos.y = y;
		if (ImmSetCompositionWindow(hIMC, &cf)) {
			LOGFONTW lf = {0};
			lf.lfHeight = font_height;
			// lf.lfFaceName = font_face;
			if (ImmSetCompositionFontW(hIMC, &lf)) {
				ret = TRUE;
			}
		}
	}

	ImmReleaseContext(hWnd, hIMC);
	return ret;
}