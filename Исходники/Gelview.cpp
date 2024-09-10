void CGelView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CGenedocDoc *pDoc = GetDocument();


//	if ( pDoc->IsEmbedded() && m_GelView ) {

	if ( m_init ) {

		CDC* pDC = GetDC();
		
		CRect ClientRect;
		
		GetClientRect(ClientRect);
		
		CPoint ptl = ClientRect.TopLeft();
		CPoint pbr = ClientRect.BottomRight();

		ptl.x = ptl.x + 220;
		ptl.y = ptl.y + 0;

		pbr.x = pbr.x - 0;
		pbr.y = pbr.y - 0;

		ClientRect.TopLeft() = ptl;
		ClientRect.BottomRight() = pbr;

		int DisplayHeight = ClientRect.Height();
		int DisplayWidth = ClientRect.Width();

		double ypi = pDC->GetDeviceCaps(LOGPIXELSY);
		double xpi = pDC->GetDeviceCaps(LOGPIXELSX);


//		WINDOWPLACEMENT wndpl;
//		m_cDraw.GetWindowPlacement( &wndpl );
//		wndpl.rcNormalPosition.bottom = DisplayHeight - 10;
//		wndpl.rcNormalPosition.right = DisplayWidth - 10;
//		m_cDraw.SetWindowPlacement( &wndpl );

		int x = (int)((double)(DisplayWidth - 10) / xpi * 100.0 );
		int y = (int)((double)(DisplayHeight - 10) / ypi * 100.0 );

		SetGelSize( x, y );
		
//		x = (int)((double)DisplayWidth / xpi * 100.0 );
//		y = (int)((double)DisplayHeight / ypi * 100.0 );

//		pDoc->m_ViewSize =  CSize( x, y );

		ReleaseDC(pDC);
	}

}