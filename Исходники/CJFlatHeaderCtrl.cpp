void CCJFlatHeaderCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC dc;

	dc.Attach( lpDrawItemStruct->hDC );
	
	// Get the column rect
	CRect rcLabel( lpDrawItemStruct->rcItem );
	
	// Save DC
	int nSavedDC = dc.SaveDC();
	
	// Set clipping region to limit drawing within column
	CRgn rgn;
	rgn.CreateRectRgnIndirect( &rcLabel );
	dc.SelectObject( &rgn );
	rgn.DeleteObject();
	
	// Draw the background
	dc.FillRect(rcLabel, &CBrush(::GetSysColor(COLOR_3DFACE)));
	dc.SetBkMode(TRANSPARENT);

	// Get the column text and format
	TCHAR buf[256];
	HD_ITEM hditem;
	
	hditem.mask = HDI_TEXT | HDI_FORMAT;
	hditem.pszText = buf;
	hditem.cchTextMax = 255;
	
	GetItem( lpDrawItemStruct->itemID, &hditem );
	
	// Determine format for drawing column label
	UINT uFormat = DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP 
		| DT_VCENTER | DT_END_ELLIPSIS ;
	
	if( hditem.fmt & HDF_CENTER)
		uFormat |= DT_CENTER;
	else if( hditem.fmt & HDF_RIGHT)
		uFormat |= DT_RIGHT;
	else
		uFormat |= DT_LEFT;
	
	// Adjust the rect if the mouse button is pressed on it
	if( lpDrawItemStruct->itemState == ODS_SELECTED )
	{
		rcLabel.left++;
		rcLabel.top += 2;
		rcLabel.right++;
	}
	
	// Adjust the rect further if Sort arrow is to be displayed
	if( lpDrawItemStruct->itemID == (UINT)m_nSortCol )
	{
		rcLabel.right -= 3 * m_nOffset;
	}
	
	rcLabel.left += m_nOffset;
	rcLabel.right -= m_nOffset;

	// Draw column label
	if( rcLabel.left < rcLabel.right )
	{
		if (m_bBoldFont) {
			dc.SelectObject(&m_HeaderFont);
		}
		dc.DrawText(buf,-1,rcLabel, uFormat);
	}

	// Draw the Sort arrow
	if( lpDrawItemStruct->itemID == (UINT)m_nSortCol )
	{
		CRect rcIcon( lpDrawItemStruct->rcItem );
		
		// Set up pens to use for drawing the triangle
		CPen penLite(PS_SOLID, 1, ::GetSysColor(COLOR_3DHILIGHT));
		CPen penShad(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW));
		CPen *pOldPen = dc.SelectObject( &penLite );
		
		if( m_bSortAsc )
		{
			// Draw triangle pointing upwards
			dc.MoveTo( rcIcon.right - 2*m_nOffset, m_nOffset-1);
			dc.LineTo( rcIcon.right - 3*m_nOffset/2, rcIcon.bottom - m_nOffset );
			dc.LineTo( rcIcon.right - 5*m_nOffset/2-2, rcIcon.bottom - m_nOffset );
			dc.MoveTo( rcIcon.right - 5*m_nOffset/2-1, rcIcon.bottom - m_nOffset-1 );
			
			dc.SelectObject( &penShad );
			dc.LineTo( rcIcon.right - 2*m_nOffset, m_nOffset-2);
		}
		else
		{
			// Draw triangle pointing downwords
			dc.MoveTo( rcIcon.right - 3*m_nOffset/2, m_nOffset-1);
			dc.LineTo( rcIcon.right - 2*m_nOffset-1, rcIcon.bottom - m_nOffset + 1 );
			dc.MoveTo( rcIcon.right - 2*m_nOffset-1, rcIcon.bottom - m_nOffset );
			
			dc.SelectObject( &penShad );
			dc.LineTo( rcIcon.right - 5*m_nOffset/2-1, m_nOffset -1 );
			dc.LineTo( rcIcon.right - 3*m_nOffset/2, m_nOffset -1);
		}
		
		// Restore the pen
		dc.SelectObject( pOldPen );
	}

	// Restore dc
	dc.RestoreDC( nSavedDC );
	
	// Detach the dc before returning
	dc.Detach();
}