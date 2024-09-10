void CMyListCtrl::OnNcPaint() 
{
	// this is a sample drawing code :
// 	CRect rcWin;
// 	GetWindowRect(&rcWin);
// 
// 	CRect rcHeadCtrl;
// 	GetHeaderCtrl()->GetWindowRect(&rcHeadCtrl);
// 
// 	rcHeadCtrl.bottom += rcWin.Height();
// 
// 	CRect rcFrame(0, 0, rcWin.Width(), rcWin.Height());
// 	CPaintDC dc(this); 
// 	CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
// 	CPen *pOld = dc.SelectObject(&pen);
// 	dc.Rectangle(&rcFrame);
// 	dc.SelectObject(pOld);

	// draw the inside.
	Default();
	
	// draw over the border.
	CBrush brush(RGB(255, 0, 0));
	CRect rc;
	GetWindowRect(rc);
	
	CDC *pDC = GetParent()->GetDC();
	GetParent()->ScreenToClient( &rc );
	// do the drawing ...
	pDC->FrameRect( &rc , &brush );
 	rc.DeflateRect( 1, 1, 1, 1 );
 	pDC->FrameRect( &rc, &brush );

	GetParent()->ReleaseDC(pDC);
}