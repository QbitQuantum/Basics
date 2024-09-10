void SetHIMETRICtoDP(HDC hdc, SIZE* sz)
{
	POINT pt;
	int nMapMode = GetMapMode(hdc);
	if (nMapMode < MM_ISOTROPIC && nMapMode != MM_TEXT) {
		// when using a constrained map mode, map against physical inch
		SetMapMode(hdc, MM_HIMETRIC);
		pt.x = sz->cx;
		pt.y = sz->cy;
		LPtoDP(hdc, &pt, 1);
		sz->cx = pt.x;
		sz->cy = pt.y;
		SetMapMode(hdc, nMapMode);
	}
	else {
		// map against logical inch for non-constrained mapping modes
		int cxPerInch, cyPerInch;
		cxPerInch = GetDeviceCaps(hdc, LOGPIXELSX);
		cyPerInch = GetDeviceCaps(hdc, LOGPIXELSY);
		sz->cx = MulDiv(sz->cx, cxPerInch, HIMETRIC_INCH);
		sz->cy = MulDiv(sz->cy, cyPerInch, HIMETRIC_INCH);
	}

	pt.x = sz->cx;
	pt.y = sz->cy;
	DPtoLP(hdc, &pt, 1);
	sz->cx = pt.x;
	sz->cy = pt.y;
}