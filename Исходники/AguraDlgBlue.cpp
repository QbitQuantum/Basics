void CAguraDlgBlue::gradationCenter(Graphics& g, CRect rt, Color& color1, Color& color2, BOOL bLine, Color& color3)
{
	GraphicsPath gPath;

	int iHeight = rt.Width() / 4;
	int iWidth = rt.Width() / 4;

	RectF rtF((REAL)rt.left - iWidth, (REAL)rt.top - iHeight, (REAL)rt.Width() + iWidth * 2, (REAL)rt.Height() + iHeight * 2);
	gPath.AddEllipse(rtF);
	gPath.CloseFigure();

	PathGradientBrush PGB(&gPath);
	PGB.SetCenterColor(color1); //would be some shade of blue, following your example
	int colCount = 1;
	PGB.SetSurroundColors(&color2, &colCount); //same as your center color, but with the alpha channel set to 0

	//play with these numbers to get the glow effect you want
	REAL blendFactors[] = {0.0f, 0.1f, 0.3f, 1.0f};
	REAL blendPos[] = {0.0f, 0.4f, 0.6f, 1.0f};
	//sets how transition toward the center is shaped
	PGB.SetBlend(blendFactors, blendPos, 4);
	//sets the scaling on the center. you may want to have it elongated in the x-direction
	PGB.SetFocusScales(0.2f, 0.2f);

	RectF rtDraw((REAL)rt.left, (REAL)rt.top, (REAL)rt.Width(), (REAL)rt.Height());
	g.FillRectangle(&PGB, rtDraw);

	if (bLine == TRUE)
	{
		Pen pen(color3, 1);
		g.DrawRectangle(&pen, rtDraw);
	}
}