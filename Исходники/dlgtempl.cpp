AFX_STATIC void AFXAPI _AfxConvertDialogUnitsToPixels(LPCTSTR pszFontFace, WORD wFontSize,
	int cxDlg, int cyDlg, SIZE* pSizePixel)
{
	// Attempt to create the font to be used in the dialog box
	UINT cxSysChar, cySysChar;
	LOGFONT lf;
	HDC hDC = ::GetDC(NULL);
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = -MulDiv(wFontSize, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	lf.lfWeight = FW_NORMAL;
	lf.lfCharSet = DEFAULT_CHARSET;
	Checked::tcsncpy_s(lf.lfFaceName, _countof(lf.lfFaceName), pszFontFace, _TRUNCATE);

	HFONT hNewFont = CreateFontIndirect(&lf);
	if (hNewFont != NULL)
	{
		HFONT hFontOld = (HFONT)SelectObject(hDC, hNewFont);
		TEXTMETRIC tm;
		GetTextMetrics(hDC, &tm);
		cySysChar = tm.tmHeight + tm.tmExternalLeading;
		SIZE size;
		::GetTextExtentPoint32(hDC,
			_T("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"), 52,
			&size);
		cxSysChar = (size.cx + 26) / 52;
		SelectObject(hDC, hFontOld);
		DeleteObject(hNewFont);
	}
	else
	{
		// Could not create the font so just use the system's values
		cxSysChar = LOWORD(GetDialogBaseUnits());
		cySysChar = HIWORD(GetDialogBaseUnits());
	}
	::ReleaseDC(NULL, hDC);

	// Translate dialog units to pixels
	pSizePixel->cx = MulDiv(cxDlg, cxSysChar, 4);
	pSizePixel->cy = MulDiv(cyDlg, cySysChar, 8);
}