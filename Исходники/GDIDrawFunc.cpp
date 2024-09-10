void GPDrawShadowTextSimple( Graphics&gc, CString& strTxtIn, CRect& rcIn, Gdiplus::Font& fontIn, ARGB BrushClrIn, ARGB shadowBrushClrIn /*= 0xff000000*/, int nOffXIn /*= 2*/, int nOffYIn /*= 2*/, StringFormat* fmtIn /*= NULL*/ )
{
	Gdiplus::Font& gcfont = fontIn;
	Rect rcText = CRect2Rect(rcIn);
	StringFormat fmt;
	fmt.SetAlignment(StringAlignmentCenter);
	fmt.SetTrimming(StringTrimmingEllipsisWord);
	fmt.SetLineAlignment(StringAlignmentCenter);
	StringFormat& fmtUse = fmtIn == NULL? fmt:*fmtIn;

	GraphicsContainer  gcContainer = gc.BeginContainer();
	gc.SetSmoothingMode(SmoothingModeAntiAlias);
	CComBSTR btrTxtIn(strTxtIn);

	SolidBrush textbrush(ARGB2Color(shadowBrushClrIn));
	RectF rfText = Rect2RectF(rcText);
	if (shadowBrushClrIn != 0)
	{
		rfText.Offset(1.0, 1.0);
		gc.DrawString(btrTxtIn, -1, &gcfont, rfText, &fmtUse, &textbrush);
	}

	textbrush.SetColor(ARGB2Color(BrushClrIn));
	gc.DrawString(btrTxtIn, -1, &gcfont, rfText, &fmtUse, &textbrush);
	gc.EndContainer(gcContainer);
}