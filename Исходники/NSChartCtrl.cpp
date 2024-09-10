void CNSChartCtrl::OnPaint() 
{
	CPaintDC dc(this); 

	int iValues	= m_ChartValues.GetSize();
	int iColors		= m_BrushArray.GetSize();

	CString str;
	CRect rect;
	GetClientRect(&rect);

	// Check values count
	if(iValues <= 0 )
	{
		CFont* oldFont = dc.SelectObject(&m_txtFont);

		str = "No data are available...";
		dc.FillSolidRect(rect,RGB(255,255,255));
		rect.top += 50;
		dc.DrawText(str,&rect,DT_CENTER|DT_VCENTER);
		dc.SelectObject(oldFont);
		return;
	}
	// Check color count
	if(iColors <= 1)
	{
		CFont* oldFont = dc.SelectObject(&m_txtFont);
		str = "Color count mus be > 1";
		dc.FillSolidRect(rect,RGB(255,255,255));
		rect.top += 50;
		dc.DrawText(str,&rect,DT_CENTER|DT_VCENTER);
		dc.SelectObject(oldFont);
		return;
	}

	//Creating double buffer painting

	CDC imageDC;
	imageDC.CreateCompatibleDC(&dc);

	CBitmap* pOldMemDCBitmap = NULL;

	if(m_bmpScreen.m_hObject == NULL) 
		m_bmpScreen.CreateCompatibleBitmap( &dc, rect.Width(), rect.Height() );
	pOldMemDCBitmap = (CBitmap*)imageDC.SelectObject(&m_bmpScreen);
	
	imageDC.FillSolidRect(rect,RGB(255,255,255));

//	rect.DeflateRect(0,5);

	// Drawing the chart
	if(m_dwStyle == NSCS_BAR ){
		DrawBarChart(&imageDC);
	}
	if(m_dwStyle == NSCS_PIE ){
		DrawPieChart(&imageDC);
	}
	if(m_dwStyle == NSCS_LINE ){
		DrawLineChart(&imageDC);
	}
	// Drawing the Title

	if(m_Caption.GetLength() == 0 )
		GetWindowText(str);
	else
	{
		str = m_Caption;
	}



	CFont* oldFont = imageDC.SelectObject(&m_titleFont);
	imageDC.DrawText(str,rect,DT_CENTER);
	imageDC.SelectObject(oldFont);

	// Drawing the new bitmap

	dc.BitBlt( rect.left , rect.top , rect.Width(), rect.Height(), 
					&imageDC, 0, 0, SRCCOPY );

	imageDC.SelectObject(pOldMemDCBitmap);

}