void CUploadsCtrl::PaintQueue(CDC& dc, const CRect& rcRow, CUploadQueue* pQueue, BOOL bFocus)
{
	ASSUME_LOCK( UploadQueues.m_pSection );

	COLORREF crNatural	= CoolInterface.m_crWindow;
	COLORREF crBack		= pQueue->m_bSelected ? CoolInterface.m_crHighlight : crNatural;
	COLORREF crLeftAligned = crBack ;

	dc.SetBkColor( crBack );
	dc.SetBkMode( OPAQUE );
	
	if ( pQueue->m_bSelected )
		dc.SetTextColor( CoolInterface.m_crHiText );
	else
		dc.SetTextColor( CoolInterface.m_crText );
	
	int nTextLeft = rcRow.right, nTextRight = rcRow.left;
	HDITEM pColumn = {};
	
	pColumn.mask = HDI_FORMAT | HDI_LPARAM;
	
	dc.SelectObject( &CoolInterface.m_fntBold );
	
	for ( int nColumn = 0 ; m_wndHeader.GetItem( nColumn, &pColumn ) ; nColumn++ )
	{
		CString strText;
		CRect rcCell;
		
		m_wndHeader.GetItemRect( nColumn, &rcCell );
		rcCell.left		+= rcRow.left;
		rcCell.right	+= rcRow.left;
		rcCell.top		= rcRow.top;
		rcCell.bottom	= rcRow.bottom;

		crLeftAligned = ( rcRow.left == rcCell.left ? crNatural : crBack ) ;

		POINT ptHover;
		RECT  rcTick = { rcCell.left+2, rcCell.top+2, rcCell.left+14, rcCell.bottom-2 };
		GetCursorPos(&ptHover);
		ScreenToClient(&ptHover);

		switch ( pColumn.lParam )
		{
		case UPLOAD_COLUMN_TITLE:
			dc.FillSolidRect( rcCell.left, rcCell.bottom - 1, 32, 1, crLeftAligned );

			if ( pQueue->m_bExpanded )
			{
			CoolInterface.Draw( &dc, PtInRect(&rcTick,ptHover) ? IDI_MINUS_HOVER : IDI_MINUS,
					16, rcCell.left, rcCell.top, crLeftAligned );
			}
			else
			{
				CoolInterface.Draw( &dc, PtInRect(&rcTick,ptHover) ? IDI_PLUS_HOVER : IDI_PLUS,
					16, rcCell.left, rcCell.top, crLeftAligned );
			}

			rcCell.left += 16;
			if ( pQueue == UploadQueues.m_pTorrentQueue )
			{
				ImageList_DrawEx( m_gdiProtocols, PROTOCOL_BT, dc.GetSafeHdc(),
						rcCell.left, rcCell.top, 16, 16, crLeftAligned, CLR_DEFAULT, pQueue->m_bSelected ? ILD_SELECTED : ILD_NORMAL );
			}
			else if ( pQueue->m_nProtocols == ( 1 << PROTOCOL_HTTP ) )
			{
				ImageList_DrawEx( m_gdiProtocols, PROTOCOL_HTTP, dc.GetSafeHdc(),
						rcCell.left, rcCell.top, 16, 16, crLeftAligned, CLR_DEFAULT, pQueue->m_bSelected ? ILD_SELECTED : ILD_NORMAL );
			}
			else if ( pQueue->m_nProtocols == ( 1 << PROTOCOL_ED2K ) )
			{
				ImageList_DrawEx( m_gdiProtocols, PROTOCOL_ED2K, dc.GetSafeHdc(),
						rcCell.left, rcCell.top, 16, 16, crLeftAligned, CLR_DEFAULT, pQueue->m_bSelected ? ILD_SELECTED : ILD_NORMAL );
			}
			else
			{
				CoolInterface.Draw( &dc,
					pQueue->m_bExpanded ? IDI_FOLDER_OPEN : IDI_FOLDER_CLOSED, 16,
					rcCell.left, rcCell.top, crLeftAligned, pQueue->m_bSelected );
			}
			rcCell.left += 16;
			dc.FillSolidRect( rcCell.left, rcCell.top, 1, rcCell.Height(), crLeftAligned );
			rcCell.left += 1;
			
			strText = pQueue->m_sName;
			break;
			
		case UPLOAD_COLUMN_SIZE:
			if ( pQueue == UploadQueues.m_pTorrentQueue )
				strText.Format( _T("%u/%u"), pQueue->m_nMinTransfers, pQueue->m_nMaxTransfers ); //No. Clients was loaded into these variables
			else if ( pQueue != UploadQueues.m_pHistoryQueue )
				strText.Format( _T("%u/%u"), pQueue->GetTransferCount(), pQueue->GetQueuedCount() );
			break;
			
		case UPLOAD_COLUMN_SPEED:
			if ( pQueue != UploadQueues.m_pHistoryQueue )
				strText = Settings.SmartSpeed( pQueue->GetMeasuredSpeed() );
			break;
		}
		
		nTextLeft	= min( nTextLeft, (int)rcCell.left );
		nTextRight	= max( nTextRight, (int)rcCell.right );
		
		if ( rcCell.Width() < 8 ) strText.Empty();
		
		if ( dc.GetTextExtent( strText ).cx > rcCell.Width() - 8 )
		{
			while ( dc.GetTextExtent( strText + _T('\x2026') ).cx > ( rcCell.Width() - 8 ) && strText.GetLength() > 0 )
			{
				strText.Truncate( strText.GetLength() - 1 );
			}
			
			if ( strText.GetLength() > 0 ) strText += _T('\x2026');
		}
		
		int nWidth		= dc.GetTextExtent( strText ).cx;
		int nPosition	= 0;
		
		switch ( pColumn.fmt & LVCFMT_JUSTIFYMASK )
		{
		default:
			nPosition = ( rcCell.left + 4 );
			break;
		case LVCFMT_CENTER:
			nPosition = ( ( rcCell.left + rcCell.right ) / 2 ) - ( nWidth / 2 );
			break;
		case LVCFMT_RIGHT:
			nPosition = ( rcCell.right - 4 - nWidth );
			break;
		}
		
		dc.SetBkColor( crBack );
		dc.ExtTextOut( nPosition, rcCell.top + 2, ETO_CLIPPED|ETO_OPAQUE,
			&rcCell, strText, NULL );
	}
	
	if ( nTextRight < rcRow.right )
	{
		CRect rcBlank( nTextRight, rcRow.top, rcRow.right, rcRow.bottom );
		dc.FillSolidRect( &rcBlank, crBack );
	}
	
	dc.SelectObject( &CoolInterface.m_fntNormal );
	
	if ( bFocus )
	{
		CRect rcFocus( nTextLeft, rcRow.top, max( (int)rcRow.right, nTextRight ), rcRow.bottom );
		dc.Draw3dRect( &rcFocus, CoolInterface.m_crHiBorder, CoolInterface.m_crHiBorder );
	}
}