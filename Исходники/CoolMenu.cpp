void CCoolMenu::OnDrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CRect rcItem, rcText;
	CString strText;
	int nIcon = -1;
	CDC dc;
	
	BOOL	bSelected	= lpDrawItemStruct->itemState & ODS_SELECTED;
	BOOL	bChecked	= lpDrawItemStruct->itemState & ODS_CHECKED;
	BOOL	bDisabled	= lpDrawItemStruct->itemState & ODS_GRAYED;
	BOOL	bKeyboard	= FALSE;
	BOOL	bEdge		= TRUE;
	
	dc.Attach( lpDrawItemStruct->hDC );
	
	if ( CWnd* pWnd = dc.GetWindow() )
	{
		CRect rcScreen( &lpDrawItemStruct->rcItem );
		CPoint ptCursor;
		
		GetCursorPos( &ptCursor );
		pWnd->ClientToScreen( &rcScreen );
		
		bKeyboard = ! rcScreen.PtInRect( ptCursor );
	}
	
	rcItem.CopyRect( &lpDrawItemStruct->rcItem );
	rcItem.OffsetRect( -rcItem.left, -rcItem.top );
	if ( m_hMsgHook != NULL ) rcItem.bottom += ( bEdge = m_bPrinted );
	
	rcText.CopyRect( &rcItem );
	rcText.left += 32;
	rcText.right -= 2;
	
	CDC* pDC = CoolInterface.GetBuffer( dc, rcItem.Size() );
	
	if ( m_bmWatermark.m_hObject != NULL )
	{
		DrawWatermark( pDC, &rcItem, lpDrawItemStruct->rcItem.left, lpDrawItemStruct->rcItem.top );
	}
	else
	{
		pDC->FillSolidRect( rcItem.left, rcItem.top, 24, rcItem.Height(), CoolInterface.m_crMargin );
		pDC->FillSolidRect( rcItem.left + 24, rcItem.top, rcItem.Width() - 24, rcItem.Height(), CoolInterface.m_crBackNormal );
	}
	
	if ( m_pStrings.Lookup( lpDrawItemStruct->itemData, strText ) == FALSE )
	{
		int nMiddle = rcText.top + 1;
		
		pDC->FillSolidRect( rcText.left, nMiddle, rcText.Width() + 2, 1, CoolInterface.m_crDisabled );
		
		dc.BitBlt( lpDrawItemStruct->rcItem.left, lpDrawItemStruct->rcItem.top,
			rcItem.Width(), rcItem.Height(), pDC, 0, 0, SRCCOPY );
		dc.Detach();
		
		return;
	}
	
	if ( bSelected )
	{
		if ( ! bDisabled )
		{
			pDC->Draw3dRect( rcItem.left + 1, rcItem.top + 1,
				rcItem.Width() - 2, rcItem.Height() - 1 - bEdge,
				CoolInterface.m_crBorder, CoolInterface.m_crBorder );
			pDC->FillSolidRect( rcItem.left + 2, rcItem.top + 2,
				rcItem.Width() - 4, rcItem.Height() - 3 - bEdge,
				CoolInterface.m_crBackSel );
			
			pDC->SetBkColor( CoolInterface.m_crBackSel );
		}
		else if ( bKeyboard )
		{
			pDC->Draw3dRect( rcItem.left + 1, rcItem.top + 1,
				rcItem.Width() - 2, rcItem.Height() - 1 - bEdge,
				CoolInterface.m_crBorder, CoolInterface.m_crBorder );
			pDC->FillSolidRect( rcItem.left + 2, rcItem.top + 2,
				rcItem.Width() - 4, rcItem.Height() - 3 - bEdge,
				CoolInterface.m_crBackNormal );
			
			pDC->SetBkColor( CoolInterface.m_crBackNormal );
		}
	}
	else
	{
		pDC->SetBkColor( CoolInterface.m_crBackNormal );
	}
	
	if ( bChecked )
	{
		pDC->Draw3dRect( rcItem.left + 2, rcItem.top + 2, 20, rcItem.Height() - 3 - bEdge,
			CoolInterface.m_crBorder, CoolInterface.m_crBorder );
		pDC->FillSolidRect( rcItem.left + 3, rcItem.top + 3, 18, rcItem.Height() - 5 - bEdge,
			( bSelected && !bDisabled ) ? CoolInterface.m_crBackCheckSel : CoolInterface.m_crBackCheck );
	}
	
	nIcon = CoolInterface.ImageForID( (DWORD)lpDrawItemStruct->itemID );
	
	if ( bChecked && nIcon < 0 ) nIcon = m_nCheckIcon;
	
	if ( nIcon >= 0 )
	{
		CPoint pt( rcItem.left + 4, rcItem.top + 4 );
		
		if ( bDisabled )
		{
			ImageList_DrawEx( CoolInterface.m_pImages.m_hImageList, nIcon, pDC->GetSafeHdc(),
				pt.x, pt.y, 0, 0, CLR_NONE, CoolInterface.m_crDisabled, CM_DISABLEDBLEND );
		}
		else if ( bChecked )
		{
			CoolInterface.m_pImages.Draw( pDC, nIcon, pt, ILD_TRANSPARENT );
		}
		else if ( bSelected )
		{
			pt.Offset( 1, 1 );
			pDC->SetTextColor( CoolInterface.m_crShadow );
			CoolInterface.m_pImages.Draw( pDC, nIcon, pt, ILD_MASK );
			pt.Offset( -2, -2 );
			CoolInterface.m_pImages.Draw( pDC, nIcon, pt, ILD_TRANSPARENT );
		}
		else
		{
			ImageList_DrawEx( CoolInterface.m_pImages.m_hImageList, nIcon, pDC->GetSafeHdc(),
				pt.x, pt.y, 0, 0, CLR_NONE, CoolInterface.m_crMargin, ILD_BLEND25 );
		}
	}
	
	CFont* pOld = (CFont*)pDC->SelectObject(
					( lpDrawItemStruct->itemState & ODS_DEFAULT ) && ! bDisabled ?
					&CoolInterface.m_fntBold : &CoolInterface.m_fntNormal );
	
	pDC->SetBkMode( TRANSPARENT );
	pDC->SetTextColor( bDisabled ? CoolInterface.m_crDisabled :
		( bSelected ? CoolInterface.m_crCmdTextSel : CoolInterface.m_crCmdText ) );
	DrawMenuText( pDC, &rcText, strText );
	
	pDC->SelectObject( pOld );
	
	dc.BitBlt( lpDrawItemStruct->rcItem.left, lpDrawItemStruct->rcItem.top,
		rcItem.Width(), rcItem.Height(), pDC, 0, 0, SRCCOPY );
	dc.Detach();
}