static int DrawTextUtf(HDC hDC, char *text, LPRECT lpRect, UINT uFormat, LPSIZE lpSize)
{
	int res;

	WCHAR *tmp = make_unicode_string(text);
	res = DrawTextW(hDC, tmp, -1, lpRect, uFormat);
	if (lpSize)
		GetTextExtentPoint32W(hDC, tmp, (int)mir_wstrlen(tmp), lpSize);
	SAFE_FREE((void**)&tmp);

	return res;
}