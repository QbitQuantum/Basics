void CBarShader::FillRect(CDC *dc, LPRECT rectSpan, COLORREF color, bool bFlat) {
	if(!color || bFlat)
		dc->FillRect(rectSpan, &CBrush(color));
	else
		FillRect(dc, rectSpan, GetRValue(color), GetGValue(color), GetBValue(color), false);
}