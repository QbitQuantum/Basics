//Display tooltip
void CToolTip2::DisplayToolTip(const CPoint& rCurrentPoint)
{
	CDC* pDC = GetDC();

	CBrush		*pOldBrush;

	CFont *pOldFont;
	pOldFont = pDC->SelectObject(&m_font);
	
	//CSize size = pDC->GetTextExtent(m_szText);
	//pDC->LPtoDP(&size);
	int x = 0;
	int nLargest = 0;
	CString sLine;
	CSize size;
	while(GetLine(m_szText, &sLine, x))
	{
		size = pDC->GetTextExtent(sLine);
		pDC->LPtoDP(&size);
		if(size.cx > nLargest)
			nLargest = size.cx;
		x++;
	}
	int nHeight = size.cy;
	size.cx = nLargest;
	size.cy *= x;

	
	
	//Form tooltip rectangle
	CRect rectToolTip(rCurrentPoint.x, rCurrentPoint.y, rCurrentPoint.x+size.cx+7, rCurrentPoint.y+size.cy+2);

	//Draw Tooltip Rect and Text
	//
	pDC->SetBkMode(TRANSPARENT);
	CBrush brushToolTip(GetSysColor(COLOR_INFOBK));
	pOldBrush = pDC->SelectObject(&brushToolTip);

	//Create and select thick black pen
	CPen penBlack(PS_SOLID, 0, COLORREF(RGB(0, 0, 0)));
	CPen* pOldPen = pDC->SelectObject(&penBlack);

	//Draw rectangle filled with COLOR_INFOBK
	pDC->Rectangle(0,0,rectToolTip.Width(),rectToolTip.Height());

	//Draw tooltip text
   	pDC->SetTextColor( GetSysColor(COLOR_INFOTEXT) );//Tool Tip color set in control panel settings
	pDC->SetTextAlign(TA_LEFT);
	//pDC->TextOut(3,1, m_szText);
	x = 0;
	while(GetLine(m_szText, &sLine, x))
	{
		pDC->TextOut(3,1 + (x * nHeight), sLine);
		x++;
	}


	CRect rectWnd = rectToolTip;
	m_pParentWnd->ClientToScreen(rectWnd); //Convert from client to screen coordinates
	CPoint ptToolTipLeft = rectWnd.TopLeft();

	//Now display tooltip
	SetWindowPos(&wndTop,ptToolTipLeft.x+1, ptToolTipLeft.y+1, rectWnd.Width(), 
rectWnd.Height(),SWP_SHOWWINDOW|SWP_NOOWNERZORDER|SWP_NOACTIVATE);

	//put back old objects
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldFont);

	ReleaseDC(pDC);
}