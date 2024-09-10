void IGTabBar::drawTab (HDC hdc, UINT nSize, bool bSelected, bool bOver, const wchar_t *pcwTitle)
{
	Graphics graphics (hdc);
	Color colBackground (Color (GetRValue (m_cBackGround), GetGValue (m_cBackGround), GetBValue (m_cBackGround)));
	SolidBrush solBrushBackground (colBackground);
	graphics.FillRectangle (&solBrushBackground, Rect (0, 0, nSize, BUTTON_HEIGHT - 1));

	SolidBrush solBrushTab (bSelected ? IGTAB_COLORBACKGND : IGTAB_COLOR_UNSELECTED);
	GraphicsPath pathBorder;
	pathBorder.StartFigure();
	pathBorder.AddArc (Rect (0, 0, IGTAB_CORNERDIAM, IGTAB_CORNERDIAM), 180.0f, 90.0f);
	pathBorder.AddArc (Rect (nSize - IGTAB_CORNERDIAM, 0, IGTAB_CORNERDIAM, IGTAB_CORNERDIAM), -90.0f, 90.0f);
	pathBorder.AddLine (Point (nSize, BUTTON_HEIGHT + (bSelected ? 1 : 0)), Point (0, BUTTON_HEIGHT + (bSelected ? 1 : 0)));
	graphics.FillPath (&solBrushTab, &pathBorder);

	if (bOver)
	{
		PathGradientBrush pthGrBrush (&pathBorder);
		pthGrBrush.SetCenterPoint (PointF (0.7f * (float)nSize,
										  0.3f * (float)BUTTON_HEIGHT));
		pthGrBrush.SetCenterColor (IGTAB_COLOR_FRAMEIN);
		Color colors[] = {IGTAB_COLOR_FRAMEOUT};
		int count = 1;
		pthGrBrush.SetSurroundColors (colors, &count);
		graphics.FillPath (&pthGrBrush, &pathBorder);
	}

	FontFamily fontFamily(L"Times New Roman");
	Font font(&fontFamily, 16, FontStyleRegular, UnitPixel);
	PointF      pointF(20.0f, 5.0f);
	SolidBrush  solidFontBrush (bSelected ? IGTAB_COLOR_FONTENABLED : IGTAB_COLOR_FONTDISABLED);
	StringFormat	format(StringFormat::GenericDefault());
	format.SetAlignment (StringAlignmentCenter);
	graphics.DrawString (pcwTitle, -1, &font, RectF (0.0f, 0.0f, (float)nSize, (float)BUTTON_HEIGHT),
							&format, &solidFontBrush);

	Pen penBorder (IGTAB_COLORBORDER, 1);
	GraphicsPath pathBorderOut;
	pathBorderOut.StartFigure();
	pathBorderOut.AddArc (Rect (0, 0, IGTAB_CORNERDIAM + 1, IGTAB_CORNERDIAM + 1), 180.0f, 90.0f);
	pathBorderOut.AddArc (Rect (nSize - IGTAB_CORNERDIAM - 2, 0, IGTAB_CORNERDIAM + 1, IGTAB_CORNERDIAM + 1), -90.0f, 90.0f);
	pathBorderOut.AddLine (Point (nSize - 1, BUTTON_HEIGHT + (bSelected ? 1 : 0)), Point (0, BUTTON_HEIGHT + (bSelected ? 1 : 0)));
	pathBorderOut.CloseFigure();
	graphics.DrawPath (&penBorder, &pathBorderOut);
}