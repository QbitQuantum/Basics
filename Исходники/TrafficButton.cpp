void CTrafficButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  添加您的代码以绘制指定项
	ASSERT( lpDrawItemStruct != NULL );

	CDC * pDC   = CDC::FromHandle( lpDrawItemStruct -> hDC );
	int erg = pDC->SelectClipRgn(&ShapeDCRegion);

	CRect rect = lpDrawItemStruct -> rcItem;
	UINT state = lpDrawItemStruct -> itemState;
	UINT nStyle = GetStyle( );

	int nSavedDC = pDC -> SaveDC( );

	// Create the brush for the color bar
	if(brushInitalized == FALSE)
	{
		CBitmap bmp;
		CMyDC *memDC = new CMyDC(pDC);

		RECT clipRect;
		memDC->GetClipBox(&clipRect);

		if(clipRect.right - clipRect.left > 1)
		{
			bmp.CreateCompatibleBitmap(memDC,plotgranularity, TGSize.cy);
			CBitmap *pOld = memDC->SelectObject(&bmp);

			CSize bmps = bmp.GetBitmapDimension();		

			// Need for scaling the color to the size of button
			double factor = 255.0 / (float)TGSize.cy;
			BYTE r,g,b;
			for(int x = 0; x<TGSize.cy; x++)
			{
				g = (BYTE)(255-factor*x);
				r = (BYTE)(factor*x);
				b = (BYTE)64;
				memDC->SetPixelV(0,x,RGB(r,g,b));
				memDC->SetPixelV(1,x,RGB(r,g,b));
			}
			memDC->SelectObject(pOld);

			colorbrush.CreatePatternBrush(&bmp);	
			brushInitalized = TRUE;
		}
		delete memDC;
	}
	if(initalized == TRUE)
	{
		COLORREF backcolor = GetSysColor(COLOR_BTNFACE);

		CBrush brush;
		CMyDC *memDC = new CMyDC(pDC);

		RECT clipRect;
		memDC->GetClipBox(&clipRect);
		memDC->FillSolidRect(&clipRect,backcolor);

		CFont *oldFont;
		int xp, yp, xx, yy;
		orgBrushOrigin = memDC->GetBrushOrg();

		oldFont = memDC->SelectObject(&smallFont);

		double scale = TGSize.cy / (maxSpeed/1024.0);

		yp = TrafficDrawRectangle.bottom;
		xp = TrafficDrawRectangle.left;

		RECT fillrect;

		// Fill the background
		back = memDC->GetBkColor();
		brush.CreateSolidBrush(darkblue);//back);
		memDC->FillRect(&TrafficDrawRectangle, &brush);


		//画网格
		int xgridlines, ygridlines;

		xgridlines = TGSize.cx / gridxresolution;
		ygridlines = TGSize.cy / gridyresolution;
		CPen* oldPen = memDC->SelectObject(&GridPen);

		// Create the vertical lines
		for (int x=0; x<= xgridlines; x++)
		{
			memDC->MoveTo(x*gridxresolution + gridxstartpos, 0			);
			memDC->LineTo(x*gridxresolution + gridxstartpos, TGSize.cy	);
		}
		// And the horizontal lines
		for (int y=0; y<= ygridlines; y++)
		{
			memDC->MoveTo(0			, gridystartpos + TGSize.cy - y*gridyresolution - 2);
			memDC->LineTo(TGSize.cx	, gridystartpos + TGSize.cy - y*gridyresolution - 2);
		}

		gridxstartpos += gridscrollxspeed;
		gridystartpos += gridscrollyspeed;
		if(gridxstartpos < 0				) gridxstartpos += gridxresolution;
		if(gridxstartpos > gridxresolution	) gridxstartpos -= gridxresolution;
		if(gridystartpos < 0				) gridystartpos += gridyresolution;
		if(gridystartpos > gridyresolution	) gridystartpos -= gridyresolution;


		memDC->SelectObject(oldPen );

		for(DWORD cnt=0; cnt<TrafficEntries; cnt++)
		{
			xx = xp + cnt*plotgranularity;
			yy = yp - (int)(TrafficStats[cnt] * scale);

			// Just paint if we are connected...
			fillrect.bottom = yp;
			fillrect.top	= yy;
			fillrect.left	= xx;
			fillrect.right	= xx+plotgranularity;
			memDC->SetBrushOrg(xx,yp);
			//TRACE("TrafficStats[%d]: %f\n", cnt,TrafficStats[cnt]);
			if(TrafficStats[cnt] > 0.0) 
			{
				//画柱状图
				memDC->FillRect(&fillrect, &colorbrush);
				memDC->SetPixelV(xx, yy, cyan);
			}
		}

		COLORREF textcolor = memDC->GetTextColor();
		int bkmode = memDC->GetBkMode();
		memDC->SetBkMode(TRANSPARENT);

		//输出统计信息
		memDC->SetTextColor(cyan);
		CString traffic;
		traffic.Format(L"CUR: %.2f  HHG: %.2f",curSpeed/1024.0,maxSpeed/1024.0);
		memDC->TextOut(5,5,traffic); 

		memDC->SetTextColor(textcolor);
		memDC->SetBkMode(bkmode);
		memDC->SelectObject(oldFont);
		memDC->SetBrushOrg(orgBrushOrigin.x, orgBrushOrigin.y);

		delete memDC;

	}
	pDC -> RestoreDC( nSavedDC );
}