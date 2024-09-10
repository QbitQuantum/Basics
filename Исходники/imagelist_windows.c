static SIZE getStateSize(HDC dc, int cbState, HTHEME theme)
{
	SIZE s;
	HRESULT res;

	res = GetThemePartSize(theme, dc, BP_CHECKBOX, themestates[cbState], NULL, TS_DRAW, &s);
	if (res != S_OK)
		xpanichresult("error getting theme part size", res);
	return s;
}