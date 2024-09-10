void CIMTree::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rcClip, rcClient;
	dc.GetClipBox( &rcClip );
	GetClientRect(&rcClient);

	// Create a compatible memory DC 
	CDC memDC;
	memDC.CreateCompatibleDC( &dc );
	
	// Select a compatible bitmap into the memory DC
	CBitmap bitmap, bmpImage;
	bitmap.CreateCompatibleBitmap( &dc, rcClient.Width(), rcClient.Height() );
	CBitmap *OldBitmap = memDC.SelectObject( &bitmap );

	// First let the control do its default drawing.
	CTreeCtrl::DefWindowProc( WM_PAINT, (WPARAM)memDC.m_hDC, 0 );


/*
	// create the font
	CFont *pFontDC;
	CFont fontDC, boldFontDC;
	LOGFONT logfont;

	CFont *pFont = GetFont();
	pFont->GetLogFont( &logfont );

	fontDC.CreateFontIndirect( &logfont );		//普通字体
	pFontDC = memDC.SelectObject( &fontDC );

	logfont.lfWeight = 700;
	boldFontDC.CreateFontIndirect( &logfont );	//粗体字

	// and now let's get to the painting itself
	HTREEITEM hItem = GetFirstVisibleItem();

	int n = GetVisibleCount();

	hItem = GetFirstVisibleItem();
	n = GetVisibleCount();

	while(hItem!=NULL && n>=0)
	{
		CRect rect;
		CRect m_labelRect;

		UINT selflag = TVIS_SELECTED ; // |TVIS_DROPHILITED;
	
		CString ItemText = GetItemText(hItem);

		GetItemRect( hItem, &m_labelRect, TRUE );	//文字
		GetItemRect( hItem, &rect, FALSE );

		if ( !(GetItemState( hItem, selflag ) & selflag )) //选中状态
		{
			memDC.SetBkMode(TRANSPARENT);

			memDC.SetTextColor(::GetSysColor (COLOR_WINDOWTEXT ));

			DrawItemText(&memDC,ItemText,m_labelRect,LVCFMT_LEFT);
		}
		else
		{
			COLORREF m_highlightColor = ::GetSysColor (COLOR_HIGHLIGHT);

			CBrush brush(m_highlightColor);

			memDC.FillRect (m_labelRect, &brush);
			// draw a dotted focus rectangle
			memDC.DrawFocusRect (m_labelRect);

			memDC.SetBkColor(m_highlightColor);

			memDC.SetTextColor(::GetSysColor (COLOR_HIGHLIGHTTEXT));

			memDC.SelectObject( &boldFontDC );

			DrawItemText(&memDC,ItemText,m_labelRect,LVCFMT_LEFT);

			memDC.SelectObject( &pFontDC );
		}

		hItem = GetNextVisibleItem( hItem );
		n--;
	}

	memDC.SelectObject( pFontDC );

*/

	// Draw bitmap in the background if one has been set
	if( m_bitmap.m_hObject != NULL )
	{
		// Now create a mask
		CDC maskDC;
		maskDC.CreateCompatibleDC(&dc);
		CBitmap maskBitmap;

		// Create monochrome bitmap for the mask
		maskBitmap.CreateBitmap( rcClient.Width(), rcClient.Height(), 
					1, 1, NULL );

		CBitmap *OldMask = maskDC.SelectObject( &maskBitmap );
		memDC.SetBkColor( ::GetSysColor( COLOR_WINDOW ) );

		// Create the mask from the memory DC
		maskDC.BitBlt( 0, 0, 
			rcClient.Width(), rcClient.Height(), 
			&memDC, 
			rcClient.left, rcClient.top, 
			SRCCOPY );

		
		CDC tempDC;
		tempDC.CreateCompatibleDC(&dc);
		CBitmap *Oldtemp = tempDC.SelectObject( &m_bitmap );

		CDC imageDC;
		CBitmap bmpImage;
		imageDC.CreateCompatibleDC( &dc );

		bmpImage.CreateCompatibleBitmap( &dc, rcClient.Width(), 
						rcClient.Height() );
		CBitmap *OldImage = imageDC.SelectObject( &bmpImage );

		if( dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE && m_pal.m_hObject != NULL )
		{
			dc.SelectPalette( &m_pal, FALSE );
			dc.RealizePalette();

			imageDC.SelectPalette( &m_pal, FALSE );
		}

		// Get x and y offset
		CRect rcRoot;
		GetItemRect( GetRootItem(), rcRoot, FALSE );
		rcRoot.left = -GetScrollPos( SB_HORZ );

		imageDC.FillSolidRect(CRect(0,0,rcClient.right,rcClient.bottom),BgColor);

		if( m_bBgStretch )
		{
			imageDC.SetStretchBltMode(COLORONCOLOR);
			imageDC.StretchBlt(
				0,0,rcClient.right,rcClient.bottom,
				&tempDC,
				0,0,m_cxBitmap,m_cyBitmap,
				SRCCOPY
			);
		}
		else
		{	
			imageDC.BitBlt( 
				rcClient.right-m_cxBitmap,rcClient.bottom-m_cyBitmap,
				m_cxBitmap,m_cyBitmap,
				&tempDC,
				0, 0, 
				SRCCOPY );
			/*
			// Draw bitmap in tiled manner to imageDC
			for( int i = rcRoot.left; i < rcClient.right; i += m_cxBitmap )
			for( int j = rcRoot.top; j < rcClient.bottom; j += m_cyBitmap )
			{
				imageDC.BitBlt( i, j, m_cxBitmap, m_cyBitmap, 
					&tempDC,0, 0, SRCCOPY );
			}
			*/
		}
		
		// Set the background in memDC to black. Using SRCPAINT with black and any other
		// color results in the other color, thus making black the transparent color
		memDC.SetBkColor(RGB(0,0,0));        
		memDC.SetTextColor(RGB(255,255,255));

		memDC.BitBlt(	rcClip.left, rcClip.top, 
				rcClip.Width(), rcClip.Height(), 
				&maskDC, 
				rcClip.left, rcClip.top, 
				SRCAND);

		// Set the foreground to black. See comment above.
		imageDC.SetBkColor(RGB(255,255,255));
		imageDC.SetTextColor(RGB(0,0,0));

		imageDC.BitBlt(	rcClip.left, rcClip.top, 
				rcClip.Width(), rcClip.Height(), 
				&maskDC, 
				rcClip.left, rcClip.top, 
				SRCAND);

		// Combine the foreground with the background
		imageDC.BitBlt(	rcClip.left, rcClip.top, 
				rcClip.Width(), rcClip.Height(), 
				&memDC, 
				rcClip.left, rcClip.top,
				SRCPAINT);
		
		// Draw the final image to the screen		
		dc.BitBlt(	rcClip.left, rcClip.top, 
				rcClip.Width(), rcClip.Height(), 
				&imageDC, 
				rcClip.left, rcClip.top, SRCCOPY );

		//释放对象
		maskDC.SelectObject(OldMask);
		imageDC.SelectObject(OldImage);
		tempDC.SelectObject(Oldtemp);

		maskBitmap.DeleteObject();
		bmpImage.DeleteObject();

		maskDC.DeleteDC();
		imageDC.DeleteDC();
		tempDC.DeleteDC();
	}
	else
	{
		dc.BitBlt(	rcClip.left, rcClip.top, 
				rcClip.Width(), 
				rcClip.Height(), 
				&memDC, 
				rcClip.left, rcClip.top, SRCCOPY );
	}

	memDC.SelectObject(OldBitmap);
	bitmap.DeleteObject();
	memDC.DeleteDC();
}