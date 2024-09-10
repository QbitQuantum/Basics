void COXTabViewContainer::DrawButton(CDC* pDC, CRect rect, 
									 HITTEST nButtonType) const
{
	ASSERT_VALID(pDC);

	pDC->FillSolidRect(rect,::GetSysColor(COLOR_BTNFACE));

	COLORREF clrTopLeft;
	COLORREF clrBottomRight;
	if(m_nPressedScrlBtn==nButtonType)
	{
		CPoint point;
		::GetCursorPos(&point);
		ScreenToClient(&point);
		if(rect.PtInRect(point))
		{
			clrBottomRight=::GetSysColor(COLOR_BTNFACE);
			clrTopLeft=::GetSysColor(COLOR_BTNFACE);
			rect.OffsetRect(1,1);
		}
		else
		{
			clrTopLeft=::GetSysColor(COLOR_BTNHILIGHT);
			clrBottomRight=::GetSysColor(COLOR_BTNSHADOW);
		}
	}
	else
	{
		clrTopLeft=::GetSysColor(COLOR_BTNHILIGHT);
		clrBottomRight=::GetSysColor(COLOR_BTNSHADOW);
	}

	pDC->Draw3dRect(rect,clrTopLeft,clrBottomRight);


	// draw arrows
	//
	rect.DeflateRect(2,2);
	CRect rectCopy=rect;

	POINT arrPoints[3];
	CRgn rgn;
	CBrush brush;
	brush.CreateSolidBrush(::GetSysColor(COLOR_WINDOWTEXT));

	switch(nButtonType)
	{
	// start
	case SCRLSTARTBTN:
		rectCopy.DeflateRect(rectCopy.Width()/4,rectCopy.Height()/6);
		rectCopy.left+=rectCopy.Width()/4-2;
		if(rectCopy.Height()%2==0)
			rectCopy.bottom+=1;
		rectCopy.right=rectCopy.left+2;
		pDC->FillSolidRect(rectCopy,::GetSysColor(COLOR_WINDOWTEXT));
	// backward
	case SCRLBACKWARDBTN:
		rectCopy=rect;
		rectCopy.DeflateRect(rectCopy.Width()/4,rectCopy.Height()/6);
		if(nButtonType==SCRLSTARTBTN)
			rectCopy.left+=rectCopy.Width()/4;
		else
			rectCopy.right-=rectCopy.Width()/4;
		if(rectCopy.Height()%2==0)
			rectCopy.bottom++;
		arrPoints[0].x=rectCopy.right;
		arrPoints[0].y=rectCopy.top-1;
		arrPoints[1].x=rectCopy.right;
		arrPoints[1].y=rectCopy.bottom;
		arrPoints[2].x=rectCopy.left;
		arrPoints[2].y=rectCopy.top+rectCopy.Height()/2;
		rgn.CreatePolygonRgn(arrPoints,3,WINDING);
		pDC->FillRgn(&rgn,&brush);
		break;
	// end
	case SCRLENDBTN:
		rectCopy.DeflateRect(rectCopy.Width()/4,rectCopy.Height()/6);
		rectCopy.right-=rectCopy.Width()/4-2;
		if(rectCopy.Height()%2==0)
			rectCopy.bottom+=1;
		rectCopy.left=rectCopy.right-2;
		pDC->FillSolidRect(rectCopy,::GetSysColor(COLOR_WINDOWTEXT));
	// forward
	case SCRLFORWARDBTN:
		rectCopy=rect;
		rectCopy.DeflateRect(rectCopy.Width()/4,rectCopy.Height()/6);
		if(nButtonType==SCRLENDBTN)
			rectCopy.right-=rectCopy.Width()/4;
		else
			rectCopy.left+=rectCopy.Width()/4;
		if(rectCopy.Height()%2==0)
			rectCopy.bottom++;
		arrPoints[0].x=rectCopy.right;
		arrPoints[0].y=rectCopy.top+rectCopy.Height()/2;
		arrPoints[1].x=rectCopy.left;
		arrPoints[1].y=rectCopy.top-1;
		arrPoints[2].x=rectCopy.left;
		arrPoints[2].y=rectCopy.bottom;
		rgn.CreatePolygonRgn(arrPoints,3,WINDING);
		pDC->FillRgn(&rgn,&brush);
		break;
	default:
		ASSERT(FALSE);
	}
}