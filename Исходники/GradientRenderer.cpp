void CGradientRenderer::DrawGradient (CDC* pDC, HANDLE hndPrinter, CRect r, LINEARGRADIENTDATA* pLgd, CPreviewDC* pDCPreview)
{
	// normalize angle
	pLgd->dAngle = normalize_rad (pLgd->dAngle);

	Graphics graphics (pDC->GetSafeHdc (), hndPrinter);
	graphics.SetPageUnit (UnitPixel);
	graphics.SetSmoothingMode (SmoothingModeHighQuality);
	graphics.SetInterpolationMode (InterpolationModeHighQualityBicubic);
	graphics.SetPixelOffsetMode (PixelOffsetModeHighQuality);

	if ((pLgd->type != Linear) && (pLgd->type != Rectangular) && (pLgd->type != Radial_TopLeft))
	{
		Color color;
		color.SetFromCOLORREF (pLgd->colors[0]);
		Rect rect (r.left, r.top, r.Width (), r.Height ());
		LinearGradientBrush brush (rect, color, color, 0.0f);
		graphics.FillRectangle (&brush, rect);
	}

	GraphicsPath* pPath = NULL;
	Brush* pBrush = CGradient::CreateGradientBrush (r, *pLgd, &pPath);

	if (pPath == NULL)
		graphics.FillRectangle (pBrush, r.left, r.top, r.Width (), r.Height ());
	else
	{
		if (pLgd->type == Radial_TopLeft)
			graphics.FillRectangle (pBrush, r.left, r.top, r.Width (), r.Height ());
		else
			graphics.FillPath (pBrush, pPath);

		delete pPath;
	}

	delete pBrush;
}