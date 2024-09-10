void 
PF_FillPoly(PF_InData		*in_data,
			PF_ContextH		contextH,
			PolyHandle		poly)

{
#ifdef AE_OS_WIN
	HDC	hdc;
	HBRUSH Brush = GetStockObject(WHITE_BRUSH);
	PF_GET_CGRAF_DATA((*contextH)->cgrafptr, PF_CGrafData_HDC, &hdc);
	FillRgn(hdc, (HRGN)*poly, Brush);
#else
	FillPoly(poly, &in_data->qd_globals->gray);
#endif
}