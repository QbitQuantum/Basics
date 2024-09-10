// Calculate the dimensions and draw the balloon header
CSize CBalloonHelp::DrawHeader(CDC* pDC, bool bDraw)
{
	CSize sizeHdr(0,0);
	CRect rectClient;
	GetClientRect(&rectClient);   // use this for positioning when drawing
	// else if content is wider than title, centering wouldn't work
	
	// calc & draw icon
	if ( NULL != m_ilIcon.m_hImageList )
	{
		int x = 0;
		int y = 0;
		ImageList_GetIconSize(m_ilIcon, &x, &y);
		sizeHdr.cx += x;
		sizeHdr.cy = max(sizeHdr.cy, y);
		m_ilIcon.SetBkColor(m_crBackground);
		if (bDraw)
			m_ilIcon.Draw(pDC, 0, CPoint(0,0), ILD_NORMAL);//ILD_TRANSPARENT);
		rectClient.left += x;
	}
	
	// calc & draw close button
	if ( m_unOptions & unSHOW_CLOSE_BUTTON )
	{
		// if something is already in the header (icon) leave space
		if ( sizeHdr.cx > 0 )
			sizeHdr.cx += nTIP_MARGIN;
		sizeHdr.cx += 16;
		sizeHdr.cy = max(sizeHdr.cy, 16);
		if (bDraw)
			pDC->DrawFrameControl(CRect(rectClient.right-16,0,rectClient.right,16), DFC_CAPTION, DFCS_CAPTIONCLOSE|DFCS_FLAT);
		rectClient.right -= 16;
	}
	
	// calc title size
	CString strTitle;
	GetWindowText(strTitle);
	if ( !strTitle.IsEmpty() )
	{
		CFont* pOldFont = pDC->SelectObject(m_pTitleFont);
		
		// if something is already in the header (icon or close button) leave space
		if ( sizeHdr.cx > 0 ) 
			sizeHdr.cx += nTIP_MARGIN;
		CRect rectTitle(0,0,0,0);
		pDC->DrawText(strTitle, &rectTitle, DT_CALCRECT | DT_NOPREFIX | DT_EXPANDTABS | DT_SINGLELINE);
		sizeHdr.cx += rectTitle.Width();
		sizeHdr.cy = max(sizeHdr.cy, rectTitle.Height());
		
		// draw title
		if ( bDraw )
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(m_crForeground);
			pDC->DrawText(strTitle, &rectClient, DT_CENTER | DT_NOPREFIX  | DT_EXPANDTABS | DT_SINGLELINE);
		}
		
		// cleanup
		pDC->SelectObject(pOldFont);
	}
	
	return sizeHdr;
}