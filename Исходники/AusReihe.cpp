void AusReihe::OnPaint()
{
	UpdateData(TRUE);
	CPaintDC dc(this); // device context for painting
	dc.FillRect(rahmen, &stdbrush.white);
	CPen *oldPen = dc.SelectObject(&stdpen.gray1);


	if (m_xraster)
	{
		for (int index = 0; index < DemoData.get_anz_s(); index++)
		{
			int x = paddingLeft + rahmen.left + (index*(rahmen.Width() - paddingWidth)) / (DemoData.get_anz_s() - 1);
			dc.MoveTo(x, rahmen.top + paddingTop);
			dc.LineTo(x, rahmen.bottom - paddingBottom);
		}
	}
	if (m_yraster)
	{
		for (int index = 0; index < anzHorizontalLines; index++)
		{
			int y = paddingTop + rahmen.top + (index*(rahmen.Height() - paddingHeight)) / (anzHorizontalLines-1);
			/*if (y > rahmen.bottom - paddingBottom)
				y = rahmen.bottom - paddingBottom;*/
			dc.MoveTo(rahmen.left + paddingLeft, y);
			dc.LineTo(rahmen.right - paddingRight, y);
		}
	}

	CSize dataRangeHeight, dataRangeWidth, windowRangeHeight, windowRangeWidth;
	dataRangeHeight = CSize(DemoData.minimum(m_selection), DemoData.maximum(m_selection));
	dataRangeWidth = CSize(0, DemoData.get_anz_s()-1);
	//windowRangeHeight = CSize(rahmen.top + 1*paddingTop, rahmen.bottom - 1*paddingBottom);
	windowRangeHeight = CSize(paddingTop, rahmen.Height()-paddingHeight);
	windowRangeWidth = CSize(rahmen.left + paddingLeft, rahmen.right - 1*paddingRight);
	//draw null line
	dc.SelectObject(&stdpen.black2);
	if ((DemoData.minimum(m_selection) < 0) && (DemoData.maximum(m_selection) > 0))
	{
		int nullLine = rahmen.bottom-scalePoint(0, &dataRangeHeight, &windowRangeHeight);
		dc.MoveTo(rahmen.left + paddingLeft, nullLine);
		dc.LineTo(rahmen.right - paddingRight, nullLine);
	}

	if (m_darstellung == 0)
	{
		CPoint oldP, newP;
		oldP = CPoint(
			scalePoint(0, &dataRangeWidth, &windowRangeWidth),
			rahmen.bottom - scalePoint(DemoData.get_wert(m_selection, 0), &dataRangeHeight, &windowRangeHeight)
			);
		dc.MoveTo(oldP);
		for (int index = 0; index < DemoData.get_anz_s(); index++)
		{
			dc.SelectObject(&stdpen.black5);
			newP = CPoint(
				scalePoint(index, &dataRangeWidth, &windowRangeWidth),
				rahmen.bottom -scalePoint(DemoData.get_wert(m_selection, index), &dataRangeHeight, &windowRangeHeight)
				);
			dc.LineTo(newP);
			dc.SelectObject(&stdpen.gray3);
			dc.MoveTo(oldP);
			dc.LineTo(newP);
			oldP = newP;
		}
		//draw the points

		dc.SelectObject(&stdbrush.gray);
		dc.SelectObject(&stdpen.black1);
		for (int index = 0; index < DemoData.get_anz_s(); index++)
		{
			CPoint loc = CPoint(
				scalePoint(index, &dataRangeWidth, &windowRangeWidth),
				rahmen.bottom - scalePoint(DemoData.get_wert(m_selection, index), &dataRangeHeight, &windowRangeHeight)
				);
			dc.Ellipse(loc.x - 5, loc.y - 5, loc.x + 5, loc.y + 5);
		}
	}
	else
	{
		dc.SelectObject(&stdbrush.gray);
		dc.SelectObject(&stdpen.black1);
		for (int index = 0; index < DemoData.get_anz_s(); index++)
		{
			int loc = scalePoint(index, &dataRangeWidth, &windowRangeWidth);
			//dc.Rectangle(loc - 5, rahmen.bottom - scalePoint(0, &dataRangeHeight, &windowRangeHeight), loc + 5, rahmen.bottom - paddingBottom + nullLine - scalePoint(DemoData.get_wert(m_selection, index), &CSize(DemoData.minimum(m_selection), DemoData.maximum(m_selection)), &CSize(0, rahmen.Height() - paddingHeight)));
			dc.Rectangle(loc, rahmen.bottom - scalePoint(0, &dataRangeHeight, &windowRangeHeight), loc + 10, rahmen.bottom - scalePoint(DemoData.get_wert(m_selection, index), &dataRangeHeight, &windowRangeHeight));
		}
	}

	//Draw all Selected 
	dc.SelectObject(&stdfont.norm);
	dc.SelectObject(&stdpen.black1);
	dc.SelectObject(&stdbrush.yellow);
	dc.SetBkMode(TRANSPARENT);
	for (int index = 0; index < DemoData.get_anz_s(); index++)
	{
		if (infoflag[index])
		{
			CPoint loc = CPoint(
				scalePoint(index, &dataRangeWidth, &windowRangeWidth),
				rahmen.bottom - scalePoint(DemoData.get_wert(m_selection, index), &dataRangeHeight, &windowRangeHeight)
				);
			CRect r = CRect(loc.x, loc.y, 0, 0);
			CString str;
			str.Format("%d", DemoData.get_wert(m_selection, index));
			dc.DrawText(str, &r, DT_CALCRECT);
			r.OffsetRect(0, -r.Height());
			r.right += 6;
			dc.Rectangle(&r);
			dc.DrawText(str, &r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}
	}
	dc.SelectObject(oldPen);
}