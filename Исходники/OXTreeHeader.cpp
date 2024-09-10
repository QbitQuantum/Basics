void COXTreeHeader::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	if (m_UxTheme.IsUxThemeLoaded())
	{
		HTHEME hTheme = m_UxTheme.GetWindowTheme(m_hWnd);
		if (hTheme != NULL)
		{

			// Draw the item background
			int iState = HIS_NORMAL;
			if (lpDrawItemStruct->itemState == ODS_SELECTED)
				iState = HIS_PRESSED;
			else
			{
				POINT ptCursor;
				::GetCursorPos(&ptCursor);
				ScreenToClient(&ptCursor);
				CRect rectItem(lpDrawItemStruct->rcItem);
				if (rectItem.PtInRect(ptCursor))
					iState = HIS_HOT;
			}
			m_UxTheme.DrawThemeBackground(hTheme,
				lpDrawItemStruct->hDC,
				HP_HEADERITEM,
				iState,
				&lpDrawItemStruct->rcItem,
				NULL);

			BOOL bDrawArrow;
			if (m_nSortOrder!=0 && lpDrawItemStruct->itemID == (UINT)m_nSortCol)
				bDrawArrow = TRUE;
			else
				bDrawArrow = FALSE;


			// Get the column text and format	
			TCHAR buf[256];	
			HD_ITEM hditem;	
			hditem.mask = HDI_TEXT | HDI_FORMAT;	
			hditem.pszText = buf;
			hditem.cchTextMax = 255;	
			GetItem( lpDrawItemStruct->itemID, &hditem );

			RECT rectText = lpDrawItemStruct->rcItem;
			rectText.left += 9;
			rectText.right -= 9;

			// Determine format for drawing column label
			UINT uFormat = DT_SINGLELINE | DT_NOPREFIX | 
				DT_VCENTER | DT_END_ELLIPSIS ;
			UINT uArrowFormat = DT_SINGLELINE | DT_VCENTER;
			if( hditem.fmt & HDF_CENTER)
			{
				uFormat |= DT_CENTER;
				uArrowFormat |= DT_RIGHT;
				if (bDrawArrow)
					rectText.right -= 12;
			}
			else if( hditem.fmt & HDF_RIGHT)
			{
				uFormat |= DT_RIGHT;
				uArrowFormat |= DT_LEFT;
				if (bDrawArrow)
					rectText.left += 12;
			}
			else
			{
				uFormat |= DT_LEFT;
				uArrowFormat |= DT_RIGHT;
				if (bDrawArrow)
					rectText.right -= 12;
			}

			m_UxTheme.DrawThemeText(hTheme,
				lpDrawItemStruct->hDC,
				HP_HEADERITEM,
				HIS_NORMAL,
				buf,
				-1,
				uFormat,
				0,
				&rectText);

			// Draw the Sort arrow	
			if (bDrawArrow)	
			{
				CDC dc;
				dc.Attach(lpDrawItemStruct->hDC);
				int nSavedDC = dc.SaveDC();
				CFont fontMarlett;
				fontMarlett.CreatePointFont(120, _T("Marlett"));
				dc.SelectObject(&fontMarlett);
				dc.SetBkMode(TRANSPARENT);
				dc.SetTextColor(RGB(128, 128, 128));

				CRect rectArrow = lpDrawItemStruct->rcItem;
				rectArrow.DeflateRect(5, 0, 5, 0);

				if (m_nSortOrder == 1)
					dc.DrawText(_T("5"), -1, &rectArrow, uArrowFormat);
				else
					dc.DrawText(_T("6"), -1, &rectArrow, uArrowFormat);

				// Restore dc	
				dc.RestoreDC(nSavedDC);
				// Detach the dc before returning	
				dc.Detach();
			}
			return;
		}
	}

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
	CBrush brush(::GetSysColor(COLOR_3DFACE));
	dc.FillRect(rcLabel,&brush);	
	// Labels are offset by a certain amount  
	// This offset is related to the width of a space character
	int offset = dc.GetTextExtent(_T(" "), 1 ).cx*2;
	// Get the column text and format	
	TCHAR buf[256];	
	HD_ITEM hditem;	
	hditem.mask = HDI_TEXT | HDI_FORMAT;	
	hditem.pszText = buf;
	hditem.cchTextMax = 255;	
	GetItem( lpDrawItemStruct->itemID, &hditem );
	// Determine format for drawing column label
	UINT uFormat = DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | 
		DT_VCENTER | DT_END_ELLIPSIS ;	
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
		rcLabel.right -= 3 * offset;	
	}
	rcLabel.left += offset;
	rcLabel.right -= offset;	
	// Draw column label
	if( rcLabel.left < rcLabel.right )
		dc.DrawText(buf,-1,rcLabel, uFormat);

	// Draw the Sort arrow	
	if( m_nSortOrder!=0 && lpDrawItemStruct->itemID == (UINT)m_nSortCol )	
	{
		CRect rcIcon( lpDrawItemStruct->rcItem );
		// Set up pens to use for drawing the triangle
		CPen penLight(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));
		CPen penShadow(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));
		CPen *pOldPen = dc.SelectObject( &penLight );		
		if( m_nSortOrder==1 )		
		{
			// Draw triangle pointing upwards
			dc.MoveTo( rcIcon.right - 2*offset, offset-1);
			dc.LineTo( rcIcon.right - 3*offset/2, rcIcon.bottom - offset );
			dc.LineTo( rcIcon.right - 5*offset/2-2, rcIcon.bottom - offset );
			dc.MoveTo( rcIcon.right - 5*offset/2-1, rcIcon.bottom - offset-1 );
			dc.SelectObject( &penShadow );
			dc.LineTo( rcIcon.right - 2*offset, offset-2);		
		}
		else		
		{
			// Draw triangle pointing downwords
			dc.MoveTo( rcIcon.right - 3*offset/2, offset-1);
			dc.LineTo( rcIcon.right - 2*offset-1, rcIcon.bottom - offset + 1 );
			dc.MoveTo( rcIcon.right - 2*offset-1, rcIcon.bottom - offset );
			dc.SelectObject( &penShadow );
			dc.LineTo( rcIcon.right - 5*offset/2-1, offset -1 );
			dc.LineTo( rcIcon.right - 3*offset/2, offset -1);		
		}
		// Restore the pen
		dc.SelectObject( pOldPen );	
	}

	// Restore dc	
	dc.RestoreDC( nSavedDC );
	// Detach the dc before returning	
	dc.Detach();
}