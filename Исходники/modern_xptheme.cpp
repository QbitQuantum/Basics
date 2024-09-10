HRESULT	xpt_DrawTheme(XPTHANDLE xptHandle, HWND hwnd, HDC hdc, int type, int state, const RECT *sizeRect, const RECT *clipRect)
{
	mir_cslock lck(xptCS);
	if (xpt_IsThemed(xptHandle)) {
		if (IsThemeBackgroundPartiallyTransparent(((XPTObject*)xptHandle)->hThemeHandle, type, state)) {
			DrawThemeParentBackground(hwnd, hdc, sizeRect);
			return DrawThemeBackground(((XPTObject*)xptHandle)->hThemeHandle, hdc, type, state, sizeRect, clipRect);
		}
	}

	return S_FALSE;
}