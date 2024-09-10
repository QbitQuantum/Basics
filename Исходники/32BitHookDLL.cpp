BOOL WINAPI ShadowExtTextOutW(HDC textdc, int x, int y, UINT fuoptions, CONST RECT *lprc, LPCWSTR lptext, UINT cb, CONST INT *lpdx)
{
	char szText[MAXTEXTOUT] = NULLSTR;
	int iLenText = 0;
	BOOL bRet = FALSE;
	BOOL bUsed = FALSE;

	// write to text buffer if it isnt a glyph
	if ((fuoptions & ETO_GLYPH_INDEX) != ETO_GLYPH_INDEX)
	{
		iLenText = WideCharToMultiByte(CP_THREAD_ACP, WC_NO_BEST_FIT_CHARS, lptext, cb, szText, MAXTEXTOUT, "*", &bUsed);
		WriteToTextBuffer((LPCSTR)szText, (UINT)iLenText);
	}

	// pass on call to real function
	UnhookFunction((PHOOKREC)&_hrExtTextOutW);
	bRet = ExtTextOutW(textdc, x, y, fuoptions, lprc, lptext, cb, lpdx);
	HookFunction((PHOOKREC)&_hrExtTextOutW);

	return bRet;
}