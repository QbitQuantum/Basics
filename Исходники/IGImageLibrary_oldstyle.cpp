HRESULT CIGImageLibrary::OnDraw(ATL_DRAWINFO& di)
{
	Graphics graphics (di.hdcDraw);
	// Middle part
	GraphicsPath path;
	path.AddRectangle (RectF (0, 0,
							IGIMAGELIBRARY_WIDTH, IGIMAGELIBRARY_HEIGHT));
	PathGradientBrush pthGrBrush (&path);
	pthGrBrush.SetCenterPoint (PointF (0.7f * (float)IGIMAGELIBRARY_WIDTH,
									  0.3f * (float)IGIMAGELIBRARY_HEIGHT));
	pthGrBrush.SetCenterColor (IGIMAGELIBRARY_COLOR_FRAMEIN);
	Color colors[] = {IGIMAGELIBRARY_COLOR_FRAMEOUT};
	int count = 1;
	pthGrBrush.SetSurroundColors(colors, &count);
	graphics.FillPath (&pthGrBrush, &path);

	// Left part
	LinearGradientBrush linLeftGrBrush (PointF(0,0), PointF((float)IGIMAGELIBRARY_BORDERWIDTH / 2.0f, 0),
							IGIMAGELIBRARY_COLOR_BORDEROUT, IGIMAGELIBRARY_COLOR_BORDERMIDDLE);	
	graphics.FillRectangle (&linLeftGrBrush, RectF (0, 0,
							(float)IGIMAGELIBRARY_BORDERWIDTH / 2.0f,
							IGIMAGELIBRARY_HEIGHT - IGIMAGELIBRARY_CORNERRADIUS));
	LinearGradientBrush linLeft2GrBrush (PointF ((float)IGIMAGELIBRARY_BORDERWIDTH / 2.0f - 1.0f, 0), PointF (IGIMAGELIBRARY_BORDERWIDTH, 0),
							IGIMAGELIBRARY_COLOR_BORDERMIDDLE, IGIMAGELIBRARY_COLOR_BORDERIN);	
	graphics.FillRectangle (&linLeft2GrBrush, RectF ((float)IGIMAGELIBRARY_BORDERWIDTH / 2.0f, 0,
							(float)IGIMAGELIBRARY_BORDERWIDTH / 2.0f,
							IGIMAGELIBRARY_HEIGHT - IGIMAGELIBRARY_CORNERRADIUS));
	
	// Right part
	LinearGradientBrush linRightGrBrush (PointF(IGIMAGELIBRARY_WIDTH - IGIMAGELIBRARY_BORDERWIDTH - 1, 0),
										PointF(IGIMAGELIBRARY_WIDTH - (float)IGIMAGELIBRARY_BORDERWIDTH / 2.0f, 0),
										IGIMAGELIBRARY_COLOR_BORDERIN, IGIMAGELIBRARY_COLOR_BORDERMIDDLE);
	graphics.FillRectangle (&linRightGrBrush, RectF (IGIMAGELIBRARY_WIDTH - IGIMAGELIBRARY_BORDERWIDTH, 0,
							(float)IGIMAGELIBRARY_BORDERWIDTH / 2.0f,
							IGIMAGELIBRARY_HEIGHT - IGIMAGELIBRARY_CORNERRADIUS));
	LinearGradientBrush linRight2GrBrush (PointF(IGIMAGELIBRARY_WIDTH - (float)IGIMAGELIBRARY_BORDERWIDTH / 2.0f - 1.0f, 0),
										PointF(IGIMAGELIBRARY_WIDTH, 0),
										IGIMAGELIBRARY_COLOR_BORDERMIDDLE, IGIMAGELIBRARY_COLOR_BORDEROUT);
	graphics.FillRectangle (&linRight2GrBrush, RectF (IGIMAGELIBRARY_WIDTH - (float)IGIMAGELIBRARY_BORDERWIDTH / 2.0f, 0,
							(float)IGIMAGELIBRARY_BORDERWIDTH / 2.0f,
							IGIMAGELIBRARY_HEIGHT - IGIMAGELIBRARY_CORNERRADIUS));
	
	// Bottom part
	LinearGradientBrush linBottomGrBrush (PointF (0, IGIMAGELIBRARY_HEIGHT - IGIMAGELIBRARY_BORDERWIDTH - 1.0f),
											PointF (0, IGIMAGELIBRARY_HEIGHT - (float)IGIMAGELIBRARY_BORDERWIDTH / 2.0f),
							IGIMAGELIBRARY_COLOR_BORDERIN, IGIMAGELIBRARY_COLOR_BORDERMIDDLE);
	graphics.FillRectangle (&linBottomGrBrush, RectF (IGIMAGELIBRARY_CORNERRADIUS, 
												IGIMAGELIBRARY_HEIGHT - IGIMAGELIBRARY_BORDERWIDTH,
												IGIMAGELIBRARY_WIDTH - IGIMAGELIBRARY_CORNERDIAM,
												(float)IGIMAGELIBRARY_BORDERWIDTH / 2.0f));
	LinearGradientBrush linBottom2GrBrush (PointF(0,IGIMAGELIBRARY_HEIGHT - (float)IGIMAGELIBRARY_BORDERWIDTH / 2.0f - 1.0f),
											PointF(0,IGIMAGELIBRARY_HEIGHT),
							IGIMAGELIBRARY_COLOR_BORDERMIDDLE, IGIMAGELIBRARY_COLOR_BORDEROUT);
	graphics.FillRectangle (&linBottom2GrBrush, RectF (IGIMAGELIBRARY_CORNERRADIUS, 
												IGIMAGELIBRARY_HEIGHT - (float)IGIMAGELIBRARY_BORDERWIDTH / 2.0f,
												IGIMAGELIBRARY_WIDTH - IGIMAGELIBRARY_CORNERDIAM,
												(float)IGIMAGELIBRARY_BORDERWIDTH / 2.0f));

	// Bottom left part
	GraphicsPath pathBottomLeft;
	pathBottomLeft.AddEllipse (RectF (-5, IGIMAGELIBRARY_HEIGHT - IGIMAGELIBRARY_CORNERDIAM,
										IGIMAGELIBRARY_CORNERDIAM + 10.0f, IGIMAGELIBRARY_CORNERDIAM));
	PathGradientBrush pthGrBrushBottomLeft (&pathBottomLeft);
	Color colorsBottom[] = {IGIMAGELIBRARY_COLOR_BORDEROUT,
								IGIMAGELIBRARY_COLOR_BORDERMIDDLE,
								IGIMAGELIBRARY_COLOR_BORDERIN,
								IGIMAGELIBRARY_COLOR_FRAMEBORDER,
								IGIMAGELIBRARY_COLOR_FRAMEBORDER};
	REAL interpPositionsBottom[] = {   0.0f,
									   0.28f,
									   0.49f,
									   0.50f,
									   1.0f};
	pthGrBrushBottomLeft.SetInterpolationColors (colorsBottom, interpPositionsBottom, 5);
	graphics.FillRectangle (&pthGrBrushBottomLeft, RectF (0, IGIMAGELIBRARY_HEIGHT - IGIMAGELIBRARY_CORNERRADIUS,
															IGIMAGELIBRARY_CORNERRADIUS, IGIMAGELIBRARY_CORNERRADIUS));

	// Bottom right part
	REAL interpPositionsBottomRight[] = {   0.0f,
									   		0.30f,
									   		0.54f,
									   		0.55f,
									   		1.0f};
	GraphicsPath pathBottomRight;
	pathBottomRight.AddEllipse (RectF (IGIMAGELIBRARY_WIDTH - IGIMAGELIBRARY_CORNERDIAM, IGIMAGELIBRARY_HEIGHT - IGIMAGELIBRARY_CORNERDIAM - 5,
										IGIMAGELIBRARY_CORNERDIAM, IGIMAGELIBRARY_CORNERDIAM + 10));
	PathGradientBrush pthGrBrushBottomRight (&pathBottomRight);
	pthGrBrushBottomRight.SetInterpolationColors (colorsBottom, interpPositionsBottomRight, 5);
	graphics.FillRectangle (&pthGrBrushBottomRight, RectF (IGIMAGELIBRARY_WIDTH - IGIMAGELIBRARY_CORNERRADIUS, IGIMAGELIBRARY_HEIGHT - IGIMAGELIBRARY_CORNERRADIUS,
															IGIMAGELIBRARY_CORNERRADIUS, IGIMAGELIBRARY_CORNERRADIUS));
	return S_OK;
}